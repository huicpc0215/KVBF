#include<iostream>
#include"sbf.h"
#include<cstdlib>
#include<stdio.h>
#include<fstream>
#include<map>
using namespace std;
#define DK 0xFF
sbf SBF(3,40320);
ifstream fi;
typedef unsigned char byte;
map<string,byte> mp;

int main(){
    fi.open("data2.in");
    string s;
    int v,allcnt=0,sbf_wrong_query=0;
    byte answer,sbf_answer,real_answer;
    byte bytev;
    while( fi >> s){
        fi >> v;
        bytev = ( byte )v;
        SBF.get(s.c_str(),&sbf_answer);
        real_answer = mp[s];
        if(real_answer!=sbf_answer){
            sbf_wrong_query++;
        }
        if( v < 16 ){
            mp[s]=bytev;
            if( sbf_answer == 0 ) SBF.ins(s.c_str(),&bytev);
            else if(sbf_answer != DK )SBF.mdf(s.c_str(),&bytev);
        }
        else {
            mp[s]=0;
            if( sbf_answer != 0 && sbf_wrong_query != DK ) SBF.del(s.c_str(),&sbf_answer);
        }
        allcnt ++;
    }
    printf("allcnt = %d sbf_wrong_query = %d\n",allcnt,sbf_wrong_query);
    return 0;
}
