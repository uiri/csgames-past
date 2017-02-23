'''
Created on Jan 6, 2015

@author: scarriere
'''

from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction

class Missile(object):
    '''
    Class that contain all the informations about the Missile
        (You can't use any of the functions or variables that start with an "_")
    '''
    def __init__(self, position):
        self.isReady = True
        '''
        Is the missile ready to be use
            (see :class:`.bool`)
        '''
        self.position = Vector2(position.x, position.y)
        '''
        The current position of the missile
            (see :class:`.Vector2`)
        '''
        self.direction = Direction.UP
        '''
        The current direction of the missile
            (see :class:`.Direction`)
        '''
        
    def _updatePositionDirection(self, position, direction):
        self.position.x = position.x
        self.position.y = position.y
        self.direction = direction
