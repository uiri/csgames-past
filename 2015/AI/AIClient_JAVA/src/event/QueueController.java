/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** QueueController.java
 ** Controller that manage all the queue
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.util.LinkedList;
import java.util.Queue;

public class QueueController {
	private static QueueController instance = null;
	private Queue<OutgoingEvent> outEvents = new LinkedList<OutgoingEvent>();
	private Queue<IngoingEvent> inEvents = new LinkedList<IngoingEvent>();

	protected QueueController() {
		// Exists only to defeat instantiation
	}

	public static QueueController getInstance() {
		if (instance == null) {
			instance = new QueueController();
		}
		return instance;
	}
	
	public void addOutgoingEvent(OutgoingEvent event) {
		outEvents.add(event);
	}

	public void addIngoingEvent(IngoingEvent event) {
		inEvents.add(event);
	}

	public Queue<OutgoingEvent> getOutEvents() {
		return outEvents;
	}

	public Queue<IngoingEvent> getInEvents() {
		return inEvents;
	}
}
