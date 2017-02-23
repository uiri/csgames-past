'''
Created on Dec 20, 2014

@author: samuel
'''
from world.Character import Character
from mathUtils.Vector2 import Vector2

class Team(object):
    '''
    Class that contain all the informations about the Team
        (You can't use any of the functions or variables that start with an "_")
    '''
    def __init__(self, teamId, numberOfCharacter):
        self._teamId = teamId
        self.characters = []
        '''
        List of all the characters
            (see :class:`.Character`)
            
            Note: The index of the characters start at 0
            and the id of the character is the same as his index
        '''
        for index in range(0, numberOfCharacter):
            self.characters.insert(index, Character(index, Vector2(0,0)))
    
    def getFirstCharacter(self):
        '''
        Return the first character(:class:`.Character`) of the team
            
        Exemple::
        
            aCharacter = aTeam.getFirstCharacter()
        '''
        return self.characters[0]
    
    def getSecondCharacter(self):
        '''
        Return the second character(:class:`.Character`) of the team
            
        Exemple::
        
            aCharacter = aTeam.getSecondCharacter()
        '''
        return self.characters[1]