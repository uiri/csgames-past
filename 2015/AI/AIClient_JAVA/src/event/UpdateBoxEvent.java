/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** UpdateBoxEvent.java
 ** Event that send a box position
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.awt.Point;

import world.World;

public class UpdateBoxEvent extends IngoingEvent {
	private Point position = new Point();

	@Override
	public void execute() {
		World.getInstance().updateBox(position);
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 3);

		position.x = convertCharToNumeral(messageParts[0]);
		position.y = convertCharToNumeral(messageParts[1]);
		return true;
	}

}
