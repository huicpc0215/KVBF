#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<cmath>
#include<time.h>
#include<algorithm>
using namespace std;
#define generation_number 1000000
set<int> s;
unsigned char value_range[8];
int main(){
    freopen("test_case.in","w",stdout);
    s.clear();
    value_range[0]=1;
    for(int i=0;i<7;i++)
        value_range[i+1]=value_range[i]*2;
    //for(int i=0;i<8;i++)
    //    printf("value=%d\n",(unsigned int)value_range[i]);
    for(int i=0;i<generation_number;i++){
        int tmp=rand()%1000*rand()%1000+rand();
        while(s.find(tmp)!=s.end())
            tmp=rand()%1000*rand()%1000+rand();
        s.insert(tmp);
        int v=rand()%8;
        printf("%d %d\n",tmp,value_range[v]);
    }
    return 0;
}
