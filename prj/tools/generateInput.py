import random
from collections import deque
import collections

def GenerateInput(fileName="input.txt",problemSize=[10,100,10000,20000,50000,70000,100000],repeatNum=10):
    with open(fileName,'w') as file:
            file.write("{0}".format(repeatNum))
            for pSize in problemSize:
                file.write("\n{0}".format(pSize))
                for rNum in range(0,repeatNum):
                    input=collections.deque()
                    for index in range(0,pSize):
                        input.append(random.randint(-10000,10000))
                        file.write("\n{0}".format(input[index]))
            
if __name__=="__main__":
    GenerateInput()

