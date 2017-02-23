from DrunkTestPrivate import DrunkTestGenerator
import dateutil
import matplotlib.pyplot as pyplot

def WritePathsToFile(paths, csvFile):
	
	for i in range(len(paths)):
		for j in range(len(paths[i])):
			csvFile.write(str(paths[i][j]) + ",")
		csvFile.write(bytes("\n"))
	

Generator = DrunkTestGenerator(100,500, 0.3, 0.07, 0.03)

Generator.GenerateData()
csvFileS = open("dats.csv", 'wb')
csvFileD = open("datd.csv", 'wb')

WritePathsToFile(Generator.PathsDrunk, csvFileD)
WritePathsToFile(Generator.PathsSober, csvFileS)
csvFileD.close()
csvFileS.close()

for i in range(len(Generator.PathsDrunk)):
	pyplot.plot(range(len(Generator.PathsDrunk[i])), Generator.PathsDrunk[i], "ro-",range(len(Generator.PathsDrunk[i])), Generator.PathsSober[i], "bo-")
pyplot.show()

