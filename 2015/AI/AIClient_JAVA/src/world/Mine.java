/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Mine.java
 ** A mine
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

/**
 * Class that contain all the informations about the mine
 */
public class Mine {

	private boolean isReady;

	public Mine() {
		this.isReady = true;
	}
	
	public void drop() {
		isReady = false;
	}
	
	public void hit() {
		isReady = true;
	}

	/**
	 * Check if the mine is ready
	 * 
	 * @return true if the missile is ready, else false
	 */
	public boolean isReady() {
		return isReady;
	}
}