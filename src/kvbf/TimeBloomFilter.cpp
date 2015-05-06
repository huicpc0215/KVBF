/*=============================================================================
#     FileName: TimeBloomFilter.cpp
#         Desc: implementationi of TimeBloomFilter.h
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-11-07 09:08:28
#      History:
=============================================================================*/
#include"TimeBloomFilter.h"
#include<cstdio>
#define NONE_VALUE -1
#define MIX_VALUE -2
#define MURMURHASH 1
#define EASY_HASH 2
#define INF 10
using namespace std;
TimeBloomFilter::TimeBloomFilter(){
    printf("in construction 0");
    Cell_number=32000000;
    for(int i=0;i<Cell_number;i++)
        B.push_back(BloomFilterCell());
    Hash_number=4;
    set_hash_type(1);
}

TimeBloomFilter::TimeBloomFilter(int _Cell_number){
    printf("in construction 1");
    Cell_number=_Cell_number;
    for(int i=0;i<Cell_number;i++)
        B.push_back(BloomFilterCell());
    Hash_number=4;
    set_hash_type(1);
}
TimeBloomFilter::TimeBloomFilter(int _Cell_number,int _Hash_number){
    printf("in construction 2");
    Cell_number=_Cell_number;
    for(int i=0;i<Cell_number;i++)
        B.push_back(BloomFilterCell());
    Hash_number=_Hash_number;
}
unsigned int TimeBloomFilter::murmur_hash(const void *key,int len,int seed){
    //printf("in mumurhash\n");
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    int x=(int)key;
    //while(x){
    //    len++;
    //    x/=2;
    //}

    //printf("x=%u\n",x);
    //printf("len=%d\n",len);
    // Initialize the hash to a 'random' value
    unsigned int h = seed ^ len;
    // Mix 4 bytes at a time into the hash
    const unsigned char * data = (const unsigned char *)key;
    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
            h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}
unsigned int TimeBloomFilter::easy_hash(const void *key,int len,int seed){
    unsigned int h=seed^len;
    const unsigned char * tmp= (const unsigned char *)key;
    for(int i=0;i<len;i++){
        h=h*17+tmp[i];
    }
    return h;
}
vector<unsigned int> TimeBloomFilter::get_hash(int _Key){
    //printf("in get_hash");
    vector<unsigned int> res;
    char tmp[20];
    int len=0;
    while(_Key){
        tmp[len++]=(_Key%10)+'0';
        _Key/=10;
    }
    int low_bound=0;
    unsigned int seed=0;
    //printf(" hashtype =%d murmurhash=%d\n",hashtype, MURMURHASH );
    for(int i=0;i<Hash_number;i++){
        if( Hash_type == MURMURHASH){
            seed = murmur_hash( tmp, len, seed );
            res.push_back( seed % (Cell_number/Hash_number)+low_bound);
            low_bound+=Cell_number/Hash_number;
            //printf("res-> %d\n",seed%CellNumber);
        }
        else if( Hash_type == EASY_HASH ){
            seed = easy_hash( tmp, len ,seed);
            res.push_back( seed % (Cell_number/Hash_number)+low_bound);
            low_bound+=Cell_number/Hash_number;
        }
    }
    return res;
}

void TimeBloomFilter::set_hash_type(int _Hash_type){
    Hash_type=_Hash_type;
}

void TimeBloomFilter::insert(int _Key,unsigned char _Value){
    //printf("in insert()");
    vector<unsigned int> hash=get_hash(_Key);
    int sz=hash.size();
    //printf("insert = %d\n",_Key);
    for(int i=0;i<sz;i++)
        B[ hash[i] ].insert(_Value);
}

unsigned char TimeBloomFilter::query(int _Key){
    //printf(" in query()");
    unsigned char res=255;
    vector<unsigned int> hash=get_hash(_Key);
    int sz=hash.size();
    for(int i=0;i<sz;i++){
        res&=B[ hash[i] ].get();
    }
    return res;
}
