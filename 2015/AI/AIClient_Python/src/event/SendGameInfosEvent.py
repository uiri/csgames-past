'''
Created on Dec 20, 2014

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class SendGameInfosEvent(IngoingEvent):

    def __init__(self):
        self.mapWidth = 0
        self.mapHeight = 0
        self.numberOfTeam = 0
        self.numberOfCharacter = 0
        self.teamsIds = []

    def fillArguments(self, string):
        numberParts = string.split(":", 4)
        self.mapWidth = int(numberParts[0])
        self.mapHeight = int(numberParts[1])
        self.numberOfTeam = int(numberParts[2])
        self.numberOfCharacter = int(numberParts[3])
        
        # The last number is the game client id that we don't need
        teamIds = numberParts[4].split(":", self.numberOfTeam)
        for index in range(0, self.numberOfTeam):
            self.teamsIds.insert(index, int(teamIds[index]))
            
    def execute(self):
        world = Singleton(World)
        world._sendGameInfos(self.mapWidth, self.mapHeight, self.numberOfTeam, self.numberOfCharacter, self.teamsIds)