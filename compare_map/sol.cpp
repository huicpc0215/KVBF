#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<time.h>
#include<malloc.h>
using namespace std;
#define test_number 1000000
#define query_number 1000000
//int data[test_number];
//int query_data[query_number];
int main(){
    malloc_stats();
    map<int,unsigned char> mp;
    freopen("./test_case.in","r",stdin);
    int key,value;
    //int cnt=0;
    system("pause");
    while(scanf("%d %d",&key,&value)!=EOF){
        mp[key]=(unsigned char)value;
    //    data[cnt++]=key;
    }
    malloc_stats();
    //for(int i=0;i<query_number;i++){
    //    query_data[i]=(rand()%1000*rand()%1000+rand()%1000)%test_number;
    //}
    //malloc_stats();
    //clock_t start,end;
    //int answer;
    //start=clock();
    //for(int i=0;i<query_number;i++){
    //    answer=mp[ query_data[i] ];
    //}
    //end=clock();
    //double duration;
    //duration = (double)(end-start)/CLOCKS_PER_SEC;
    //printf("using %lf seconds to query %d items\n",duration,query_number);
    while(1);
    return 0;
}
