'''
Created on Dec 20, 2014

@author: scarriere
'''
from event.OutgoingEvent import OutgoingEvent

class MoveCharacterEvent(OutgoingEvent):

    def __init__(self, characterId, positionX, positionY):
        self.characterId = characterId
        self.positionX = positionX
        self.positionY = positionY
        
    def toString(self):
        message = "Game:Move:"
        
        message += str(self.characterId) + self.SEPARATOR
        message += str(self.positionX) + self.SEPARATOR
        message += str(self.positionY)
        
        return message