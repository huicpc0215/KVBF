/*=============================================================================
#     FileName: kvbf.cpp
#         Desc: implemtation
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-06 19:52:31
#      History:
=============================================================================*/
#include"BloomFilterCell.h"

BloomFilterCell::BloomFilterCell(){
    Value=0;
}

unsigned char BloomFilterCell::get(){
    return Value;
}

void BloomFilterCell::insert(unsigned char _Value){
    Value|=_Value;
}

BloomFilterCell::~BloomFilterCell(){

}
