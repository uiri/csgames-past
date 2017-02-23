/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Character.java
 ** A character
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import mathUtils.Direction;
import mathUtils.Vector2;
import event.DropMineEvent;
import event.MoveCharacterEvent;
import event.QueueController;
import event.ShootMissileEvent;

/**
 * Class that contain all the information about the character
 */
public class Character {
	private Vector2 position;
	private int id;
	private int life;
	private Mine mine = new Mine();
	private Missile missile = new Missile();

	public Character(int id) {
		this.id = id;
		this.position = new Vector2(0, 0);
		this.life = 3;
	}

	public void updateInfo(Vector2 position) {
		this.position = position;
	}
	
	public void hitByMine() {
		if (isAlive()) {
			--life;
		}
	}

	public void hitByMissile() {
		if (isAlive()) {
			--life;
		}
	}

	public void mineHit() {
		mine.hit();
	}

	public void missileHit() {
		missile.hit();
	}
	
	/**
	 * Send the order to move the character to a certain position
	 * 
	 * Exemple :
	 *		character.move(new Point(5,5));
	 */	
	public void move(Vector2 position) {
		QueueController queueController = QueueController.getInstance();
		MoveCharacterEvent event = new MoveCharacterEvent(id, position);
		queueController.addOutgoingEvent(event);
	}

	/**
	 * Send the order to drop a mine at the character position
	 * if the mine is ready
	 * 
	 * Exemple :
	 *		character.dropMine();
	 */	
	public void dropMine() {
		if (mine.isReady()) {
			QueueController queueController = QueueController.getInstance();
			DropMineEvent event = new DropMineEvent(id);
			queueController.addOutgoingEvent(event);
			mine.drop();
		}
	}

	/**
	 * Send the order to shoot a missile on a certain direction
	 * if the missile is ready
	 * 
	 * Exemple :
	 *		character.shootMissile(Missile.Direction.UP);
	 */	
	public void shootMissile(Direction direction) {
		if (missile.isReady()) {
			QueueController queueController = QueueController.getInstance();
			ShootMissileEvent event = new ShootMissileEvent(id,
					direction.ordinal());
			queueController.addOutgoingEvent(event);
			missile.shoot();
		}
	}

	/**
	 * Return the id of this team
	 * 
	 * @return the id of this team
	 */
	public Vector2 getPosition() {
		return position;
	}

	/**
	 * Check if the character still have some life point
	 * 
	 * @return true if the character is alive, else false
	 */
	public boolean isAlive() {
		return life > 0;
	}

	/**
	 * Return the missile of the character
	 * 
	 * @return the missile
	 */
	public Missile getMissile() {
		return missile;
	}
}
