'''
Created on Jan 11, 2015

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class UpdateBoxEvent(IngoingEvent):

    def __init__(self):
        self.x = 0
        self.y = 0
    
    def fillArguments(self, string):
        arguments = string.split(":", 2)
        
        self.x = int(arguments[0])
        self.y = int(arguments[1])
        
    def execute(self):
        world = Singleton(World)
        world._updateBox(self.x, self.y)
        