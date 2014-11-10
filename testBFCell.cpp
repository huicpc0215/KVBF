#include<iostream>
#include<cstdio>
#include<cmath>
#include"BloomFilterCell.h"

using namespace std;

BloomFilterCell B;


int main(){
    cout<<"B cnt="<<B.get_cnt()<<endl;
    cout<<"B next="<<B.check_next()<<endl;
    cout<<"set B"<<endl;
    B.set_next(10,true);
    cout<<"B next="<<B.check_next()<<endl;
    cout<<"B cnt="<<B.get_cnt()<<endl;
    cout<<"increase B"<<endl;
    B.increase_cnt();
    cout<<"B cnt="<<B.get_cnt()<<endl;
    for(int i=0;i<=10;i++){
        B.increase_cnt();
        cout<<"B cnt="<<B.get_cnt()<<endl;
        cout<<"B next="<<B.check_next()<<endl<<endl;
    }

    return 0;
}
