/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** MinehitEvent.java
 ** Event that happen when a character hit a mine
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import world.World;

public class MineHitEvent extends IngoingEvent {

	private int hitTeamId;
	private int hitCharacterId;
	private int originTeamId;
	private int originCharacterId;

	@Override
	public void execute() {
		World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId).hitByMine();
		World.getInstance().getTeam(originTeamId).getCharacter(originCharacterId).mineHit();
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 5);
		
		hitTeamId = convertCharToNumeral(messageParts[0]);
		if (hitTeamId == 0) {
			return false;
		}
		hitCharacterId = convertCharToNumeral(messageParts[1]);

		originTeamId = convertCharToNumeral(messageParts[2]);
		if (originTeamId == 0) {
			return false;
		}
		originCharacterId = convertCharToNumeral(messageParts[3]);
		
		return true;
	}

}
