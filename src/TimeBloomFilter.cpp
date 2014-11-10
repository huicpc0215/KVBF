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
#define none_value -1
#define mix_value -2
#define INF 10
TimeBloomFilter::TimeBloomFilter(){
    CellNumber=512;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell());
        B_second.push_back(-1);
    }
}

TimeBloomFilter::TimeBloomFilter(int _cellnumber){
    CellNumber=_cellnumber;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell());
        B_second.push_back(-1);
    }
    hashnumber=4;
}
TimeBloomFilter::TimeBloomFilter(int _cellnumber,int _hashnumber){
    CellNumber=_cellnumber;
    for(int i=0;i<CellNumber;i++){
        B.push_back(BloomFilterCell());
        B_second.push_back(-1);
    }
    hashnumber=_hashnumber;
}
vector<int> TimeBloomFilter::get_hash(int x){
    vector<int> res;
    for(int i=0;i<hashnumber;i++){


        res.push_back(x%10);
        x/=10;
    }
    return res;
}

void TimeBloomFilter::insert(int x){
    vector<int> hash=get_hash(x);
    vector<int> Nullcell;
    int sz=hash.size();
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k==none_value )Nullcell.push_back( hash[i] );
        else if( k==hash[i] ){
            B_second[ hash[i] ] = B[ hash[i] ].get_cnt();
            B[ hash[i] ].set_next(mix_value,true);
        }
        else if( k>=0 && k<CellNumber){
            int p=hash[i];
            while(B[ p ].check_next()!=hash[i])p=B[p].check_next();
            B[ p ].set_next( B[hash[i]].check_next() , false);
            B[ hash[i] ].set_next(mix_value,true);
        }
    }
    sz=Nullcell.size();
    for(int i=0;i<sz;i++){
        B[ Nullcell[i] ].set_next(Nullcell[ i==sz-1?0:i+1 ] , true);
    }
}

int TimeBloomFilter::query(int x){
    vector<int> hash=get_hash(x);
    int sz=hash.size();
    bool has_none_value=false;
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k>=0 && k< CellNumber) return B[ hash[i] ].get_cnt();
        if( k==none_value ) has_none_value=true;
    }
    if( has_none_value ) return none_value;
    int res = INF;
    for(int i=0;i<sz;i++){
        res=min( res,B_second[hash[i]]);
    }
    return res;
}

void TimeBloomFilter::increase(){
    for(int i=0;i<CellNumber;i++){
        B[i].increase_cnt();
        B_second[i]++;
    }
}
