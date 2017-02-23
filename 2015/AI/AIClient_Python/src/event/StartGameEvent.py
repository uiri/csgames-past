'''
Created on Dec 20, 2014

@author: scarriere
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class StartGameEvent(IngoingEvent):

    def __init__(self):
        pass

    def fillArguments(self, string):
        pass
            
    def execute(self):
        world = Singleton(World)
        world._startGame()