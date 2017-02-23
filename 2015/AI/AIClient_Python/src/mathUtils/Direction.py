'''
Created on Jan 6, 2015

@author: scarriere
'''

from enum import Enum


class Direction(Enum):
    '''
    Enum that represent every direction possible
        UP, DOWN, LEFT, RIGHT
    '''
    
    UP, DOWN, LEFT, RIGHT = range(4)