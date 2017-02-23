/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** DropMineEvent.java
 ** Event call when a character ask to drop a mine
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class DropMineEvent extends OutgoingEvent {
	private int characterId;

	public DropMineEvent(int characterId) {
		this.characterId = characterId;
	}

	@Override
	public String toString() {
		String message = "Game:DropMine:";
		message += characterId;

		return message;
	}
}
