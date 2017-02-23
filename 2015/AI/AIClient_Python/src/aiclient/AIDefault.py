from enum import Enum
from aiclient.Singleton import Singleton
from world.World import World
from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction


class AIStatus(Enum):
    '''
    Enum created for the AI example
    (Can be deleted)
    '''
    INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT = range(5)


class AIDefault(object):
    '''
    Represents the AI that need to be implemented
    '''
    
    world = Singleton(World)
    '''
    The world singleton needed to get the info on the current state of the world
       (see :class:`.World`)
    '''
    
    aiStatus = AIStatus.INIT
    '''
    The current status of the AI example
    (Can be deleted)
    '''

    position1 = Vector2(0,0)
    position2 = Vector2(7,0)
    position3 = Vector2(0,7)
    position4 = Vector2(7,7)

    def setNames(self):
        '''
        Function call to set the name of the team and characters
        (Cannot be deleted)
        '''
        teamName = "Team python"
        characterNames = ["Python character1", "Python character2"]
        self.world._setNames(teamName, characterNames)

    def tick(self):
        '''
        Function call every 30 ms, this is the starting point for the AI
        (Cannot be deleted)
        '''
        if self.aiStatus == AIStatus.INIT:
            self.initState()
        elif self.aiStatus == AIStatus.LOWER_RIGHT:
            self.lowerRight()
        elif self.aiStatus == AIStatus.LOWER_LEFT:
            self.lowerLeft()
        elif self.aiStatus == AIStatus.UPPER_RIGHT:
            self.upperRight()
        elif self.aiStatus == AIStatus.UPPER_LEFT:
            self.upperLeft()
    
    def initState(self):
        '''
        Function call for the init state of the AI example
        (Can be deleted)
        '''
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        character1.goTo(self.position2)
        character2.goTo(self.position3)
        
        character1.shootMissile(Direction.RIGHT)
        character2.shootMissile(Direction.LEFT)
        
        self.aiStatus = AIStatus.LOWER_RIGHT
    
    def lowerRight(self):
        '''
        Function call for the lowerRight state of the AI example
        (Can be deleted)
        '''
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position2:
            character1.goTo(self.position1)
            character2.goTo(self.position4)

            character1.dropMine()
            character2.dropMine()
            
            character1.shootMissile(Direction.LEFT)
            character2.shootMissile(Direction.RIGHT)
            
            self.aiStatus = AIStatus.LOWER_LEFT
    
    def lowerLeft(self):
        '''
        Function call for the lowerLeft state of the AI example
        (Can be deleted)
        '''
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position1:
            character1.goTo(self.position4)
            character2.goTo(self.position1)
            
            character1.shootMissile(Direction.UP)
            character2.shootMissile(Direction.DOWN)
            
            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.UPPER_RIGHT
    
    def upperRight(self):
        '''
        Function call for the upperRight state of the AI example
        (Can be deleted)
        '''
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position4:
            character1.goTo(self.position3)
            character2.goTo(self.position2)

            character1.shootMissile(Direction.DOWN)
            character2.shootMissile(Direction.UP)

            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.UPPER_LEFT
    
    def upperLeft(self):
        '''
        Function call for the upperLeft state of the AI example
        (Can be deleted)
        '''
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position3:
            character1.goTo(self.position2)
            character2.goTo(self.position3)
            
            character1.shootMissile(Direction.RIGHT)
            character2.shootMissile(Direction.LEFT)
            
            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.LOWER_RIGHT