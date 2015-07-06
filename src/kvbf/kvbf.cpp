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
#include<omp.h>
#include<pthread.h>

pthread_mutex_t ans_mutex = PTHREAD_MUTEX_INITIALIZER;

void kvbf_constrction(size_t _hash_num,size_t _cell_num, size_t _layer_num, size_t _byte_num){
    kvbf_block_num = _hash_num;
    kvbf_cell_num = _cell_num;
    kvbf_layer_num = _layer_num;
    kvbf_byte_num = _byte_num;
    kvbf_each_block = kvbf_cell_num/kvbf_block_num;
    kvbf_cells = (byte*)malloc( kvbf_cell_num * kvbf_layer_num * kvbf_byte_num );
}
void kvbf_destruction(){
    free(kvbf_cells);
}

size_t kvbf_hash(const char *key,int seed){
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
    return h%kvbf_each_block;
}

void* kvbf_para_query(void * ptr){
    kvbf_triple* p = (kvbf_triple* )ptr;
    size_t cell_index = ( kvbf_each_block * p->block_index + kvbf_hash( p->key , p->block_index ) ) * 3;
    byte* ans = p->val;
    byte tmp=kvbf_cells[ cell_index ] | kvbf_cells[ cell_index + 1 ] | kvbf_cells[ cell_index + 2 ];
    pthread_mutex_lock( &ans_mutex );
    (*ans) &= tmp;
    pthread_mutex_unlock( &ans_mutex );
}
void kvbf_get(const char*key,byte* answer){
    *answer=0xFF;
    for(int i=0;i<kvbf_block_num;i++){
        kvbf_triple p(key,i,answer);
        pthread_create( &kvbf_thread_id[i] ,NULL,kvbf_para_query, &p);
    }
    for(int i=0;i<kvbf_block_num;i++){
        pthread_join( kvbf_thread_id[i] , NULL );
    }
}

void *kvbf_para_del(void *ptr){
    kvbf_triple *p = (kvbf_triple*) ptr;
    byte tmp=*(p->val);
    size_t cell_index = ( kvbf_each_block * p->block_index + kvbf_hash( p->key, p->block_index ) )*3;
    kvbf_cells[ cell_index ] ^= tmp;
    tmp &= ~ ( kvbf_cells[ cell_index ] );
    kvbf_cells[ cell_index+1 ] ^= tmp;
    tmp &= ~ ( kvbf_cells[ cell_index+1 ] );
    kvbf_cells[ cell_index+2 ] ^= tmp;
    tmp &= ~ ( kvbf_cells[ cell_index+2 ] );
}

void kvbf_del(const char *key,byte* _Value){
    for(int i=0;i<kvbf_block_num;i++){
        kvbf_triple p(key,i,_Value);
        pthread_create( &kvbf_thread_id[i],NULL,kvbf_para_del,&p );
    }
    for(int i=0;i<kvbf_block_num;i++){
        pthread_join( kvbf_thread_id[i],NULL );
    }
}

void *kvbf_para_ins(void *ptr){
    kvbf_triple *p = (kvbf_triple*) ptr;
    byte tmp=*(p->val);
    size_t cell_index = ( kvbf_each_block * p->block_index + kvbf_hash( p->key, p->block_index ) )*3;
    kvbf_cells[ cell_index ] ^= tmp;
    tmp &= kvbf_cells[ cell_index ];
    kvbf_cells[ cell_index+1 ] ^= tmp;
    tmp &= kvbf_cells[ cell_index+1 ];
    kvbf_cells[ cell_index+2 ] ^= tmp;
    tmp &= kvbf_cells[ cell_index+2 ];
}

void kvbf_ins(const char *key,byte* _Value){
    for(int i=0;i<kvbf_block_num;i++){
        kvbf_triple p(key,i,_Value);
        pthread_create( &kvbf_thread_id[i],NULL,kvbf_para_ins,&p );
    }
    for(int i=0;i<kvbf_block_num;i++){
        pthread_join( kvbf_thread_id[i],NULL );
    }
}
