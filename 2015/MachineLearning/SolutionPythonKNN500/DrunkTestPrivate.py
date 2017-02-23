import random
from math import atan2, pi, tan
#Each person has a starting point and an end point which is random.
class DrunkTestGenerator:
	PathsDrunk = []
	PathsSober = []

	PathLength = 0
	NbPathToGenerate = 6
	#How much can the direction change over to steps.
	MaxDirectionDeltaDrunk = 0.0
	MaxDirectionDeltaSober = 0.0
	MaxDirectionDelta = 0.0
	#How much can the person NOT head in the good direction.
	MaxDestinationDeviation = 0.0

	def __init__(self, pathLength, nbPathToGenerate, maxDirectionDeltaDrunk, maxDirectionDeltaSober):
		self.NbPathToGenerate = nbPathToGenerate
		self.PathLength = pathLength
		self.MaxDirectionDeltaDrunk = maxDirectionDeltaDrunk
		self.MaxDirectionDeltaSober = maxDirectionDeltaSober
		self.PathsDrunk = [None] * self.NbPathToGenerate
		self.PathsSober = [None] * self.NbPathToGenerate
		
	def GenerateData(self):
		for i in range(self.NbPathToGenerate):
		  
			start = random.randint(0,1000) / 10.0
			end = random.randint(0,1000) / 10.0
			self.PathsDrunk[i] = self.GeneratePath(start, end, self.MaxDirectionDeltaDrunk, True)
			#Im getting bad paths from time to time... could not figure out why. sooooooooooo I make a new one when it happens.
			while (not self.ValidatePath(self.PathsDrunk[i])):
				self.PathsDrunk[i] = self.GeneratePath(start, end, self.MaxDirectionDeltaDrunk, True)
				
			start = random.randint(0,1000) / 10.0
			end = random.randint(0,1000) / 10.0
			self.PathsSober[i] = self.GeneratePath(start, end, self.MaxDirectionDeltaSober, True)
			while (not self.ValidatePath(self.PathsSober[i])):
				self.PathsSober[i] = self.GeneratePath(start, end, self.MaxDirectionDeltaSober, True)
			
	def ValidatePath(self, path):
		for i in range(self.PathLength):
			if (path[i] > 100 or path[i] < 0):
				return False
			      
		return True
		  
	def GeneratePath(self, startPoint, endPoint, maxDirectionDelta, shouldAddNoise):
		path = [None] * (self.PathLength + 1) #somehow last point is always bad, so we make one extra, and remove it. please forgive the hack
		path[0] = startPoint
		path[self.PathLength] = endPoint
		
		#Previous direction in rad
		PrevDir = 0.0
		#Current direction in rad
		Dir = 0.0
		for i in range(1, self.PathLength):
			# select drunken path with the following rules :
			#  - Our direction must point toward the objective with a maximum angle of : MaxDestinationDeviation
			#  - Our direction cannot more than MaxDirectionDelta radiants
			#  - We tend to follow our current trend (if we started turning left, we are more likely to turn more left on the next step)
			
			#We have a chance of changing direction completely
			if (shouldAddNoise and i < 80 and random.randint(0,35) == 0):
				endPointNoise = random.randint(0,1000) / 10.0
				endPoint = endPointNoise
				#print endPoint
				path[self.PathLength] = endPoint
				
			#Get current ideal direction (from here to end point)
			dx = self.PathLength  - i 
			dy = endPoint - path[i-1] 
			IdealDirection = atan2(dy,dx)

			#Calculates new random (partially) delta
			PreviousDirectionDelta = Dir - PrevDir

			Sign = -1 if PreviousDirectionDelta < 0 else 1
			Noise = random.randint(int(0), int(maxDirectionDelta * 1000.0)) / 1000.0
			
			
			#Add noise accordingly to our current trend (previous delta).
			NewDelta = Sign* Noise
			
			#Since we cannot deviate to much, recalculate the current maximum angle our path can afford
			PrevDir = Dir
			NewDir = PrevDir + NewDelta
			NewDirINV = PrevDir - NewDelta
			if (NewDelta < 0):
				Dir = NewDirINV if NewDir < IdealDirection - maxDirectionDelta else NewDir
			else :
				Dir = NewDirINV if NewDir > IdealDirection + maxDirectionDelta else NewDir

			path[i] = path[i-1] + tan(Dir)
			
			#print("Delta : " + str(tan(Dir)) + " NewDir :" + str(NewDir) + " IdealDirection : " + str(IdealDirection))

		del path[-1]#shameless hack
		return path
	
