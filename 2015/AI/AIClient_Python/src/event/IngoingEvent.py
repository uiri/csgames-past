'''
Created on Dec 15, 2014

@author: scarriere
'''

from event.BaseEvent import BaseEvent

class IngoingEvent(BaseEvent):
    
    def __init__(self):
        '''
        Constructor
        '''
    
    def execute(self):
        print("IngoingEvent::execute")
    
    def fillArguments(self, string):
        print("IngoingEvent::fillArguments")
        return False