/*=============================================================================
#     FileName: main.cpp
#         Desc: simulation main function
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-06 18:46:30
#      History:
=============================================================================*/
#include "proceed/proceed.h"

int main(int argc,char *argv[]){
    if( argc < 2 ){
        fprintf(stdout,"no input file name\n");
        return 0;
    }
    proceed(argv[1]);
    return 0;
}
