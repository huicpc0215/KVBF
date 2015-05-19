#include<iostream>
#include"sbf.h"
#include<cstdlib>
#include<stdio.h>

using namespace std;
sbf s(3,1024);
typedef unsigned char byte;
int main(){
    byte ins,answer;
    ins = 1;
    s.ins("abasdf",&ins);
    s.get("abasdf",&answer);
    printf("get %d\n",answer);
    return 0;
}
