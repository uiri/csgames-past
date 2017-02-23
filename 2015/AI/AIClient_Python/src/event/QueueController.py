'''
Created on Dec 20, 2014

@author: scarriere
'''

import sys
import queue
from event.OutgoingEvent import OutgoingEvent
from event.IngoingEvent import IngoingEvent

class QueueController(object):
    _instance = None
    outEvents = queue.Queue()
    inEvents = queue.Queue()

    def addOutgoingEvent(self, event):
        if isinstance(event, OutgoingEvent):
            self.outEvents.put(event)
    
    def addIngoingEvent(self, event):
        if isinstance(event, IngoingEvent):
            self.inEvents.put(event)
            
    def getOutQueue(self):
        return self.outEvents