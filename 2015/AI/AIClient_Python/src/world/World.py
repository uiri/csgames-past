'''
Created on Dec 20, 2014

@author: scarriere
'''
import math
from event.AddPlayerEvent import AddPlayerEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from mathUtils.Vector2 import Vector2
from world.Team import Team
from enum import Enum

class Entity(Enum):
    '''
    An Enum that represent all the entity that can be found in the world
        EMPTY, BOX, CHARACTER, MISSILE
    '''
    EMPTY, BOX, CHARACTER, MISSILE = range(4)

class World(object):
    '''
    Class that contain all the informations about the Teams, Characters and Missiles
        (You can't use any of the functions or variables that start with an "_")
    '''
    _instance = None
    _yourId = 0
    _map = {}
    _gameIsStarted = False
    _gameIsFinished = False
    _teamName = "No name"
    _characterNames = ["No name", "No name"]

    teams = []
    '''
    List of all the teams
        (see :class:`.Team`)
    '''

    def _error(self, message):
        print(message)
    
    def _joinGame(self, yourId):
        self._yourId = yourId
        print("JoinGameEvent: {}".format(self._yourId))
        
        event = AddPlayerEvent(self._teamName, self._characterNames)
        queueController = Singleton(QueueController)
        queueController.outEvents.put(event)
    
    def _sendGameInfos(self, mapWidth, mapHeight, numberOfteam, numberOfCharacter, teamIDs):
        for index in range(0, numberOfteam):
            self.teams.insert(index, Team(teamIDs[index], numberOfCharacter))

    def _startGame(self):
        self._gameIsStarted = True
    
    def _updateBox(self, x, y):
        self._map[x, y] = 1

    def _endGame(self):
        print("End game")
        self._gameIsFinished = True

    def _setNames(self, teamName, characterNames):
        self._teamName = teamName
        self._characterNames = characterNames

    def getTeam(self, teamId) -> Team:
        '''
        Return the team that is associate with the given team Id(:class:`int`)
        or None if not found
        
            Important: the team id are not starting at 0
            
        Exemple::
        
            aTeam = world.getTeam(2)
        '''
        for team in self.teams:
            if team._teamId == teamId:
                return team
        return None
    
    def getMyTeam(self) -> Team:
        '''
        Return the team associate with your id(:class:`int`)
        
        Exemple::

            myTeam = world.getMyTeam()
        '''
        return self.getTeam(self._yourId)

    def getOpponentTeam(self) -> Team:
        '''
        Return the opponent team
        
        Exemple::

            otherTeam = world.getOpponentTeam()
        '''
        for team in self.teams:
            if team._teamId is not self._yourId:
                return team
        return None

    def isBoxAtPosition(self, position) -> bool:
        '''
        Check if there's a box at a certain position(:class:`.Vector2`)
        
        Exemple::

            checkBox = world.isBoxAtPosition(Vector2(5,5))
        '''
        if (position.x, position.y) in self._map:
            return True
        return False
        
    def isCharacterAtposition(self, position) -> bool:
        '''
        Check if there's a character(:class:`.Character`)
        at a certain position(:class:`.Vector2`)
        
        Exemple::

            checkCharacter = world.isCharacterAtposition(Vector2(5,5))
        '''
        for team in self.teams:
            for character in team.characters:
                if character.position == position:
                    return True
        return False

    def isMissileAtPosition(self, position) -> bool:
        '''
        Check if there's a missile(:class:`.Missile`)
        at a certain position(:class:`.Vector2`)
        
        Exemple::

            checkMissile = world.isMissileAtPosition(Vector2(5,5))
        '''
        for team in self.teams:
            for character in team.characters:
                if character.missile.position == position and character.missile.isReady is False:
                    return True
        return False
    
    def whatIsAtPosition(self, position) -> Entity:
        '''
        Return the Entity(:class:`.Entity`)
        at a certain position(:class:`.Vector2`)
        
        Exemple::

            entity = world.whatIsAtPosition(Vector2(5,5))
        '''
        if self.isBoxAtPosition(position):
            return Entity.BOX
        if self.isCharacterAtposition(position):
            return Entity.CHARACTER
        if self.isMissileAtPosition(position):
            return Entity.MISSILE
        return Entity.EMPTY

    def whatIsInTheWay(self, origin: Vector2, direction: Vector2) -> {}:
        '''
        Return a dict[x,y] = mapEntity between a position and a direction
        vector(:class:`.Vector2`)
        
        Exemple::

            objects = world.whatIsInTheWay(origin,
                            MathUtils.getDirectionVector(origin, toPosition))
        '''
        obstacle = {}
        length = int(math.sqrt(direction.x ** 2 + direction.y ** 2))
        if length == 0:
            return obstacle
        unit_direction = Vector2(direction.x/length, direction.y/length)
        if math.sqrt(unit_direction.x**2 + unit_direction.y**2) != 1:
            raise Exception("Non possible path", unit_direction)

        for i in range(1, length - 1):
            currentPos = Vector2(origin.x + unit_direction.x * i, origin.y + unit_direction.y * i)
            obj = self.whatIsAtPosition(currentPos)
            if obj is not Entity.EMPTY:
                obstacle[currentPos.x, currentPos.y] = obj
        return obstacle




