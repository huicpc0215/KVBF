#include<iostream>
#include"kbf.h"
#include<cstdlib>
#include<stdio.h>
#include<fstream>
#include<map>
using namespace std;
kbf KBF(3,40320);
ifstream fi;
typedef unsigned char byte;
map<string,byte> mp;
int main(){
    fi.open("data2.in");
    string s;
    int v,allcnt=0,kbf_wrong_query=0;
    byte answer,kbf_answer,real_answer;
    byte bytev;
    while( fi >> s){
        fi >> v;
        bytev = ( byte )v;
        KBF.get(s.c_str(),&kbf_answer);
        real_answer = mp[s];
        printf("real_answer = %d kbf_answer=%d\n",real_answer,kbf_answer);
        if(real_answer!=kbf_answer){
            kbf_wrong_query++;
        }
        mp[s]=bytev;
        if( real_answer > 0 ) KBF.del(s.c_str(),&real_answer);
        if( bytev > 0 ) KBF.ins(s.c_str(),&bytev);
        allcnt ++;
    }
    printf(" allcnt = %d, wrong query = %d\n",allcnt,kbf_wrong_query);
    return 0;
}
