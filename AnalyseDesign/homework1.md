# 第一次题目

![](./算法设计作业1.png)

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

## Ex P36

如下是估计一个集合的势的代码：
```c
SetCount (X) {
		k ← 0; S ← Ф;
		a ← uniform(X);
		do {
			k++;
			S ← S∪{a}; a ← uniform(X);
		} while (a ∉ S)
		return 2k2/π
	}

```
用上述算法，估计整数子集1~n的大小，并分析n对估计值的影响。

用该算法估计C语言中ramdom()函数产生的最大值。

```c++
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define PI 3.1415926

using namespace std;

long int uniform(){
    return random();
}



double SetCount(){
    double k = 0;
    vector<int> S;
    long int a = uniform();
    bool isChecked = false;
    do{
        k++;
        S.push_back(a);
        a = uniform();
        vector<int>::iterator iter = std::find(S.begin(),S.end(),a);
        if(iter!=S.end()){
            isChecked = true;
        }
    }while(!isChecked);
    return 2*k*k/PI;
}

int main(){
    srandom(time(NULL));
    printf("RAND_MAX:%d\n",RAND_MAX);
    printf("Evaluate:%.0lf\n",SetCount());
    return 0;
}
```
实验结果：
#### 第一次：
```
RAND_MAX:2147483647
Evaluate:37951351
```

#### 第二次：
```
RAND_MAX:2147483647
Evaluate:2915055392
```

#### 第三次：
```
RAND_MAX:2147483647
Evaluate:3683311513
```

#### 第四次：
```
RAND_MAX:2147483647
Evaluate:4683398122
```

通过多次计算求平均值：

#### 100次后求平均值：
```
RAND_MAX:2147483647
Evaluate:2720385488
```
误差：26.677%

#### 1000次后求平均值后：
```
RAND_MAX:2147483647
Evaluate:2666816931
```
误差：24.183%

误差随着次数的增加，会减小，但还是在20%以上；

## Ex P54
![](./P54Ex.png)

分析dlogRH的工作原理,指出该算法中相应的u(u为使用shewood算法进行随机化的函数)和v(v为将结果转换回去的函数)

解答：
![](./P54Answer.png)

其中：
```
b ← ModularExponent(g, r, p);
c ← ba mod p;
为u函数

(y-r) mod (p-1); 
为v函数
```

## Ex67 搜索有序表

设x≥val[i]且x在表中,则从位置i开始查找x的算法为
```
Search(x, i) { //仍可改进
    while x > val[i] do
    i ← ptr[i];
    return i;
}

A(x) {
    return Search(x, head);
}

B(x) { //设x在val[1..n]中
    i ← head;
    max ← val[i]; // max初值是表val中最小值
    for j ← 1 to ⌊√n⌋{ 
        y ← val[ j ];
        // 的最大整数y相应的下标
        if max < y ≤x then {
            i ← j;
            max ← y;
        } //endif
    } // endfor
    return Search(x, i); // 从y开始继续搜索
}


D(x) {
    i ← uniform(1..n);
    y ← val[i];
    case {
    x < y:return Search(x, head); // case1
    x > y:return Search(x, ptr[i]); //case2
    otherwise: return i; // case3, x = y
    }
}
```
**Ex. 写一Sherwood算法C,与算法A, B, D比较,
给出实验结果。**

代码构建：

