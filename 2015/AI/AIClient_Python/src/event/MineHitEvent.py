'''
Created on Jan 2, 2015

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class MineHitEvent(IngoingEvent):

    def __init__(self):
        self.hitTeamId = 0
        self.hitCharacterId = 0
        self.originTeamId = 0
        self.originCharacterId = 0
    
    def fillArguments(self, string):
        arguments = string.split(":", 4)
        
        self.hitTeamId = int(arguments[0])
        self.hitCharacterId = int(arguments[1])
        self.originTeamId = int(arguments[2])
        self.originCharacterId = int(arguments[3])
        
    def execute(self):
        world = Singleton(World)
        world.getTeam(self.hitTeamId).characters[self.hitCharacterId]._hitByMine()
        world.getTeam(self.originTeamId).characters[self.originCharacterId]._mineHit()