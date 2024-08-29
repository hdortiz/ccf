make:
	g++ ccf_fft.cc -L/opt/gsl/lib -I/opt/gsl/include -lgsl -lgslcblas -lm -O3 -o ccf

clean:
	rm -rf ccf