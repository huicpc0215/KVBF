#include<iostream>
#include"sbf.h"
#include<cstdlib>
#include<stdio.h>
#include<fstream>
#include<map>
using namespace std;
sbf SBF(3,40320);
ifstream fi;
typedef unsigned char byte;
map<string,byte> mp;
int main(){
    fi.open("data2.in");
    string s;
    int v,allcnt=0,sbf_wrong_query=0;
    byte answer,sbf_answer;
    byte bytev;
    while( fi >> s){
        fi >> v;
        bytev = ( byte )v;
        SBF-get(s.c_str(),&sbf_answer);
        real_answer =mp[s];
        if(real_answer!=sbf_answer){
            sbf_wrong_query++;
        }
        allcnt ++;
        if( v < 16 ){
            mp[s]=bytev;
            SBF->

        }
    }

    return 0;
}
