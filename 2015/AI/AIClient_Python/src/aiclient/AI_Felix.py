import copy
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from mathUtils.MathUtils import MathUtils
from world.Character import Character
from world.World import World
from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction
from aiclient.AIDefault import AIDefault

'''
Attack and follow strategy
'''
class MyAI(AIDefault):
    world = Singleton(World)
    otherTeam = None
    oponent1 = None
    oponent2 = None
    tank1 = None
    tank2 = None
    oponentLastPosition1 = None
    oponentLastPosition2 = None
    firstTick = True

    def setNames(self):
        teamName = "Felix team"
        characterNames = ["Batman", "Robin"]
        self.world._setNames(teamName, characterNames)

    def initWorld(self):
        self.tank1 = self.world.getMyTeam().getFirstCharacter()
        self.tank2 = self.world.getMyTeam().getSecondCharacter()
        ':type tank1: Character'
        self.otherTeam = self.world.getOpponentTeam()
        ':type otherTeam: Team'
        self.oponent1 = self.otherTeam.getFirstCharacter()
        self.oponent2 = self.otherTeam.getSecondCharacter()
        ':type oponent: Character'
        self.firstTick = False

    def tick(self):
        if self.firstTick:
            self.initWorld()
    
        if self.isAttackable(self.tank1.getPosition(), self.oponent1.getPosition()) and self.oponent1.isAlive() and self.tank1.isAlive():
            targetDirection = MathUtils.getDirectionFromPositions(self.tank1.getPosition(), self.oponent1.getPosition())
            self.tank1.shootMissile(targetDirection)
        elif self.oponent1.getPosition() != self.oponentLastPosition1:
            self.tank1.goTo(self.oponent1.getPosition())
            self.oponentLastPosition1 = copy.deepcopy(self.oponent1.getPosition())

        if self.isAttackable(self.tank2.getPosition(), self.oponent2.getPosition()) and self.oponent2.isAlive() and self.tank2.isAlive():
            targetDirection = MathUtils.getDirectionFromPositions(self.tank2.getPosition(), self.oponent2.getPosition())
            self.tank2.shootMissile(targetDirection)
        elif self.oponent2.getPosition() != self.oponentLastPosition2:
            self.tank2.goTo(self.oponent2.getPosition())
            self.oponentLastPosition2 = copy.deepcopy(self.oponent2.getPosition())

    def isAttackable(self, fromposition: Vector2, toposition: Vector2):
        ret = fromposition.x == toposition.x or fromposition.y == toposition.y
        if ret is True:
            objects = self.world.whatIsInTheWay(fromposition,
                                                     MathUtils.getDirectionVector(fromposition, toposition))
            ret = len(objects) == 0
        return ret