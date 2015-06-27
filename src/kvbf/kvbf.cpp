/*=============================================================================
#     FileName: kvbf.cpp
#         Desc: kvbf.cpp
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-12 14:54:55
#      History:
=============================================================================*/
#include"kvbf.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
kvbf::kvbf(size_t hash_num=3,size_t cell_num=1024,size_t layer_num=2,size_t byte_num=1){
    bk_num = hash_num;
    //kvbf_block::cl_num = cell_num_per_block;
    kvbf_cell::ly_num = layer_num;
    kvbf_cell::by_num = byte_num;
    cell_num /= layer_num;
    int *seed;
    int tmp;
    int nowsize=cell_num/hash_num,remain=cell_num;
    seed = (int *)malloc( bk_num * sizeof( int ) );
    block = (kvbf_block **) malloc ( bk_num * sizeof( kvbf_block* ) );
    for(size_t i=0;i<bk_num;i++){
        bool same_seed=false;
        do{
            same_seed=false;
            tmp=rand();
            for(size_t j=0;j<i;j++){
                if( seed[j]==tmp ){
                    same_seed = true;
                    break;
                }
            }
        }while(same_seed);
        seed[i]=tmp;
        block[i]=new kvbf_block(tmp,(i==bk_num-1?remain:nowsize));
        remain-=nowsize;
    }
    tmp_value=(byte*)malloc(byte_num * sizeof(byte) );
    free(seed);
}
kvbf::~kvbf(){
    free(tmp_value);
    for(size_t i=0;i<bk_num;i++){
        delete(block[i]);
    }
    free(block);
}

void kvbf::get(const char *key,byte* answer){
    memset(answer,0xFF,kvbf_cell::by_num);
    for(size_t i=0;i<bk_num;i++){
        block[i]->get(key,tmp_value);
        for(size_t j=0;j<kvbf_cell::by_num;j++){
            *(answer+j) &= *(tmp_value+j);
        }
    }
}

void kvbf::ins(const char *key,byte* _Value){
    for(size_t i=0;i<bk_num;i++){
        memcpy( tmp_value , _Value, kvbf_cell::by_num );
        block[i]->ins(key,tmp_value);
    }
}

void kvbf::del(const char *key,byte* _Value){
    for(size_t i=0;i<bk_num;i++){
        memcpy( tmp_value, _Value , kvbf_cell::by_num );
        block[i]->del(key,tmp_value);
    }
}

void kvbf::mdf(const char *key,byte* newValue){
    byte * oldValue;
    oldValue = ( byte* ) malloc( kvbf_cell::by_num );
    get(key,oldValue);
    del(key,oldValue);
    ins(key,newValue);
    free(oldValue);
}
