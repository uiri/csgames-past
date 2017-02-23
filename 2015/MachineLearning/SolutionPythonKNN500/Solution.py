import numpy as np
import math
#data length is always 100

LENGTH = 100
LENGTH_EVAL = 10
class Solution:
	dataS = []
	dataD = []
	#will be called once with two datasets of 500 paths. Each path contains 100 positions.
	def train(self, samplesDrunk, samplesSober):
		
		for i in range(len(samplesDrunk)):
			self.dataS.append(self.ConvertToSpeeds(samplesSober[i]))
			self.dataD.append(self.ConvertToSpeeds(samplesDrunk[i]))

	#return true if you give it a drunk guy's path, false otherwise
	#Will be called once automatically when you run SolutionTest after train, so you know it is called correctly and work as expected.
	# we STRONGLY suggest you to test more than one sample to know if your suggestions work ;)
	def evaluate(self, sample):
		speeds = self.ConvertToSpeeds(sample)
		distS = []
		for i in range(len(self.dataS)):
			distS.append(self.ComputeDistance(speeds, self.dataS[i]))
		distD = []
		for i in range(len(self.dataD)):
			distD.append(self.ComputeDistance(speeds, self.dataD[i]))
		distS.sort()
		distD.sort()
		votes = 0
		for i in range(1):
			if (distS[0] > distD[0]):
				votes = votes + 1
				distD.pop(0)
			else:
				votes = votes - 1
				distS.pop(0)
		return  votes > 0

	def ConvertToSpeeds(self, path):
		speeds = [0] * (len(path) - 1)
		for i in range(len(path) - 1):
			speeds[i] = path[i+1]-path[i]
		return speeds

	def ComputeDistance(self, samples1, samples2):
		dist = 0.0
		for i in range(LENGTH_EVAL):
			dist += math.fabs(samples1[i] - samples2[i])
		return dist


