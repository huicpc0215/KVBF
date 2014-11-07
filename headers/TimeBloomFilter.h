/*=============================================================================
#     FileName: BloomFilter.h
#         Desc: description for Bloom Filter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-11-01 22:30:43
#      History:
=============================================================================*/

#ifndef TimeBloomFilter_headers_TimeBloomFilter_H_
#define TimeBloomFilter_headers_TimeBloomFilter_H_
#define CellNumber 512
#include<vector>
class TimeBloomFilter{
    private:
    // Cellnumber BloomfilterCell also
    // type: BloomfilterCell
    BloomFilterCell B[CellNumber];

    // k's hash that shows the k distinct number for any Integer
    // parameters: int x ( that to be hashed ) , int k ( hash number )
    // return : hashed position vector
    vector<int> getHash(int x,int k);

    public:
    // insert a integer and set the k position to zero
    // parameters: int x ( that want to insert into the TimeBloomFilter)
    // return : void
    void insert(int x);

    // query a integer how long the number has hashed into.
    // parameters: int x( that want to query if the element has hashed into the TimeBloomFilter)
    // return : 0-INF how long the number has hashed into
    int query(int x);

};
#endif
