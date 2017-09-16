#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isSetSeed = 0;

double uniform0_1(){
    if(!isSetSeed){
        isSetSeed = 1;
        srandom(time(NULL));
    }
    return (double)random()/RAND_MAX;
}

double dart(long n){
    int k = 0;
    for(int i=0; i<n; ++i){
        double x = uniform0_1();
        double y = x;
        if(x*x+y*y<=1)++k;
    }
    return 4*(double)k/n;
}

int main(){
    printf("10  million:%lf\n",dart(10000000));
    printf("100 million:%lf\n",dart(100000000));
    printf("1   billion:%lf\n",dart(1000000000));
    return 0;
}



