import numpy as np
from Solution import Solution
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
pathsTest = ReadPaths("datt.csv")

#train and predict

solution = Solution()
solution.train(pathsDrunk, pathsSober)


#TEST
if (not solution.evaluate(pathsTest[0])):
	print("your code executed successfuly, and it was right on this sample")
else:
	print("your code executed successfuly, but it was wrong on this sample. This guy is not drunk at all")

