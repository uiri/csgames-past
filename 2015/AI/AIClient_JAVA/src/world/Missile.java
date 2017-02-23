/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Missile.java
 ** A missile
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import java.awt.Point;
import mathUtils.Direction;

/**
 * Class that contain all the informations about the missile
 */
public class Missile {
	private Point position;
	private Direction direction;
	private boolean isReady;

	public Missile() {
		this.position = new Point(0, 0);
		this.direction = Direction.UP;
		this.isReady = true;
	}

	public void shoot() {
		this.isReady = false;
	}
	
	public void updateInfo(Point position, Direction direction) {
		this.position = position;
		this.direction = direction;
	}

	public void hit() {
		this.isReady = true;
	}

	/**
	 * Return the position of the missile
	 * 
	 * @return the position
	 */
	public Point getPosition() {
		return position;
	}

	/**
	 * Return the direction of the missile
	 * 
	 * @return the direction
	 */
	public Direction getDirection() {
		return direction;
	}

	/**
	 * Check if the missile is ready
	 * 
	 * @return true if the missile is ready, else false
	 */
	public boolean isReady() {
		return isReady;
	}
}