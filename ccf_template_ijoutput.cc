#include <iterator>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_statistics_double.h>

using namespace std;

vector<double> dot(vector<double>&d1,vector<double>&d2){

int i,n;

n=d1.size();

double sd1 = gsl_stats_variance(&d1[0],1,n);
double sd2 = gsl_stats_variance(&d2[0],1,n);
sd1 = sd1*(n-1);
sd2 = sd2*(n-1);
double de = sqrt(sd1*sd2);

gsl_fft_real_radix2_transform (&d1[0], 1,d1.size());
gsl_fft_real_radix2_transform (&d2[0], 1,d2.size());
n=d1.size();

        vector<double> c(n);
        c[0] = d1[0]*d2[0];
        c[n/2] = d1[n/2]*d2[n/2];
        for (i=1; i<n/2; ++i) {
            c[i] = d1[i]*d2[i] + d1[n-i]*d2[n-i];
            c[n-i] = d1[n-i]*d2[i] - d1[i]*d2[n-i];
        }

gsl_fft_halfcomplex_radix2_inverse(&c[0], 1, c.size());
double mc = gsl_stats_max(&c[0],1,n);
double ml = gsl_stats_max_index (&c[0],1,n);
vector<double> m (2);
m[0]=mc/de;
if (ml > n/2){m[1] = ml-n;}
else {m[1]=ml;}

return m;

}

vector<double> seq (double initial, double final, double step)
{
int i, n;
if ( step == 0){
vector<double> r (1);
r[0]=0;
return r;
}
else {
n=floor((final-initial)/step)+1;
vector<double> r (n);
r[0]=initial;
for (i=1;i<n;i++){
r[i]=r[i-1]+step;
}
return r;
}
}



int main(int argc, char *argv[])
{
int n, i, j, sum;
ifstream delay(argv[1]);
istream_iterator<double> s(delay), e;
vector<double> d(s, e);
n=512;
sum=0;
vector<double> c (2);
vector<double> index;
index=seq(0,d.size(),n);
    
for (j=0;j<NUMBER;j++){
for (i=j;i<NUMBER;i++){
vector<double> d1(&d[index[j]],&d[index[j+1]]);
vector<double> d2(&d[index[i]],&d[index[i+1]]);
c = dot(d1,d2); 
sum = sum+1;
printf("%0d %0d %0d %.5f %.0f \n",sum,j,i,c[0],c[1]);
}
}
return 0;
}



