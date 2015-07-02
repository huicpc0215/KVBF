/*=============================================================================
#     FileName: kvbf_layer.h
#         Desc: Basic units in the BloomFilter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-11 16:30:52
#      History:
=============================================================================*/

#ifndef KVBF_LAYER_H
#define KVBF_LAYER_H
#include<stdio.h>
typedef unsigned char byte;
//typedef unsigned int size_t;
class kvbf_layer{
    public:
    // construction
    kvbf_layer(size_t b);

    // get Cell value
    // parameters : void
    // return : byte*
    byte* get();

    // destory function
    ~kvbf_layer();

    private:

    // value saved in this layer
    // type : byte
    byte* Value;
};
#endif
