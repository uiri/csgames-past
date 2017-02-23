/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** NetworkController.java
 ** Control all the network communication
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package network;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import event.EventFactory;
import event.OutgoingEvent;
import event.QueueController;

public class NetworkController {
	private static NetworkController instance = null;
	private Socket webSocket;
	private PrintWriter outToServer;
	private BufferedReader inFromServer;
	private ReaderThread readerThead;
	private boolean connected = false;

	protected NetworkController() {
		try {
			webSocket = new Socket("127.0.0.1", 1337);
			outToServer = new PrintWriter(webSocket.getOutputStream(), true);
			inFromServer = new BufferedReader(new InputStreamReader(
					webSocket.getInputStream()));
			readerThead = new ReaderThread();
			connected = true;
		} catch (Exception e) {
			System.out.println("Error : the GameClient is not started");
		}
	}

	public static NetworkController getInstance() {
		if (instance == null) {
			instance = new NetworkController();
		}
		return instance;
	}

	public void init() {
		sendMessage("AIClientReady");
		if (readerThead != null) {
			readerThead.start();
		}
	}

	public void executeOutgoingEvents() {
		QueueController queueController = QueueController.getInstance();

		while (!queueController.getOutEvents().isEmpty()) {
			OutgoingEvent event = queueController.getOutEvents().remove();
			NetworkController.getInstance().sendMessage(event.toString());
		}
	}

	public boolean isConnected() {
		return connected;
	}

	public void readFunctionThread() {
		boolean exit = false;
		while (!exit) {
			String fullMessage = readMessage();

			if (fullMessage == null || fullMessage.equals("Net:OkForExit")) {
				exit = true;
				connected = false;
				break;
			}

			dispatchMessage(fullMessage);
		}

	}

	public void dispatchMessage(String message) {
		String[] messageParts = message.split(":", 2);
		if (messageParts[0].equals("Net")) {
			parseNetMessage(messageParts[1]);
		} else if (messageParts[0].equals("Game")) {
			EventFactory.generateEvent(messageParts[1]);
		}
	}

	public void parseNetMessage(String message) {
		if (message.equals("JoinGameFailed")) {
			connectionRetry();
		} else if (message.equals("ErrorGameClientDisconnect")) {
			System.out.println("Error : the game client was disconnected");
		} else {
			System.out.println("unknow net message: " + message);
		}
	}

	public void sendMessage(String message) {
		if (outToServer != null) {
			System.out.println(message);
			outToServer.println(message + '\n');
		} else {
			System.out.println("Error: can't send the message: " + message);
		}
	}

	public String readMessage() {
		String textServer = "";
		try {
			textServer = inFromServer.readLine();
			//System.out.println("Server: " + textServer);
		} catch (Exception e) {
			System.out.println("Error: can't read on socket");
			return null;
		}
		return textServer;
	}

	public void close() {
		try {
			sendMessage("Exit");

			if (readerThead != null) {
				readerThead.join();
			}

			if (webSocket != null) {
				webSocket.close();
			}

			connected = false;
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public void connectionRetry() {
		System.out.println("Error : the game client was not connected");
		System.out.println("Info : connection retry in few seconds...");
		try {
			Thread.sleep(2000);
			sendMessage("AIClientReady");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
