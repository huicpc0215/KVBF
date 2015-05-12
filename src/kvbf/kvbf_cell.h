/*=============================================================================
#     FileName: kvbf_cell.h
#         Desc: Basic units in the BloomFilter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-11 20:47:28
#      History:
=============================================================================*/

#ifndef KVBF_CELL_H
#define KVBF_CELL_H
#include"kvbf_layer.h"
class kvbf_cell{
    public:
    // default construction
    kvbf_cell();

    // destory function
    ~kvbf_cell();

    // get Cell value
    // parameters : byte*
    // return : void
    void get(byte* answer);

    // insert Cell with _Value
    // parameters :
    // return : void
    void ins(byte* _Value);

    // delete Cell with _Value
    // parameters : byte*
    // return : void
    void del(byte* _Value);

    // number of layer
    static size_t ly_num;

    // number of byte
    static size_t by_num;

    private:
    // data storage
    kvbf_layer **layer;


};
#endif
