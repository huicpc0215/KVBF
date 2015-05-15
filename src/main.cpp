/*=============================================================================
#     FileName: main.cpp
#         Desc: simulation main function
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-06 18:46:30
#      History:
=============================================================================*/
#include "proceed/proceed.h"
#include "kvbf/kvbf.h"
#include<string.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<map>
#include<time.h>
typedef unsigned char byte;
//size_t kvbf_block::cl_num=0;
size_t kvbf_cell::ly_num=0;
size_t kvbf_cell::by_num=0;
map<string,byte> mp;
ifstream fi;
ofstream fo;
#define hash_default 3
#define cell_default 40960
#define layer_default 4

int hash_num_begin=hash_default;
int hash_num_end=hash_default;
int cell_num_begin=cell_default;
int cell_num_end=cell_default;
int layer_num_per_cell_begin=layer_default;
int layer_num_per_cell_end=layer_default;

int main(int argc,char *argv[]){
    if( argc < 3 ){
        fprintf(stdout,"no input file name or change type\n");
        return 0;
    }
    int p = atoi(argv[2]);
    if( p==0 ){
        printf("please choose hash_num(default %d) range[,]:\n",hash_default);
        scanf("%d%d",&hash_num_begin,&hash_num_end);
    }
    else if( p==1 ){
        printf("please choose cell_num_per_hash(default %d) range[,]:\n",cell_default);
        scanf("%d%d",&cell_num_begin,&cell_num_end);
    }
    else if( p==2 ){
        printf("please choose layer_num(default %d) range[,]:\n",layer_default);
        scanf("%d%d",&layer_num_per_cell_begin,&layer_num_per_cell_end);
    }
    else {
        printf("no %d options\n",p);
        return 0;
    }
    proceed(argv[1]);
    fo.open("result.out");
    srand(time(NULL));
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_num_begin;j<=cell_num_end;j+=cell_default){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                printf("start simulation hash = %d cell = %d layer = %d \n",i,j,k);
                if(p==0) printf("hash_num = %d ",i);
                else if(p==1) printf("cell_num_per_hash = %d ",j);
                else printf("layer_num_per_cell = %d ",k);
                kvbf* KVBF;
                KVBF = new kvbf(i,j,k,1);
                fi.open("data.in");
                mp.clear();
                string s;
                byte v,answer,real_answer;
                int allcnt = 0;
                int wrong_query = 0;
                while( fi>>s ){
                    //if( allcnt % 10000 == 0 ) printf("proceed %d packet!\n",allcnt);
                    fi>>v;
                    KVBF->get(s.c_str(),&answer);
                    real_answer=mp[s];

                    if( real_answer != answer ){
                        wrong_query++;
                    }
                    if( answer!= 0 ){
                        KVBF->del( s.c_str(),&answer );
                    }
                    if( v <= 4 ){
                        mp[s]=v;
                        KVBF->ins(s.c_str(),&v);
                    }
                    else mp[s]=0;
                    allcnt++;
                }
                printf("error rate = %lf \n",(double)wrong_query/(double)allcnt);
                int variant = (p==0?i:( p==1?j:k ));
                fo<<variant<<" "<<1.0*wrong_query/allcnt<<endl;
                fi.close();
                delete(KVBF);
            }
        }
    }
    fo.close();
    return 0;
}
