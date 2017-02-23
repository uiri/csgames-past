/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** JoinGameEvent.java
 ** Event that happen when you join a game
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import world.World;

public class JoinGameEvent extends IngoingEvent {

	private int yourId;

	@Override
	public void execute() {
		World.getInstance().joinGame(yourId);
	}

	@Override
	public boolean fillArguments(String string) {
		yourId = convertCharToNumeral(string);
		if (yourId != 0) {
			return true;
		}
		return false;
	}

}
