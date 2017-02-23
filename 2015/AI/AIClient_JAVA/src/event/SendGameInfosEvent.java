/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** SendGameInfosEvent.java
 ** Event that happen before the game start
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.util.ArrayList;
import java.util.List;

import world.World;

public class SendGameInfosEvent extends IngoingEvent {
	private int mapWidth, mapHeight, numberOfTeam, numberOfCharacter;
	private List<Integer> teamIDs = new ArrayList<Integer>();

	@Override
	public void execute() {
		World.getInstance().sendGameInfos(mapWidth, mapHeight, numberOfTeam, numberOfCharacter, teamIDs);
	}

	@Override
	public boolean fillArguments(String message) {
		String[] headerParts = message.split(SEPARATOR, 5);

		mapWidth = convertCharToNumeral(headerParts[0]);
		mapHeight = convertCharToNumeral(headerParts[1]);
		numberOfTeam = convertCharToNumeral(headerParts[2]);
		numberOfCharacter = convertCharToNumeral(headerParts[3]);

		if (numberOfTeam < 1 || numberOfCharacter < 1) {
			return false;
		}

		//Plus one for the sender id that we don't use
		String[] ids = headerParts[4].split(SEPARATOR, numberOfTeam+1);
		for (int index = 0; index < ids.length-1; ++index) {
			teamIDs.add(convertCharToNumeral(ids[index]));
			if (teamIDs.get(index) == 0) {
				return false;
			}
		}
		return false;
	}
}
