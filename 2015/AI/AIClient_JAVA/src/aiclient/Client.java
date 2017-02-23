/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Client.java
 ** Main program loop
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package aiclient;

import network.NetworkController;
import world.World;
import event.EventController;

/**
 * Main class (Any changes made to this class won't be taken)
 */
class Client {
	/**
	 * The main loop
	 * @param args
	 */
	public static void main(String args[]) {

		NetworkController networkController = NetworkController.getInstance();
		EventController eventController = EventController.getInstance();
		World world = World.getInstance();
		
		/**
		 * If your create a new class for the ai, replace it here
		 */
		SamAI ai = new SamAI();

		ai.setNames();
		networkController.init();

		while (networkController.isConnected() && !world.isGameIsFinished()) {
			eventController.executeIngoingEvents();

			if (world.isGameIsStarted()) {
				ai.tick();
			}

			networkController.executeOutgoingEvents();
			pause(33);
		}

		NetworkController.getInstance().close();
		System.out.println(" - end - ");
	}

	/**
	 * Put the current Thread on sleep for a certain time
	 * @param milli time to sleep
	 */
	public static void pause(long milli) {
		try {
			Thread.sleep(milli);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}