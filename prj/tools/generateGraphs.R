fileNames<-c("heapSortBench","quickSortBench",
      "mergeSortBench")
      
for(fileName in fileNames)
{
  csvFileName<-paste("output",paste(fileName,"csv",sep="."),sep="/")
  epsFileName<-paste("../doc/Sprawozdanie/Wykresy",paste(fileName,"eps",sep="."),sep="/")
  csvData<-read.csv(file=csvFileName, sep=",", header=TRUE)
  postscript(file=epsFileName,width=10,height=5,horizontal=FALSE)
    plot(csvData$Rozmiar,csvData$Czas_us,main=fileName,
    ylab="Czas[us]",xlab="Rozmiar problemu",log="x")
 dev.off()
  
}

  csvData<-read.csv(file="output/quickSortBetterWorstBench.csv", sep=",", header=TRUE)
  csvData2<-read.csv(file="output/quickSortWorseWorstBench.csv", sep=",", header=TRUE)
 postscript(file="../doc/Sprawozdanie/Wykresy/quickSortWorstBench.eps",width=10,height=5,horizontal=FALSE)
  plot(csvData2$Rozmiar,csvData2$Czas_us,main="Worst Quick Sort",
  ylab="Czas[us]",xlab="Rozmiar problemu",col="red")
  points(csvData$Rozmiar,csvData$Czas_us)
 dev.off()