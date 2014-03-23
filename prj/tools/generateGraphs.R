fileNames<-c("heapSortBench","quickSortBench",
      "mergeSortBench","quickSortWorstBench")
      
for(fileName in fileNames)
{
  csvFileName<-paste("output",paste(fileName,"csv",sep="."),sep="/")
  epsFileName<-paste("../doc/Sprawozdanie/Wykresy",paste(fileName,"eps",sep="."),sep="/")
  csvData<-read.csv(file=csvFileName, sep=",", header=TRUE)
  postscript(file=epsFileName,width=10,height=5,horizontal=FALSE)
  if(fileName=="quickSortWorstBench")
  plot(csvData$Rozmiar,csvData$Czas_us,main=fileName,
    ylab="Czas[us]",xlab="Rozmiar problemu")
  else
    plot(csvData$Rozmiar,csvData$Czas_us,main=fileName,
    ylab="Czas[us]",xlab="Rozmiar problemu",log="x")
  dev.off()
}