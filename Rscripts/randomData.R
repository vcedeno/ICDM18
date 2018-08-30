data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn.csv", sep=",")
data <- data[order(data$V1),] 
optimal=94476.703125
matplot(seq(1:length(data)),data,  type = "l",ylim=range(1:max(data)))
points(optimal, col="red", pch=19)

data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn.csv", sep=",")
data <- data[order(data$V1),] 
optimal=94476.703125
matplot(rep(1,length(data)),data/100000,  pch = ".",ylim=range(0.9:3),xlim=(range(1:1)))
points(optimal/100000, col="red", pch='o')

boxplot(data/100000,ylim=c(0.9,3))
points(optimal/100000, col="red", pch='o')

data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn.csv", sep=",")
b0=data.frame(as.numeric(data$V1))
colnames(b0) <- c("count")
b0["data"] <- "0"
data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn1.csv", sep=",")
b1=data.frame(as.numeric(data$V1))
colnames(b1) <- c("count")
b1["data"] <- "1"
data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn2.csv", sep=",")
b2=data.frame(as.numeric(data$V1))
colnames(b2) <- c("count")
b2["data"] <- "2"
data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn3.csv", sep=",")
b3=data.frame(as.numeric(data$V1))
colnames(b3) <- c("count")
b3["data"] <- "3"
data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn4.csv", sep=",")
b4=data.frame(as.numeric(data$V1))
colnames(b4) <- c("count")
b4["data"] <- "4"
data <-read.table("/Users/vcedeno/Desktop/KDD18/scripts/noiseData/timessyn5.csv", sep=",")
b5=data.frame(as.numeric(data$V1))
colnames(b5) <- c("count")
b5["data"] <- "5"
b=rbind(b0,b1,b2,b3,b4,b5)

ggplot() + 
  geom_boxplot(data = b, aes(x = factor(data), y= count/100000)) +
  geom_point(data = data.frame(x = factor(c(0,1,2,3,4,5)), y = c(0.94,0.97,0.99,1,1.02,1.03)),
             aes(x=x, y=y),
             color = 'red')+ 
  scale_x_discrete(name="Noise %",labels=c("M1:0","M2:0.1","M3:0.2","M4:0.3","M5:0.4","M6:0.5"))+ 
  ylab("Cost of data model x10^5")+
theme(axis.text = element_text(size = 30)) +
theme(axis.title = element_text(size = 30))



  