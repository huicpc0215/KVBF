/*=============================================================================
#     FileName: kvbf_block.h
#         Desc: kvbf_block.h
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-11 20:48:49
#      History:
=============================================================================*/

#ifndef KVBF_BLOCK_H
#define KVBF_BLOCK_H
#include "kvbf_cell.h"
class kvbf_block{
    public:
    // default construction
    kvbf_block();

    // destory function
    ~kvbf_block();

    // get key's value in this block
    // parameters : char *, byte *
    // return : void
    void get(char *key,byte* answer);

    // insert the key in this block
    // parameters : char *, byte *
    // return : void
    void ins(char *key,byte* answer);

    // delete the key in this block
    // parameters : char *, byte *
    // return : void
    void del(char *key,byte* answer);

    private:
    // data storage
    kvbf_cell **cell;

    // hash seed
    int seed;

    // number of cell;
    static size_t cl_num;

    // use the seed and key to generate the position
    // parameters: char *
    // return :position
    size_t hash(char *key){

    }
};
#endif
