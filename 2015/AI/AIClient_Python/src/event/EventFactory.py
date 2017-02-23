'''
Created on Dec 16, 2014

@author: scarriere
'''
from event.JoinGameEvent import JoinGameEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from event.StartGameEvent import StartGameEvent
from event.SendGameInfosEvent import SendGameInfosEvent
from event.UpdateCharacterEvent import UpdateCharacterEvent
from event.MineHitEvent import MineHitEvent
from event.MissileHitEvent import MissileHitEvent
from event.UpdateMissileEvent import UpdateMissileEvent
from event.UpdateBoxEvent import UpdateBoxEvent
from event.EndGameEvent import EndGameEvent

class EventFactory(object):
    @staticmethod
    def generateEvent(message):
        messageParts = message.split(":", 1)
        event = EventFactory.createEvent(messageParts[0])
        if event != None:
            event.fillArguments(messageParts[1])
            queueController = Singleton(QueueController)
            queueController.addIngoingEvent(event)
    
    @staticmethod
    def createEvent(eventType):
        if eventType == "JoinGame":
            return JoinGameEvent()
        elif eventType == "StartGame":
            return StartGameEvent()
        elif eventType == "SendGameInfos":
            return SendGameInfosEvent()
        elif eventType == "UpdateCharacter":
            return UpdateCharacterEvent()
        elif eventType == "MineHit":
            return MineHitEvent()
        elif eventType == "MissileHit":
            return MissileHitEvent()
        elif eventType == "UpdateMissile":
            return UpdateMissileEvent()
        elif eventType == "UpdateBox":
            return UpdateBoxEvent()
        elif eventType == "EndGame":
            return EndGameEvent()
        return None