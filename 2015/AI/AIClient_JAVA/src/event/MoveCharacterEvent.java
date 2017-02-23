/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** MoveCharacter.java
 ** Event call to move a character
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.awt.Point;

public class MoveCharacterEvent extends OutgoingEvent {
	private int characterID;
	private Point position;

	public MoveCharacterEvent(int characterID, Point position) {
		this.characterID = characterID;
		this.position = position;
	}

	@Override
	public String toString() {
		String message = "Game:Move" + SEPARATOR;
		message += characterID + SEPARATOR;
		message += position.x + SEPARATOR;
		message += position.y;
		return message;
	}
}
