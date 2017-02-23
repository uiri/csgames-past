'''
Created on Jan 2, 2015

@author: scarriere
'''

from event.OutgoingEvent import OutgoingEvent
from mathUtils.Direction import Direction

class ThrowMissileEvent(OutgoingEvent):

    def __init__(self, characterId, direction):
        self.characterId = characterId
        self.direction = Direction(direction)
        
    def toString(self):
        message = "Game:ThrowMissile:"
        message += str(self.characterId) + self.SEPARATOR
        message += str(self.direction.value)
        
        return message