/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** AI.java
 ** The AI loop
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package aiclient;

import mathUtils.Direction;
import mathUtils.Vector2;
import world.Character;
import world.World;

/**
 * Represents the AI that need to be implemented
 */
public class AI {
	/**
	 * Enum created for the AI example
     * (Can be deleted)
	 */
	public enum AIStatus {
		INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT
	}

	/**
	 * The current status of the AI example
	 * (Can be deleted)
	 */
	AIStatus status = AIStatus.INIT;
	
	/**
	 * The world singleton needed to get the info on the current state of the world
	 */
	World world = World.getInstance();

	Vector2 position1 = new Vector2(0, 0);
	Vector2 position2 = new Vector2(8, 0);
	Vector2 position3 = new Vector2(0, 8);
	Vector2 position4 = new Vector2(8, 8);

	/**
	 * Function call to set the name of the team and characters
     * (Cannot be deleted)
	 */
	public void setNames() {
		String teamName = "No name";
		String[] characternames = {"No name", "No name"};
		world.setNames(teamName, characternames);
	}

	/**
	 * Function call every 30 ms, this is the starting point for the AI
     * (Cannot be deleted)
	 */
	public void tick() {
		if (status == AIStatus.INIT) {
			init();
		} else if (status == AIStatus.LOWER_RIGHT) {
			lowerRight();
		} else if (status == AIStatus.LOWER_LEFT) {
			lowerLeft();
		} else if (status == AIStatus.UPPER_RIGHT) {
			upperRight();
		} else if (status == AIStatus.UPPER_LEFT) {
			upperLeft();
		}
	}

	/**
	 * Function call for the init state of the AI example
     * (Can be deleted)
	 */
	public void init() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		king.move(position2);
		soldier.move(position3);

		status = AIStatus.LOWER_RIGHT;
	}

	/**
	 * Function call for the lowerRight state of the AI example
     * (Can be deleted)
	 */
	public void lowerRight() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position2)) {
			king.move(position1);
			soldier.move(position4);

			king.dropMine();
			soldier.dropMine();

			king.shootMissile(Direction.LEFT);
			soldier.shootMissile(Direction.RIGHT);

			status = AIStatus.LOWER_LEFT;
		}
	}

	/**
	 * Function call for the lowerLeft state of the AI example
     * (Can be deleted)
	 */
	public void lowerLeft() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position1)) {
			king.move(position4);
			soldier.move(position1);

			king.shootMissile(Direction.UP);
			soldier.shootMissile(Direction.DOWN);

			king.dropMine();
			soldier.dropMine();

			status = AIStatus.UPPER_RIGHT;
		}
	}

	/**
	 * Function call for the upperRight state of the AI example
     * (Can be deleted)
	 */
	public void upperRight() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position4)) {
			king.move(position3);
			soldier.move(position2);

			king.shootMissile(Direction.DOWN);
			soldier.shootMissile(Direction.UP);

			king.dropMine();
			soldier.dropMine();

			status = AIStatus.UPPER_LEFT;
		}
	}

	/**
	 * Function call for the upperLeft state of the AI example
     * (Can be deleted)
	 */
	public void upperLeft() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position3)) {
			king.move(position2);
			soldier.move(position3);

			king.dropMine();
			soldier.dropMine();

			king.shootMissile(Direction.RIGHT);
			soldier.shootMissile(Direction.LEFT);

			status = AIStatus.LOWER_RIGHT;
		}
	}
}
