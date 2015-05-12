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
kvbf::kvbf(size_t hash_num=3,size_t cell_num_per_block=1024,size_t layer_num=2,size_t byte_num=1){
    bk_num = hash_num;
    kvbf_block::cl_num = cell_num_per_block;
    kvbf_cell::ly_num = layer_num;
    kvbf_cell::by_num = byte_num;
    int *seed;
    int tmp;
    seed = (int *)malloc( bk_num * sizeof( int*) );
    block = (kvbf_block **) malloc ( bk_num * sizeof( kvbf_block*) );
    for(size_t i=0;i<bk_num;i++){
        bool same_seed=false;
        do{
            tmp=rand();
            for(size_t j=0;j<i;j++){
                if( seed[j]==tmp ){
                    same_seed = true;
                    break;
                }
            }
        }while(same_seed);
        seed[i]=tmp;
        block[i]=new kvbf_block(tmp);
    }
}
kvbf::~kvbf(){
    for(size_t i=0;i<bk_num;i++){
        delete(block[i]);
    }
    free(block);
}

void kvbf::get(const char *key,byte* answer){
    memset(answer,0xFF,kvbf_cell::by_num);
    byte * tmp;
    tmp = (byte *)malloc( kvbf_cell::by_num * sizeof(byte) );
    for(size_t i=0;i<bk_num;i++){
        block[i]->get(key,tmp);
        for(size_t j=0;j<kvbf_cell::by_num;j++){
            *(answer+j) &= *(tmp+j);
        }
    }
}

void kvbf::ins(const char *key,byte* _Value){
    byte * tmp;
    tmp = (byte *) malloc ( kvbf_cell::by_num*sizeof(byte) );
    for(size_t i=0;i<bk_num;i++){
        memcpy( tmp , _Value, kvbf_cell::by_num );
        block[i]->ins(key,tmp);
    }
}

void kvbf::del(const char *key,byte* _Value){
    byte * tmp;
    tmp = (byte* )malloc ( kvbf_cell::by_num*sizeof(byte) );
    for(size_t i=0;i<bk_num;i++){
        memcpy( tmp, _Value , kvbf_cell::by_num );
        block[i]->del(key,tmp);
    }
}
