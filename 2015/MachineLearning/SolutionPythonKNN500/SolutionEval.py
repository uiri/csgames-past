import numpy as np
from Solution import Solution
from DrunkTestPrivate import DrunkTestGenerator
#import matplotlib.pyplot as pyplot
import csv
#length of a path
LENGTH = 100

#read data from file.

def ReadPaths(fileName):
	paths = []
	with open(fileName, 'rb') as csvfile:
		pathreader = csv.reader(csvfile, delimiter=',')
		for row in pathreader:
			path = []
			for pos in row:
				if (pos.strip("'\"") != ""):
					path.append(float(pos.strip("'\"")))

			paths.append(path)
	
	return paths

pathsDrunk = ReadPaths("datd.csv")
pathsSober = ReadPaths("dats.csv")
pathsDrunkT = ReadPaths("datdt.csv")
pathsSoberT = ReadPaths("datst.csv")
#train and predict

solution = Solution()
solution.train(pathsDrunk, pathsSober)



print("TESTING\n")
#TEST
good = 0
bad = 0
for i in range(len(pathsDrunkT)):
	if (solution.evaluate(pathsDrunkT[i])):
		#pyplot.plot(range(len(GeneratorTest.PathsDrunk[i])), GeneratorTest.PathsDrunk[i], "r-")
		good += 1
	else:
		#pyplot.plot(range(len(GeneratorTest.PathsDrunk[i])), GeneratorTest.PathsDrunk[i], "ro-")
		#print "miss"
		bad += 1

for i in range(len(pathsSoberT)):
	if (solution.evaluate(pathsSoberT[i])):
		#pyplot.plot(range(len(GeneratorTest.PathsSober[i])), GeneratorTest.PathsSober[i], "bo-")
		#print "false positive"
		bad += 1
	else:
		good += 1
		#pyplot.plot(range(len(GeneratorTest.PathsSober[i])), GeneratorTest.PathsSober[i], "b-")

print good
print bad
print(str((float(good) / float(good + bad)) * 100) + "% efficiency")

#pyplot.show()

