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
    hashnumber=4;

}

vector<int> TimeBloomFilter::getHash(int x){


}

void TimeBloomFilter::insert(int x){
    vector<int> hash=getHash(x);
    vector<int> Nullcell;
    int sz=hash.size();
    for(int i=0;i<sz;i++){
        if( B[ hash[i] ].check_next()==-1 ){
            Nullcell.push_back( hash[i] );
        }
        else B[ hash[i] ].set_next(-2);
    }
    sz=Nullcell.size();
    for(int i=0;i<sz;i++){
        B[ Nullcell[i] ].set_next(Nullcell[ i==sz-1?0:i+1 ]);
    }
}

int TimeBloomFilter::query(int x){
    vector<int> hash=getHash(x);
    int sz=hash.size();
    for(int i=0;i<sz;i++){
        int k=B[ hash[i] ].check_next();
        if( k>=0 && k< m ) return
    }

}

void TimeBloomFilter::increase(){

}




