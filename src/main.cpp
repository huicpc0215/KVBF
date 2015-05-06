#include "proceed/proceed.h"

int main(int argc,char *argv[]){
    if( argc < 2 ){
        fprintf(stdout,"arguments too few\n");
        return 0;
    }
    proceed(argv[1]);
    return 0;
}
