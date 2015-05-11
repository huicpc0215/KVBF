/*=============================================================================
#     FileName: kvbf_cell.cpp
#         Desc: implemtation
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: huicpc0215.github.io
#      Version: 0.0.1
#   LastChange: 2015-05-11 20:47:23
#      History:
=============================================================================*/
#include<stdlib.h>
#include<string.h>
#include"kvbf_cell.h"

kvbf_cell::kvbf_cell(){
    layer = (kvbf_layer**) malloc( ly_num * sizeof( kvbf_layer* ) );
    for(size_t i=0;i<ly_num;i++){
        layer[i]=new kvbf_layer(by_num);
    }
}

kvbf_cell::~kvbf_cell(){
    for(size_t i=ly_num-1;i>=0;i--){
        delete(layer[i]);
    }
    free(layer);
}

/*
 * write in parallel maybe accelarate query
 */
void kvbf_cell::get(byte* answer){
    // set the answer's all bits to 1
    memset(answer,0,by_num);
    for(size_t i=0;i<ly_num;i++){
        for(size_t j=0;j<by_num;j++){
            ( *(answer+j) ) |= ( *(layer[i]->get()+j ) );
        }
    }
}


/*
 * write in parallel may be accelarate insertion
 */
void kvbf_cell::ins(byte* _Value){
    if(ly_num==1){

    }
    else if(ly_num==2){

    }
}

/*
 * write in parallel maybe accelarate deletion
 */
void kvbf_cell::del(byte* _Value){
    if(ly_num==1){

    }
    else if(ly_num==2){

    }
}


