import random
import collections

def GenerateInput(fileName="input.txt",problemSize=[10,100,1000,10000,20000,50000,70000,100000,400000,600000,1000000],repeatNum=5):
    with open(fileName,'w') as file:
            file.write("{0}".format(repeatNum))
            for pSize in problemSize:
                file.write("\n{0}".format(pSize))
                for rNum in range(0,repeatNum):
                    input=collections.deque()
                    for index in range(0,pSize):
                        input.append(random.randint(-10000,10000))
                        file.write("\n{0}".format(input[index]))
                    input=sorted(input)
                    for index in range(0,pSize):
                        file.write("\n{0}".format(input[index]))

def GenerateWorstQuickSort(fileName="input.txt",problemSize=[10,100,1000,5000,10000,15000],
                           repeatNum=5):
    with open(fileName,'w') as file:
            file.write("{0}".format(repeatNum))
            for pSize in problemSize:
                file.write("\n{0}".format(pSize))
                for rNum in range(0,repeatNum):
                    input=collections.deque()
                    for index in range(0,pSize):
                        input.append(random.randint(-10000,10000))
                    input=sorted(input)
                    for index in range(0,pSize):
                        file.write("\n{0}".format(input[index]))
                    for index in range(0,pSize):
                        file.write("\n{0}".format(input[index]))    

if __name__=="__main__":
    GenerateInput(fileName="randomInput.txt")
    GenerateWorstQuickSort(fileName="worstQuickSortInput.txt")

