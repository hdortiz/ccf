a <- read.table('datatest.dat')
a <- as.matrix(a)

j <- 54
x <- ccf(a[1,],a[j,])
x <- ccf(a[1,],a[j,],lag=512/2)
max(x$acf)

xc <- fft(fft(a[1,])*Conj(fft(a[j,])),inverse=TRUE)

par(mfrow=c(2,1))
plot(x$acf,type="l")
plot(Re(xc),type="l")


Edge effects start affecting so its recomendable to pad with zeros to the input data. 