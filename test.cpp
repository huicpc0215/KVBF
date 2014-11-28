#include<iostream>
#include<time.h>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<cmath>
#include"TimeBloomFilter.h"

using namespace std;

#define OBJ_PER_SEC 5
#define SIMULATION_TIME 50
#define UP_OFFSET 10
#define EXIST_QUERY_OK 0
#define EXIST_QUERY_WRONG 1
#define NO_EXIST_QUERY_OK -1
#define NO_EXIST_QUERY_WRONG -2
#define TEST_EXIST_PER_SEC 15
#define TEST_NO_EXIST_PER_SEC 5
#define INF 10
#define NONE_VALUE -1


BloomFilterCell B;
TimeBloomFilter TM(1024,4);
set<int> s;
set<int> timeline[SIMULATION_TIME];
set<int>::iterator it;
set<int> test_exist;
set<int> test_no_exist;


int main(){
    srand(time(NULL));
    printf("int = %d char = %d \n",sizeof(int),sizeof(char));
    puts("ok");
    TM.set_hashtype(1);
    printf("set ok!");
    for(int i=0;i<OBJ_PER_SEC * SIMULATION_TIME ;i++){
        int k=rand();
        while(s.find(k)!=s.end())k=rand();
        s.insert(k);
        timeline[i/OBJ_PER_SEC].insert(k);
    }
    for(int i=0;i<SIMULATION_TIME;i++){
        printf("time %d insert %d things\n",i,timeline[i].size());
    }
    puts("Generation OK!");
    for(int i=0;i<SIMULATION_TIME;i++){
        for(it=timeline[i].begin();it!=timeline[i].end();it++){
            TM.insert(*it);
        }
        printf("enter to continue \n");
        getchar();
        test_no_exist.clear();
        test_exist.clear();
        int count_test_exist_ok=0;
        for(int j=0;j<TEST_EXIST_PER_SEC;j++){
            int flag;
            int k=rand()%(i+1);
            int q=rand()%timeline[k].size();
            it=timeline[k].begin();
            while(q--)it++;
            //if(i<5)printf("it =%d\n",timeline[k].find(*it)==timeline[k].end());
            int real_answer=min(i-k,INF);
            int BF_answer=TM.query(*it);
            if( real_answer == BF_answer ) flag=EXIST_QUERY_OK;
            else flag=EXIST_QUERY_WRONG;
            switch(flag){
                case EXIST_QUERY_OK:
                    count_test_exist_ok++;
                    break;
                case EXIST_QUERY_WRONG:
                    puts("here wrong appears");
                    printf(" BF_answer=%d real_answer =%d\n",BF_answer,real_answer);
                    break;
            }
        }
        int count_test_no_exist_ok=0;
        set<int> recall_test;
        recall_test.clear();
        for(int j=0;j<TEST_NO_EXIST_PER_SEC;j++){
            int k=rand();
            int flag;
            while(s.find(k)!=s.end())k=rand();
            if( TM.query(k) == INF || TM.query(k) == NONE_VALUE ) flag=NO_EXIST_QUERY_OK;
            else flag=NO_EXIST_QUERY_WRONG;
            switch(flag){
                case NO_EXIST_QUERY_OK:
                    count_test_no_exist_ok++;
                    break;
                case NO_EXIST_QUERY_WRONG:
                    recall_test.insert(k);
                    break;
            }
        }
        if( count_test_no_exist_ok != TEST_NO_EXIST_PER_SEC ){
            puts("BAD:");
            for(it=recall_test.begin();it!=recall_test.end();it++){
                printf("%d ->  hash \n",*it);
                vector<int> hs=TM.get_hash(*it);
                int sz=hs.size();
                for(int p=0;p<sz;p++){
                printf("%d\n",hs[p]);
                }
            }
        }
        printf("round %d -> test %d exist : %d ok , %d wrong \n",i,TEST_EXIST_PER_SEC,count_test_exist_ok,TEST_EXIST_PER_SEC-count_test_exist_ok);
        printf("round %d -> test %d no exist : %d ok , %d wrong \n",i,TEST_NO_EXIST_PER_SEC,count_test_no_exist_ok,TEST_NO_EXIST_PER_SEC - count_test_no_exist_ok );
        puts("");
        TM.increase();
    }
    return 0;
}