一个用于创建静态链表的类：
```py
class StaticChain:
    def __init__(self, size):
        self.size = size;
        self.val = [0 for i in range(size)];
        self.ptr = [i+1 for i in range(size)];
        self.ptr[size-1] = -1;
        #使用了的空间的头指针
        self.head = -1;
        #未使用的空间的头指针
        self.uhead = 0;
        self.len = 0;

    def len(self):
        return self.len;

    def assignPos(self):
        if(self.uhead==-1):
            return -1;
        p = self.uhead;
        self.uhead = self.ptr[self.uhead];
        return p;

    def reclaimPos(self,p):
        self.ptr[p] = self.uhead;
        self.uhead = p;

    def insert(self, v):
        newPos = self.assignPos();
        if(newPos==-1):
            print("chain has full");
            return self;
        if(self.head==-1 or v <= self.val[self.head]):
            self.ptr[newPos] = self.head;
            self.head = newPos;
            self.val[self.head] = v;
            return;
        p = self.head;
        while(self.ptr[p]!=-1 and self.val[self.ptr[p]]<v):
            p = self.ptr[p];
        self.ptr[newPos] = self.ptr[p];
        self.ptr[p] = newPos;
        self.val[newPos] = v;
        return self;

    def pushFront(self,v):
        newPos = self.assignPos();
        if(newPos==-1):
            print("chain has full");
            return;
        self.ptr[newPos] = self.head;
        self.head = newPos;
        self.val[self.head] = v;

    def popFront(self):
        if(self.head==-1):
            print("chain has empty");
            return;
        v = self.val[self.head];
        tpos = self.head;
        self.head = self.ptr[self.head];
        self.reclaimPos(tpos);

    def front(self):
        if(self.head==-1):
            print("chain has empty");
            return;
        return self.val[self.head];

    def showChain(self):
        p = self.head;
        while(p!=-1):
            print(self.val[p],end=",");
            p = self.ptr[p];
        print();
```
A、B、C、D 4种搜索方法的定义与测试：
```py
from datetime import datetime
import random
import math

chainLen = 10000;
sc = StaticChain(chainLen);

for i in range(chainLen):
    sc.insert(random.randint(0,10*chainLen));

def search(x, i):
    while i!=-1 and x > sc.val[i]:
        i = sc.ptr[i];
    return i;

def A(x):
    return search(x,sc.head);

def B(x):
    i = sc.head;
    maxv = sc.val[i];
    tp = int(math.sqrt(chainLen));
    for j in range(0,tp):
        y = sc.val[j];
        if maxv < y and y <= x :
            i = j
            maxv = y;
    return search(x, i);

def C(x):
    r = random.randint(1,chainLen-1);
    i = sc.head;
    maxv = sc.val[i];
    tp = int(math.sqrt(chainLen));
    for j in range(r,r+tp):
        if(j >= chainLen):
            break;
        y = sc.val[j];
        if maxv < y and y <= x :
            i = j;
            maxv = y;
    return search(x, i);

def D(x):
    i = random.randint(0,chainLen-1);
    y = sc.val[i];
    if x < y:
        return search(x, sc.head);
    elif x > y:
        return search(x,sc.ptr[i]);
    else:
        return i;

testv = sc.val[random.randint(0,chainLen-1)];
print("testv : %d" %testv);

def testFunc(func):
    print("----test %s----" %func.__name__);
    t1 = datetime.now();
    index = func(testv);
    delta = datetime.now()-t1;
    print("index:%d, delta:%s, value:%d" %(index,str(delta),sc.val[index]));
    print();

testFunc(A);
testFunc(B);
testFunc(C);
testFunc(D);
```

测试结果1：
```
testv : 75776
----test A----
index:7246, delta:0:00:00.001377, value:75776

----test B----
index:7246, delta:0:00:00.000085, value:75776

----test C----
index:7246, delta:0:00:00.000077, value:75776

----test D----
index:7246, delta:0:00:00.000827, value:75776
```
测试结果2：
```
testv : 30652
----test A----
index:9876, delta:0:00:00.000597, value:30652

----test B----
index:9876, delta:0:00:00.000040, value:30652

----test C----
index:9876, delta:0:00:00.000059, value:30652

----test D----
index:9876, delta:0:00:00.000586, value:30652
```
**总结**：A、D的运行时间大致相等，B、C的运行时间大致相等,B、C的运行效率要高于A、D的运行效率；


## EX Page 77
**证明：当放置(k+1)th 皇后时，若有多个位置是开放的，则算法QueensLV选中其中任一位置的概率是相同的；**

证明：
```
设有c个位置是开放的，将这c个位置进行编号，为1、2、... 、 c；

则对于其中编号为a的元素，其被选中的条件是：
在计算出的开放个数为a时，uniform(1..a)=1，概率为：1/a；
在计算出的开放个数为a+1时，uniform(1..a+1)!=1，概率为：a/a+1；
...
在计算出的开放个数为c时，uniform(1..c)!=1,概率为：c-1/c；
故，编号为a的元素被选中的概率为：
(1/a)*(a/(a+1))*((a+1)/(a+2))*...*((c-1)/c) = 1/c；
可见，对于每个编号，其选中的概率与其位置无关，都为1/c；
证明完毕！
```

## EX Page 83

