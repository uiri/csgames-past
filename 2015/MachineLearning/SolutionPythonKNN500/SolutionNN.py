import numpy as np
from pybrain.tools.shortcuts import buildNetwork
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
import matplotlib.pyplot as pyplot
#data length is always 100

LENGTH = 100

class Solution:
	net = None
	#will be called once with two datasets of 500 paths. Each path contains 100 positions.
	def train(self, samplesDrunk, samplesSober):
		#inaoin
		print("BUILDING NETWORK\n")
		#training
		self.net = buildNetwork(LENGTH - 1, 50, 25, 1)
		ds = SupervisedDataSet(LENGTH - 1, 1)

		print("CREATING DATASET\n")
		for i in range(50):
			ds.addSample(self.ConvertToSpeeds(samplesDrunk[i]), 1)
		for i in range(50):
			ds.addSample(self.ConvertToSpeeds(samplesSober[i]), -1)

		print("TRAINING\n")
		trainer = BackpropTrainer(self.net, ds)
		trainer.trainUntilConvergence( verbose = True, validationProportion = 0.15, maxEpochs = 1000, continueEpochs = 10 )

	#return true if you give it a drunk guy's path, false otherwise
	#Will be called once automatically when you run SolutionTest after train, so you know it is called correctly and work as expected.
	# we STRONGLY suggest you to test more than one sample to know if your suggestions work ;)
	def evaluate(self, sample):
		val = self.net.activate(self.ConvertToSpeeds(sample))
		print val
		return  val > 0
	

	def ConvertToSpeeds(self, path):
		speeds = [0] * (len(path) - 1)
		for i in range(len(path) - 1):
			speeds[i] = path[i+1]-path[i]
		return speeds


