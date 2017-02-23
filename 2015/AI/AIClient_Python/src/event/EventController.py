'''
Created on Dec 16, 2014

@author: scarriere
'''

from aiclient.Singleton import Singleton
from event.QueueController import QueueController

class EventController:
    _instance = None
    
    def executeIngoingEvents(self):
        queueController = Singleton(QueueController)
        while not queueController.inEvents.empty():
            event = queueController.inEvents.get()
            event.execute()