/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** MissileHitEvent.java
 ** Event that happen when a missile hit an entity
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import world.World;

public class MissileHitEvent extends IngoingEvent {

	private int hitEntity;
	private int hitTeamId;
	private int hitCharacterId;
	private int originTeamId;
	private int originCharacterId;
	private int backfire;

	@Override
	public void execute() {
		World.getInstance().getTeam(originTeamId)
				.getCharacter(originCharacterId).missileHit();

		if (hitEntity == 1) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.hitByMissile();
		} else if (hitEntity == 2) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.mineHit();
		} else if (hitEntity == 3) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.missileHit();
		}
		
		if(backfire == 1)
		{
			World.getInstance().getTeam(originTeamId)
			.getCharacter(originCharacterId).hitByMissile();
		}
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 7);

		hitEntity = convertCharToNumeral(messageParts[0]);
		hitTeamId = convertCharToNumeral(messageParts[1]);
		hitCharacterId = convertCharToNumeral(messageParts[2]);

		originTeamId = convertCharToNumeral(messageParts[3]);
		if (originTeamId == 0) {
			return false;
		}
		originCharacterId = convertCharToNumeral(messageParts[4]);
		backfire = convertCharToNumeral(messageParts[5]);
		return true;
	}

}