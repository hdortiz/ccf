#! /bin/bash -f
rm -rf exe_par.sh
rm -rf ccfpar_0*
for line in `cat info`; do
suff=`echo $line | awk -F_ '{print $1}'`
NW=`echo $line | awk -F_ '{print $2}'`
sed "s|NUMBER|$NW|g" ccf_template_par.cc > ccf_$suff.cc
/opt/homebrew/bin/g++-13 -fopenmp ccf_$suff.cc -L/opt/gsl/lib -I/opt/gsl/include -lgsl -lgslcblas -lm -O3 -o ccfpar_$suff
echo "nohup ./ccf_$suff data_$suff.dat > cdata_$suff.txt &" >> exe_par.sh
done
#sed 's|NUMBER|1000|g' ccf_template.cc
