'''
Created on Dec 17, 2014

@author: scarriere
'''

def Singleton(klass):
    '''
    Call to get the singleton instance of a class
    '''
    if not klass._instance:
        klass._instance = klass()
    return klass._instance