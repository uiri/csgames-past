'''
Created on Dec 31, 2014

@author: scarriere
'''
from event.OutgoingEvent import OutgoingEvent

class DropMineEvent(OutgoingEvent):

    def __init__(self, characterId):
        self.characterId = characterId
        
    def toString(self):
        message = "Game:DropMine:"
        message += str(self.characterId)
        
        return message