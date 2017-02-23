/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** EventController.java
 ** Singleton that manage all the events
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;


public class EventController {
	private static EventController instance = null;

	protected EventController() {
		// Exists only to defeat instantiation
	}

	public static EventController getInstance() {
		if (instance == null) {
			instance = new EventController();
		}
		return instance;
	}
	
	public void executeIngoingEvents() {
		QueueController queueController = QueueController.getInstance();
		
		while (!queueController.getInEvents().isEmpty()) {
			IngoingEvent event = queueController.getInEvents().poll();
			if(event != null) {
				event.execute();
			}
		}
	}
}
