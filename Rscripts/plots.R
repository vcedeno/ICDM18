

par(mfrow=c(1,1))

df2 <-read.table("/Users/vcedeno/Desktop/clustering/c/intro2.txt", sep=",")
matplot(t(df2), pch='.',xaxt='n')
axis(1,at=c(1,37,118))

par(mfrow=c(1,1))
df2 <-read.table("/Users/vcedeno/Desktop/ICDM18/landslide/fatalities/FatalitiesByday.txt", sep=",")
matplot(t(df2), pch=20,xaxt='n',ylab = "Fatalities by landslide",cex.lab=1.5, cex.axis=1.5)
axis(1,at=c(1,1238,1314,1316,2801,2824,2973,2974,3503,3586))




for (x in 1:102sum(df2[86,1316:2800]))
row_sub = df2[as.logical(rowSums(df2 != 0)), ]
matplot(t(row_sub), pch='.')

for (x in 1:102)
{
  print(sum(df2[x,3503:3586]))
}

for (x in 1:102)
{
  print(sum(df2[x,1314:1315]))
}

colors=c(rep(2,146),rep(3,1),rep(2,3))
data <-read.table("/Users/vcedeno/Desktop/clustering/c/intro81-160.txt", sep=",")
matplot(t(data), pch='o',xaxt='n')
axis(1,at=c(1,80))


colors=c(rep(2,50),rep(3,50),rep(4,50))
data <-read.table("/Users/vcedeno/Desktop/clustering/c/intro2.txt", sep=",")
matplot(t(data), pch='.',col = colors,xaxt='n')
axis(1,at=c(1,16,26,46,71,81,160))
matplot(t(data), pch='.')

colors=palette(rainbow(15)) 
df2 <-read.table("/Users/vcedeno/Desktop/clustering/c/weekcases.txt", sep=",")
matplot(t(df2), pch=19,col = colors,xaxt='n', xlab='Week',ylab='',cex.lab=3.5, cex.axis=3.5)
axis(1,at=c(1,14,20),cex.axis=3.5)
