#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int isSetSeed = 0;

double uniform(double min, double max){
    if(!isSetSeed){
        isSetSeed = 1;
        srandom(time(NULL));
    }
    return min+(max-min)*((double)random()/RAND_MAX);
}

//待积分的函数
double f(double x){
    return 1-x*x;
}

//f:带积分函数
//[a,b]:积分区间
//[c,d]:积分区间对应的值域
//n:投标次数
double integrate(double (*f)(double), double a, double b,
        double c, double d,long n){
    int k = 0;
    for(long i=0; i<n; ++i){
        double x = uniform(a,b);
        double y = uniform(c,d);
        double fx = f(x);
        if(fx>y){
            ++k;
        }
    }

    return ((double)k/n*(d-c)+c)*(b-a);
}

int main(){
    printf("10 million:%lf\n",integrate(f,0,2,-3,1,10000000));
    return 0;
}


