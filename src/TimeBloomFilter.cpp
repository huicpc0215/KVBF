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

TimeBloomFilter::TimeBloomFilter(){
    CellNumber=512;
    for(int i=0;i<CellNumber;i++){
        B.push_back();
        B_second.push_back(-1);
    }
}

TimeBloomFilter::TimeBloomFilter(int number){
    CellNumber=number;
    for(int i=0;i<CellNumber;i++){
        B.push_back();
        B_second.push_back(-1);
    }
}
vector<int> TimeBloomFilter::getHash(int x){


}

void TimeBloomFilter::insert(int x){
    vector<int> hash=get_hash(x);
    vector<int> Nullcell;
    int sz=hash.size();
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k==-1 )Nullcell.push_back( hash[i] );
        else if( k==hash[i] ){
            B_second[ hash[i] ] = B[ hash[i] ].get_cnt();
            B[ hash[i] ].set_next(-2,true);
        }
        else if( k>=0 && k<CellNumber){
            int p=hash[i];
            while(B[ p ].check_next()!=hash[i])p=B[p].check_next();
            B[ p ].set_next( B[hash[i]].check_next() , false);
            B[ hash[i] ].set_next(-2,true);
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
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k>=0 && k< m ) return B[ hash[i] ].get_cnt();
        else if( k==-1 ) return -1;
    }
    return query_in_second(x);
}

void TimeBloomFilter::increase(){
    for(int i=0;i<CellNumber;i++){
        B[i].increase_cnt();
        B_second[i].increase_cnt();
    }
}




