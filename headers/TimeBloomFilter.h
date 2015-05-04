/*=============================================================================
#     FileName: TimeBloomFilter.h
#         Desc: description for Time Bloom Filter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-11-07 09:37:15
#      History:
=============================================================================*/


#ifndef TimeBloomFilter_headers_TimeBloomFilter_H_
#define TimeBloomFilter_headers_TimeBloomFilter_H_
#include"BloomFilterCell.h"
#include<vector>
using namespace std;

class TimeBloomFilter{
    private:
    // cellnumber
    // type: int
    int Cell_number;

    // hash number
    // type : int
    int Hash_number;

    // hash type
    // type: int
    int Hash_type;

    // murmurhash source code
    unsigned int murmur_hash(const void *key, int len , int seed);
    unsigned int easy_hash(const void *key,int len,int seed);

    public:
    // insert a key value and union the value to the cell
    // parameters: int x ( that want to insert into the TimeBloomFilter)
    // return : void
    void insert(int _Key,unsigned char _Value);

    //Cellnumber
    vector<BloomFilterCell> B;

    // k's hash that shows the k distinct number for any Integer
    // parameters: int x ( that to be hashed ) , int k ( hash number )
    // return : hashed position vector
    vector<unsigned int> get_hash(int _Key);

    //construction function
    TimeBloomFilter();

    //construction with Cellnumber's bloomfiltercell
    TimeBloomFilter(int _Cell_number);

    //constuction with Cellnumber and hash number
    TimeBloomFilter(int _Cell_number,int _Hash_number);

    // set hash type
    // if x == 1  set the hashtype to mormorhash
    void set_hash_type(int _Hash_type);

    // query a integer how long the number has hashed into.
    // parameters: int x( that want to query if the element has hashed into the TimeBloomFilter)
    // return : 0-INF how long the number has hashed into
    unsigned char query(int _Key);
};
#endif
