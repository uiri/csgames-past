'''
Created on Jan 6, 2015

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World
from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction

class UpdateMissileEvent(IngoingEvent):

    def __init__(self):
        self.teamId = 0
        self.characterId = 0
        self.position = Vector2(0,0)
        self.direction = Direction.UP
    
    def fillArguments(self, string):
        arguments = string.split(":", 5)
        
        self.teamId = int(arguments[0])
        self.characterId = int(arguments[1])
        self.position.x = int(arguments[2])
        self.position.y = int(arguments[3])
        self.direction = Direction(int(arguments[4]))
        
    def execute(self):
        world = Singleton(World)
        world.getTeam(self.teamId).characters[self.characterId].missile._updatePositionDirection(self.position, self.direction)
        