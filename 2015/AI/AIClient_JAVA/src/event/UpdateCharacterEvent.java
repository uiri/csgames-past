/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** UpdateCharacterEvent.java
 ** Event that happen when a character move
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import mathUtils.Vector2;
import world.World;

public class UpdateCharacterEvent extends IngoingEvent {
	private int teamID, characterID;
	private int positionX, positionY;

	@Override
	public void execute() {
		//System.out.println("Move character:" + characterID + " from " + teamID
		//		+ " to " + positionX + "," + positionY);
		Vector2 position = new Vector2(positionX, positionY);
		World.getInstance().getTeam(teamID).getCharacter(characterID)
				.updateInfo(position);
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 5);

		teamID = convertCharToNumeral(messageParts[0]);
		if (teamID == 0) {
			return false;
		}

		characterID = convertCharToNumeral(messageParts[1]);
		positionX = convertCharToNumeral(messageParts[2]);
		positionY = convertCharToNumeral(messageParts[3]);
		return true;
	}

}
