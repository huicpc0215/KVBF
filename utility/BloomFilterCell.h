/*=============================================================================
#     FileName: BloomFilter.h
#         Desc: Basic units in the BloomFilter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-10-31 23:49:48
#      History:
=============================================================================*/

class BloomFilterCell{
    //use cnt to count the number of how many digits has hashed into this
    //type : int
    //0: the element has just insert into the Cell
    //10: initiation value , means that the information has no use
    int cnt;
    //use pointer to  another single Cell that save one Cell
    //type:  int
    //-1: initiation  with no use in the cell
    //0-m-1: the next single Cell
    //m: the Cell has two or more information.
    int next;
};


