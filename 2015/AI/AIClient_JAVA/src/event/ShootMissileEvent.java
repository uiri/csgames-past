/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** ShootMissileEvent.java
 ** Event call when a character ask to shoot a missile
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class ShootMissileEvent extends OutgoingEvent {
	private int characterId;
	private int direction;

	public ShootMissileEvent(int characterId, int direction) {
		this.characterId = characterId;
		this.direction = direction;
	}

	@Override
	public String toString() {
		String message = "Game:ThrowMissile:";
		message += characterId + SEPARATOR;
		message += direction;

		return message;
	}
}
