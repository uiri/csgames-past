/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Team.java
 ** A team
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import java.util.ArrayList;
import java.util.List;

/**
 * Class that contain all the information about the team
 */
public class Team {
	private int id;
	private List<Character> characters = new ArrayList<Character>();

	public Team(int id, int numberOfCharacter) {
		this.id = id;
		for (int index = 0; index < numberOfCharacter; ++index) {
			characters.add(new Character(index));
		}
	}

	/**
	 * Return the id of this team
	 * 
	 * @return the id of this team
	 */
	public int getId() {
		return id;
	}

	/**
	 * Return character associate with a certain id
	 * Note: The character id start at 0 and are the same as their index
	 * 
	 * @return the character
	 */
	public Character getCharacter(int id) {
		return characters.get(id);
	}

	/**
	 * Return the list of character from this team
	 * 
	 * @return the list of character
	 */
	public List<Character> getCharacters() {
		return characters;
	}
	
	/**
	 * Return the first character of the team
	 * Exemple:
	 * aCharacter = aTeam.getFirstCharacter()
	 * @return Character
	 */
	public Character getFirstCharacter() {
        return getCharacter(0);
	}

	/**
	 * Return the second character of the team
	 * Exemple:
	 * aCharacter = aTeam.getFirstCharacter()
	 * @return Character
	 */
	public Character getSecondCharacter() {
        return getCharacter(1);
	}
}
