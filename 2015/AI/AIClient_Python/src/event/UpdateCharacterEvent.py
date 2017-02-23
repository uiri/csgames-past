'''
Created on Dec 21, 2014

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from world.World import World
from aiclient.Singleton import Singleton
from mathUtils.Vector2 import Vector2

class UpdateCharacterEvent(IngoingEvent):

    def __init__(self):
        self.teamId = 0
        self.characterId = 0
        self.position = Vector2(0,0)
    
    def fillArguments(self, string):
        arguments = string.split(":", 4)
        
        self.teamId = int(arguments[0])
        self.characterId = int(arguments[1])
        self.position.x = int(arguments[2])
        self.position.y = int(arguments[3])
        
    def execute(self):
        world = Singleton(World)
        world.getTeam(self.teamId).characters[self.characterId]._updatePosition(self.position)
        