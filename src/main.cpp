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
typedef unsigned char byte;
size_t kvbf_block::cl_num=0;
size_t kvbf_cell::ly_num=0;
size_t kvbf_cell::by_num=0;
map<string,byte> mp;
ifstream fi;
#define hash_default 3
#define cell_default 32768
#define layer_default 3

int hash_num_begin=hash_default;
int hash_num_end=hash_default;
int cell_num_per_hash_begin=cell_default;
int cell_num_per_hash_end=cell_default;
int layer_num_per_cell_begin=layer_default;
int layer_num_per_cell_end=layer_default;

int main(int argc,char *argv[]){
    if( argc < 2 ){
        fprintf(stdout,"no input file name\n");
        return 0;
    }
    //proceed(argv[1]);
    int p = -1;
    do{
        printf("choose the variety:\n");
        printf("0. hash_num\n");
        printf("1. cell_num_per_hash\n");
        printf("2. layer_num_per_cell\n");
        scanf("%d",&p);
    }while( p < 0 || p > 2 );
    printf("p reads end p=%d \n",p);
    if( p==0 ){
        printf("please choose hash_num(default %d) range[,]:\n",hash_num_begin);
        scanf("%d%d",&hash_num_begin,&hash_num_end);
    }
    else if( p==1 ){
        printf("please choose cell_num_per_hash(default %d) range[,]:\n",cell_num_per_hash_begin);
        scanf("%d%d",&cell_num_per_hash_begin,&cell_num_per_hash_end);
    }
    else {
        printf("please choose layer_num(default %d) range[,]:\n",layer_num_per_cell_begin);
        scanf("%d%d",&layer_num_per_cell_begin,&layer_num_per_cell_end);
    }
    printf("read ends\n");
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_num_per_hash_begin;j<=cell_num_per_hash_end;j*=2){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                printf(" start simulation hash = %d cell = %d layer = %d \n",i,j,k);
                if(p==0) printf("hash_num = %d ",i);
                else if(p==1) printf("cell_num_per_hash = %d ",j);
                else printf("layer_num_per_cell = %d ",k);
                kvbf* KVBF;
                KVBF = new kvbf(i,j,k,1);
                fi.open("data.in");
                mp.clear();
                string s;
                byte v;
                byte ans;
                int allcnt = 0;
                int wrong_query = 0;
                while( fi>>s ){
                    //if( allcnt % 10000 == 0 ) printf("proceed %d packet!\n",allcnt);
                    fi>>v;
                    KVBF->get(s.c_str(),&ans);
                    if( mp[s] != ans ){
                        wrong_query++;
                    }
                    mp[s]=v;
                    if( ans != 0 ){
                        KVBF->del(s.c_str(),&ans);
                    }
                    KVBF->ins(s.c_str(),&v);
                    allcnt++;
                }
                printf("error rate = %lf \n",(double)wrong_query/(double)allcnt);
                fi.close();
                delete(KVBF);
            }
        }
    }
    return 0;
}
