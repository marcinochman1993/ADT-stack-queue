fileNames<-c("LQueue","VQueueDouble",
      "VQueueInc","LStack",
      "VStackDouble","VStackInc")
      
for(fileName in fileNames)
{
  csvFileName<-paste("wyniki",paste(fileName,"csv",sep="."),sep="/")
  epsFileName<-paste("../doc/Sprawozdanie/Wykresy",paste(fileName,"eps",sep="."),sep="/")
  csvData<-read.csv(file=csvFileName, sep=",", header=TRUE)
  postscript(file=epsFileName,width=10,height=5,horizontal=FALSE)
  plot(csvData$Rozmiar,csvData$Czas_us,main=fileName,
    ylab="Czas[us]",xlab="Rozmiar problemu")
  dev.off()
}