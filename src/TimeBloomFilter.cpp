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
#define INF 10
using namespace std;
TimeBloomFilter::TimeBloomFilter(){
    printf("in construction 0");
    CellNumber=512;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell());
        B_second.push_back(-1);
    }
    hashnumber=3;
}

TimeBloomFilter::TimeBloomFilter(int _cellnumber){
    printf("in construction 1");
    CellNumber=_cellnumber;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell(INF,-1));
        B_second.push_back(-1);
    }
    hashnumber=4;
}
TimeBloomFilter::TimeBloomFilter(int _cellnumber,int _hashnumber){
    printf("in construction 2");
    CellNumber=_cellnumber;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell(INF,-1));
        B_second.push_back(-1);
    }
    hashnumber=_hashnumber;
}
unsigned int TimeBloomFilter::murmurhash(const void *key,int len,int seed){
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
vector<int> TimeBloomFilter::get_hash(int x){
    //printf("in get_hash");
    vector<int> res;
    char tmp[20];
    int len=0;
    while(x){
        tmp[len++]=(x%10)+'0';
        x/=10;
    }
    int low_bound=0;
    unsigned int seed=0;
    //printf(" hashtype =%d murmurhash=%d\n",hashtype, MURMURHASH );
    for(int i=0;i<hashnumber;i++){
        if( hashtype == MURMURHASH){
            seed = murmurhash( tmp, len, seed );
            res.push_back( seed % (CellNumber/hashnumber)+low_bound);
            low_bound+=CellNumber/hashnumber;
            //printf("res-> %d\n",seed%CellNumber);
        }
    }
    return res;
}

void TimeBloomFilter::set_hashtype(int x){
    hashtype=x;
}

void TimeBloomFilter::insert(int x){
    //printf("in insert()");
    vector<int> hash=get_hash(x);
    vector<int> Nullcell;

    int sz=hash.size();
    printf("insert = %d\n",x);
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k==NONE_VALUE)Nullcell.push_back( hash[i] );
        else if( k==hash[i] ){
            B_second[ hash[i] ] = B[ hash[i] ].get_cnt();
            B[ hash[i] ].set_next(MIX_VALUE,true);
        }
        else if( k>=0 && k<CellNumber){
            int p=hash[i];
            while(B[ p ].check_next()!=hash[i])p=B[p].check_next();
            B[ p ].set_next( B[hash[i]].check_next() , false);
            B[ hash[i] ].set_next(MIX_VALUE,true);
        }
        printf("hash[%d]=%d\n",i,hash[i]);
    }
    sz=Nullcell.size();
    for(int i=0;i<sz;i++){
        B[ Nullcell[i] ].set_next(Nullcell[ i==sz-1?0:i+1 ] , true);
    }
}

int TimeBloomFilter::query(int x){
    //printf(" in query()");
    vector<int> hash=get_hash(x);
    int sz=hash.size();
    bool has_none_value=false;
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k>=0 && k< CellNumber) {
            int p=hash[i];
            bool fg=true;
            while(k!=p){
                if(*lower_bound(hash.begin(),hash.end(),k)!=k){
                    fg=false;
                    break;
                }
                else k=B[k].check_next();
            }
            if(fg)return B[ hash[i] ].get_cnt();
        }
        if( k==NONE_VALUE) has_none_value=true;
    }
    if( has_none_value ) return INF;
    int res = INF;
    for(int i=0;i<sz;i++){
        res=min( res,B_second[hash[i]] );
    }
    return res;
}

void TimeBloomFilter::increase(){
    //printf(" in increase");
    for(int i=0;i<CellNumber;i++){
        B[i].increase_cnt();
        B_second[i]++;
    }
}
