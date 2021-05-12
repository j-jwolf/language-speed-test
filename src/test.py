import sys
import time
import os

def read(fn):
	with open(fn) as f:
		data = f.readlines()
	return data
def write(fn, data):
	f = open(fn, "w")
	for line in data:
		f.write(line)
	f.close()
	return
def consoleOut(fn):
	command = "IF EXIST "+fn+" ( rm "+fn+" )"
	res = os.system(command)
	if(res != 0): print("PROCESS RETURNED "+res)
	return
def main():
	start = time.time()
	fn = sys.argv[1]
	destination = sys.argv[2]
	testCount = int(sys.argv[3])
	destroyAfter = int(sys.argv[4])
	print("new file name: ", destination, end="\n")
	print("Starting test, reading file ", fn, " ", testCount, " times\n-----------------------", end="\n")
	for i in range(testCount):
		data = read(fn)
		write(destination, data)
		if(destroyAfter):
			consoleOut(destination)
	end = time.time()
	print("Time elapsed: ", (end-start))
	return

main()
