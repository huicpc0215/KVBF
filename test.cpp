#include<iostream>
#include<time.h>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cmath>
#include "TimeBloomFilter.h"

using namespace std;

#define QUERY_TIME 1000000
#define TEST_NUMBER 1000000
TimeBloomFilter TM;
int query_data[QUERY_TIME];
map<int,unsigned char> mp;
int main(){
    int Key,Value;
    int cnt=0;
    FILE *fi=fopen("./test_case.in","r");
    mp.clear();
    while(fscanf(fi,"%d%d",&Key,&Value)!=EOF){
        unsigned char v=(unsigned char ) Value;
        TM.insert(Key,v);
        mp[Key]=Value;
        query_data[cnt++]=Key;
    }
    unsigned char answer;
    int wrong_answer=0;
    puts("");
    for(int i=0;i<QUERY_TIME;i++){
        answer=mp[ query_data[i] ];
        if(answer!=TM.query( query_data[i] ) ){
            wrong_answer++;
        }
    }
    clock_t start,end;
    double duration;
    start=clock();
    for(int i=0;i<QUERY_TIME;i++){
        answer = mp[ query_data[i] ];
    }
    end=clock();
    duration=(double)(end-start)/CLOCKS_PER_SEC;
    printf(" use map to query using %lf time\n",duration);
    start=clock();
    for(int i=0;i<QUERY_TIME;i++){
        answer = TM.query( query_data[i] );
    }
    end=clock();
    duration=(double)(end-start)/CLOCKS_PER_SEC;
    printf(" use KeyValueBloomFilter using %lf time\n",duration);
    printf(" end with %d wrong\n",wrong_answer);
    return 0;
}
