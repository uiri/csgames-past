/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** AddPlayerEvent.java
 ** Event call to join game
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class AddPlayerEvent extends OutgoingEvent {
	private String teamName;
	private String[] characterNames;

	public AddPlayerEvent(String teamName, String[] characterNames) {
		this.teamName = teamName;
		this.characterNames = characterNames;
	}

	@Override
	public String toString() {
		String message = "Game:AddPlayer" + SEPARATOR;
		message += teamName;

		for (int index = 0; index < characterNames.length; ++index) {
			message += SEPARATOR + characterNames[index];
		}
		return message;
	}
}