**写出一算法，求n=12～20时，最优的StepVagas值；**
```py
#!/usr/bin/python3
import sys
import random
from datetime import datetime

# Lv算法和回溯算法结合
def LvBtSolve(n, stepVegas):
    trys = [-1 for i in range(n)];
    col = []; 
    diag45 = []; 
    diag135 = []; 
    k = 0;
    while(True):
        nb = 0;
        if(stepVegas==0):
            nb = 1;
            break;
        for i in range(n):
            if not(i in col) and not(i-k in diag45) and not(i+k in diag135):
                nb += 1;
                if random.randint(1,nb)==1:
                    j = i;
        if(nb > 0): 
            trys[k] = j;
            col.append(j);
            diag45.append(j-k);
            diag135.append(j+k);
            k += 1;
        if(nb==0 or k==stepVegas):
            break;
    if (nb>0):
        success = backtrace(n, k, trys, col, diag45, diag135);
    else:
        success = False;
    return success, trys;

def backtrace(n, k, trys, col, diag45, diag135):
    tk = k;
    while 1:
        if(tk < k or tk == n):
            break;
        i = trys[tk] + 1;
        while i < n:
            if not(i in col) and not(i-tk in diag45) and not(i+tk in diag135):
                trys[tk] = i;
                col.append(i);
                diag45.append(i-tk);
                diag135.append(i+tk);
                tk += 1;
                break;
            else:
                i += 1;
        if(i==n):
            trys[tk] = -1;
            tk -= 1;
            del col[col.index(trys[tk])];
            del diag45[diag45.index(trys[tk]-tk)];
            del diag135[diag135.index(trys[tk]+tk)];
    if(tk==n):
        return True;
    else:
        return False;

def obstinateLvBt(n, stepVegas):
    while(1):
        success,trys = LvBtSolve(n, stepVegas);
        if(success):
            break;

def testBestStepVegas(n):
    bestStep = -1;
    for i in range(1,n+1):
        tBegin = datetime.now();
        obstinateLvBt(n, i);
        tEnd = datetime.now();
        deltaTime = tEnd - tBegin;
        if(bestStep==-1 or bestDelta>deltaTime):
            bestStep = i;
            bestDelta = deltaTime;
    return bestStep,deltaTime;

for i in range(12,21):
    bestStep,deltaTime = testBestStepVegas(i);
    print("Queens:%d, bestSteps:%d, delta:%s" %(i,bestStep,deltaTime));
```
第一次测试的结果为：
```
Queens:12, bestSteps:2, delta:0:00:00.000464
Queens:13, bestSteps:4, delta:0:00:00.000324
Queens:14, bestSteps:7, delta:0:00:00.019534
Queens:15, bestSteps:9, delta:0:00:00.010096
Queens:16, bestSteps:5, delta:0:00:00.013930
Queens:17, bestSteps:10, delta:0:00:00.008935
Queens:18, bestSteps:6, delta:0:00:00.003799
Queens:19, bestSteps:7, delta:0:00:00.020576
Queens:20, bestSteps:13, delta:0:00:00.004685
```

第二次的测试结果为：
```
Queens:12, bestSteps:8, delta:0:00:00.000104
Queens:13, bestSteps:10, delta:0:00:00.001582
Queens:14, bestSteps:2, delta:0:00:00.000682
Queens:15, bestSteps:9, delta:0:00:00.002025
Queens:16, bestSteps:10, delta:0:00:00.000321
Queens:17, bestSteps:11, delta:0:00:00.001399
Queens:18, bestSteps:4, delta:0:00:00.001892
Queens:19, bestSteps:11, delta:0:00:00.007513
Queens:20, bestSteps:7, delta:0:00:00.001216
```
可见，一次测试的结果通常不准确；

通过最后的测试代码修改为通过多次测试求平均值：
```py
for i in range(12,21):
    repeatTimes = 100;
    tsum = 0;
    for j in range(0,repeatTimes):
        bestStep,deltaTime = testBestStepVegas(i);
        tsum += bestStep;
    print("Queens:%d, bestSteps:%.2f" %(i,tsum/repeatTimes));
```

测试100次，求最佳的步数的平均值，得到如下结果：
```
Queens:12, bestSteps:6.45
Queens:13, bestSteps:6.07
Queens:14, bestSteps:6.81
Queens:15, bestSteps:7.50
Queens:16, bestSteps:8.41
Queens:17, bestSteps:8.80
Queens:18, bestSteps:8.82
Queens:19, bestSteps:9.79
Queens:20, bestSteps:10.74
```
可以看出，求n皇后问题，使用LV算法放置n/2步左右，效率最高；
