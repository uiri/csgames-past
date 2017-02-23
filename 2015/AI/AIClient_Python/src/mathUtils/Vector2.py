'''
Created on Jan 6, 2015

@author: scarriere
'''


class Vector2(object):
    '''
    2D Vector, useful to keep a position or to calculate a direction
    '''

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        if isinstance(other, Vector2):
            return self.x == other.x and self.y == other.y
        return NotImplemented
