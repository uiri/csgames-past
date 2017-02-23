/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** UpdateMissileEvent.java
 ** Event that happen when a missile move
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.awt.Point;

import mathUtils.Direction;

import world.World;

public class UpdateMissileEvent extends IngoingEvent {
	private int teamID, characterID;
	private Direction direction;
	private Point position = new Point();

	@Override
	public void execute() {
		World.getInstance().getTeam(teamID).getCharacter(characterID)
				.getMissile().updateInfo(position, direction);
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 6);

		teamID = convertCharToNumeral(messageParts[0]);
		if (teamID == 0) {
			return false;
		}

		characterID = convertCharToNumeral(messageParts[1]);
		position.x = convertCharToNumeral(messageParts[2]);
		position.y = convertCharToNumeral(messageParts[3]);
		direction = Direction.values()[convertCharToNumeral(messageParts[4])];
		return true;
	}
}
