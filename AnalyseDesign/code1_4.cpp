#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

#define PI 3.1415926

using namespace std;

long int uniform(){
    return random()%(RAND_MAX/4);
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
    printf("RAND_MAX:%d\n",RAND_MAX/4);
    printf("Evaluate:%.0lf\n",SetCount());
    return 0;
}



