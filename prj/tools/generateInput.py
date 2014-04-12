import random
 
def generateRandomWord():
    word=''
    for i in range(0,random.randint(3,25)):
        word+=random.choice('ABCDEFGHIJKLMNOPQRSTUWXYZabcdefghijklmnopqrstuwxyz')
    return word
 
def generateInput(fileName="input.txt",problemSize=[10,100,1000,5000,10000,15000,25000,33000,50000,65000,80000,100000,250000,500000,1000000],repeatNum=5):
    with open(fileName,'w') as file:
        
        file.write("{0}".format(repeatNum))
        for pSize in problemSize:
            file.write("\n{0}".format(pSize))
            for rNum in range(0,repeatNum):
                lastWord=''
                dict={}
                print('ProblemSize: {0}, Repeat: {1}'.format(pSize,rNum))
                for index in range(0,pSize):
                    word=generateRandomWord()
                    if(index==pSize-1):
                        lastWord=word
                    num=random.randint(0,999999999)
                    dict[word]=num
                    file.write('\n{0} {1}'.format(word,num))
                file.write('\n{0}'.format(dict[lastWord]))

if __name__=="__main__":
    generateInput("inputSmall.txt",problemSize=[10,100,1000,5000,10000,15000,25000,33000,50000,65000,80000,100000,150000])
    generateInput("inputBig.txt",problemSize=[10,100,1000,5000,10000,15000,25000,33000,50000,65000,80000,100000,150000,250000,500000,750000,1000000,1500000])