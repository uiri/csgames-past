'''
Created on Dec 17, 2014

@author: scarriere
'''

import time
from event.EventController import EventController
from network.NetworkController import NetworkController
from aiclient.Singleton import Singleton
from world.World import World
from aiclient.AI_Felix import MyAI

eventController = Singleton(EventController)
world = Singleton(World)
netController = Singleton(NetworkController)

ai = MyAI()
'''
If your create a new class for the ai, replace it here
'''

class Client(object):
    '''
    Main class (Any changes made to this class won't be taken)
    '''

    @staticmethod
    def main():
        '''
        Main loop
        '''
        ai.setNames()
        netController.init()

        while netController.connected and not world._gameIsFinished:
            eventController.executeIngoingEvents()

            if world._gameIsStarted:
                ai.tick()

            netController.executeOutgoingEvents()
            time.sleep(0.033)

        netController.closeConnection()
        print(" - end - ")
  
Client.main()
