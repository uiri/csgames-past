// Load the TCP Library
net = require('net');

var debug = true;
var HOST = '127.0.0.1';
var PORT = 1337;

var clients = [];
var currentClientId = 1;
var currentClientConnected = 0;
var gameClientId = 0;

var endline = '\n';
function print(message) {
	if(debug) {
		process.stdout.write(message + endline);
	}
}

net.createServer(function (socket) {

	// Identify this client
	socket.adress = socket.remoteAddress + ":" + socket.remotePort;
	socket.id = currentClientId;
	socket.msg = ''; // Current message, per connection
	socket.setEncoding('utf8');
	
	// Put this new client in the list
	clients.push(socket);
	currentClientConnected++;
	currentClientId++;

	print(' - join - ');

	socket.on('data', function (data) {
		var arr = data.split(endline);
		arr.forEach(function (chunk)
		{
			if(chunk.length > 1)
			{
				// print(' - Chunk - ' + chunk);
				socket.emit('message', chunk);
			}
		});
	});

	socket.on('message', function(msg) {
		if (msg == 'Exit')
		{
			send('Net:OkForExit', socket);
		}
		else if (msg == 'GameClientReady')
		{
			socket.emit('GameClientReady');
		}
		else if (msg == 'AIClientReady')
		{
			socket.emit('AIClientReady')
		}
		else
		{
			socket.emit('GameMessage', msg)
		}
	});

	socket.on('GameClientReady', function ()
	{
		if(gameClientId == 0)
		{
			gameClientId = socket.id;
			send('Net:YourAreTheGameClient', socket);
			print(' - Game Client Ready - ');
		}
		else
		{
			send('Net:CreateGameFailed', socket);
		}
	});
	
	socket.on('AIClientReady', function ()
	{
		if(gameClientId != 0)
		{
			send('Game:JoinGame:' + socket.id, socket);
		}
		else
		{
			send('Net:JoinGameFailed', socket);
		}
	});

	socket.on('GameMessage', function (message)
	{
		if(gameClientId != 0)
		{
			message += ':' + socket.id;
			broadcast(message, socket);
		}
		else
		{
			send('Net:ErrorGameClientDisconnect', socket);
		}
	});

	socket.on('end', function ()
	{
		print(' - end - ')
		removeSocket(socket);
	});

	socket.on('error', function ()
	{
		print(' - error - ')
		removeSocket(socket);
	});
  
	function broadcast(message, sender) 
	{
		clients.forEach(function (client)
		{
			// Don't want to send it to sender
			if (client === sender) return;
			client.write(message + endline);
		});
		// print('Broadcast - ' + message);
	}

	function send(message, socket) 
	{
		socket.write(message + endline)
		// print('Send - ' + message)
	}

	function removeSocket(socket)
	{
		if(socket.id == gameClientId)
		{
			process.exit();
		}
		
		clients.splice(clients.indexOf(socket), 1);
		broadcast('Game:ClientDisconnect:' + socket.id);
	}
}).listen(PORT, HOST);

console.log('Game Server: ' + HOST + ':' + PORT);

