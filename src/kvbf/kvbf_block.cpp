/*=============================================================================
#     FileName: kvbf_block.cpp
#         Desc: kvbf_block.cpp
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-12 14:42:41
#      History:
=============================================================================*/

#include"kvbf_block.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

kvbf_block::kvbf_block(int _seed=0,int _cl_num=1024){
    seed = _seed;
    cl_num = _cl_num;
    cell = (kvbf_cell **)malloc(cl_num*sizeof(kvbf_cell*));
    for(size_t i=0;i<cl_num;i++){
        cell[i]=new kvbf_cell();
		if( cell[i] == NULL ){
			printf("cann't new !!");
		}
    }
	
	byte tmp;
    printf("\ngive cell=%u seed=%d\n",cl_num,seed);

}

kvbf_block::~kvbf_block(){
    for(size_t i=0;i<cl_num;i++){
        delete(cell[i]);
    }
    free(cell);
}

void kvbf_block::get(const char *key,byte* answer){
    cell[ hash(key) ]->get(answer);
}

void kvbf_block::ins(const char *key,byte* _Value){
    cell[ hash(key) ]->ins(_Value);
}

void kvbf_block::del(const char *key,byte* _Value){
    cell[ hash(key) ]->del(_Value);
}

size_t kvbf_block::hash(const char *key){
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    int len = strlen(key);

    // Initialize the hash to a 'random' value
    unsigned int h = seed ^ len;
    // Mix 4 bytes at a time into the hash
    const unsigned char * data = (const unsigned char *)key;
    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
            h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h%cl_num;
}


