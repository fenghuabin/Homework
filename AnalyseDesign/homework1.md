# 第一次题目

![](/home/hbfeng/Document/LecturePPT/AnalyseDesign/算法设计作业1.png)

Ex.1 若将 y=uniform(0,1)修改为y=x，则上述算法的估计值是：2×√2

代码段：
```c
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
```

实验结果：
```
10  million:2.827990
100 million:2.828244
1   billion:2.828429
```
实际值为：2.8284271247461900976

Ex.2 
代码段：
```c
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
```
实验结果：
```
10  million:3.141745
100 million:3.141441
1   billion:3.141541
```

Ex3.代码段：
```c
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
```
结果：
```
10 million:-0.665241
```









