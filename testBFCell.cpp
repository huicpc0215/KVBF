#include<iostream>
#include<cstdio>
#include<cmath>
#include"BloomFilterCell.h"

using namespace std;

BloomFilterCell B;


int main(){
    cout<<"B cnt="<<B.get_cnt()<<endl;
    cout<<"B next="<<B.get_next()<<endl;
    cout<<"set B"<<endl;
    B.set_next(10);
    cout<<"B next="<<B.get_next()<<endl;
    cout<<"increase B"<<endl;
    B.increase_cnt();
    for(int i=0;i<=10;i++){
        cout<<"B cnt="<<B.get_cnt()<<endl;
        B.increase_cnt();
    }

    return 0;
}
