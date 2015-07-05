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
#include "kvbf_block.h"
#include <pthread.h>

class kvbf{
    public:
    // default construction
    kvbf(size_t hash_num,size_t cell_num,size_t  layer_num,size_t byte_num);

    // destory function
    ~kvbf();

    // get key's value
    // parameters : char *, byte *
    // return : void
    void get(const char *key,byte* answer);

    // insert the key
    // parameters : char *, byte *
    // return : void
    void ins(const char *key,byte* _Value);

    // delete the key
    // parameters : char *, byte *
    // return : void
    void del(const char *key,byte* _Value);

    // modefy the key to new value
    // parameters : char *, byte *
    // return : void
    void mdf(const char *key,byte* newValue);

    struct triple{
        const char *key;
        byte * answer;
        int index;
        kvbf* KVBF;
        triple(int _index,const char *_key,byte* _answer,kvbf *_kvbf):index(_index),key(_key),answer(_answer),KVBF(_kvbf){};
    };
    static void *query_function(void *ptr);
    static void *add_function(void *ptr);
    static void *del_function(void *ptr);

    // number of block;
    size_t bk_num;

    // data storage
    kvbf_block **block;
    pthread_t thread_id[10];
};
#endif
