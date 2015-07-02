/*=============================================================================
#     FileName: kbf.h
#         Desc: kbf.h
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-29 09:49:11
#      History:
=============================================================================*/
#ifndef KBF_H
#define KBF_H

#include <string.h>

typedef unsigned char byte;
//typedef unsigned int size_t;

class kbf{
    public:
    // default construction
    kbf( size_t hash_num,size_t totol_size);

    // destory function
    ~kbf();

    // get key's value
    // parameters: char *, byte *
    // return : void
    void get(const char *key,byte* answer);

    // insert the key
    // parameters: char *, byte *
    // return : void
    void ins(const char *key,byte* _Value);

    // delete the key
    // parameters: char *, byte *
    // return : void
    void del(const char *key,byte* _Value);

    // modify the key
    // parameters: char *, byte *
    // return : void
    void mdf(const char *key,byte* newValue);

    size_t m;

    private:

    // get hash
    // parameters : char *
    // return size_t
    size_t get_hash(const char *key,int seed);

    // byte cell
    byte *cell;

    // count cell
    byte *count;

    size_t hash_num;

    int init_seed;
};

#endif
