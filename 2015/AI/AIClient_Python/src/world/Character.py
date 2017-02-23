'''
Created on Dec 20, 2014

@author: scarriere
'''

from event.DropMineEvent import DropMineEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.Missile import Missile
from mathUtils.Vector2 import Vector2
from event.MoveCharacterEvent import MoveCharacterEvent
from event.ThrowMissileEvent import ThrowMissileEvent, Direction


class Character(object):
    '''
    Class that contain all the informations about the Character
        (You can't use any of the functions or variables that start with an "_")
    '''
    _queueController = Singleton(QueueController)
    
    def __init__(self, characterId, position):
        self._characterId = characterId
        self.position = Vector2(position.x, position.y)
        '''
        The current position of the character
            (see :class:`.Vector2`)
        '''
        self.mineReady = True
        '''
        Is the mine ready to be use
            (see :class:`.bool`)
        '''
        self.missile = Missile(Vector2(0,0))
        '''
        The missile of the character
            (see :class:`.Missile`)
        '''
        self.life = 3
        '''
        The life total of the character
            (see :class:`.int`)
        '''
    
    def _updatePosition(self, position):
        self.position.x = position.x
        self.position.y = position.y
        
    def _hitByMine(self):
        if self.isAlive():
            self.life -= 1
    
    def _mineHit(self):
        self.mineReady = True
    
    def _hitByMissile(self):
        if self.isAlive():
            self.life -= 1
        
    def _missileHit(self):
        self.missile.isReady = True

    def goTo(self, position):
        '''
        Send the order to move the character
        to a certain position(:class:`.Vector2`)
            
        Exemple::
        
            aCharacter.goTo(Vector2(6,7))
        '''
        event = MoveCharacterEvent(self._characterId, position.x, position.y)
        self._queueController.outEvents.put(event)
        
    def dropMine(self):
        '''
        Send the order to drop a mine on the current position(:class:`.Vector2`)
            if the mine is ready
            
        Exemple::
        
            aCharacter.dropMine()
        '''
        if(self.mineReady):
            event = DropMineEvent(self._characterId)
            self._queueController.addOutgoingEvent(event)
            self.mineReady = False

    def shootMissile(self, direction):
        '''
        Send the order to shoot a missile on a certain direction(:class:`.Direction`)
            if the missile is ready
            
        Exemple::
        
            aCharacter.shootMissile(Direction.UP)
        '''
        if(self.missile.isReady):
            event = ThrowMissileEvent(self._characterId, direction)
            self._queueController.addOutgoingEvent(event)
            self.missile.isReady = False
        
    def isAlive(self):
        '''
        Check if the character still have some life point
            
        Exemple::
        
            checkIfAlive = aCharacter.isAlive()
        '''
        return self.life > 0
    
    def getPosition(self):
        '''
        Return the position of the character
            
        Exemple::

            position = aCharacter.getPosition()
        '''
        return self.position
