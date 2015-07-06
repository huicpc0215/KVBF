/*=============================================================================
#     FileName: kvbf.h
#         Desc: kvbf.h
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-12 14:46:11
#      History:
=============================================================================*/

#ifndef KVBF_H
#define KVBF_H
#include <pthread.h>
typedef unsigned char byte;

size_t kvbf_cell_num;
size_t kvbf_block_num;
size_t kvbf_layer_num;
size_t kvbf_byte_num;
size_t kvbf_each_block;
byte kvbf_tmp_answer[10];
pthread_t kvbf_thread_id[10];
struct kvbf_triple{
    const char * key;
    int block_index;
    byte* val;
    kvbf_triple(const char* _key,int _block_index,byte* _answer):key(_key),block_index(_block_index),val(_answer){};
};
byte* kvbf_cells;

void kvbf_construction(size_t hash_num, size_t cell_num, size_t _layer_num,size_t _bytenum);
void kvbf_destruction();
int kvbf_hash(const char *key,int seed);

void* kvbf_para_query(void * ptr);
void kvbf_get(const char *key,byte* answer);

void* kvbf_para_ins(void *ptr);
void kvbf_ins(const char *key,byte* _Value);

void* kvbf_para_del(void *ptr);
void kvbf_del(const char *key,byte* _Value);

#endif
