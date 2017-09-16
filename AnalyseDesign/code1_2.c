#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int isSetSeed = 0;

double uniform0_1(){
    if(!isSetSeed){
        isSetSeed = 1;
        srandom(time(NULL));
    }
    return (double)random()/RAND_MAX;
}

double calcPi(long n){
    int k = 0;
    for(long i=0; i<n; ++i){
        double x = uniform0_1();
        double y = uniform0_1();
        if(sqrt(1-x*x) >= y){
            ++k;
        }
    }
    return (double)k*4/n;
}

int main(){
	printf("10  million:%lf\n",calcPi(10000000));
    printf("100 million:%lf\n",calcPi(100000000));
    printf("1   billion:%lf\n",calcPi(1000000000));
    return 0;
}



