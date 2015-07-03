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
#include<stdio.h>
#include"kvbf_cell.h"

kvbf_cell::kvbf_cell(){
    layer = (kvbf_layer**) malloc( 3 * sizeof( kvbf_layer* ) );
    layer[0]=new kvbf_layer(1);
    layer[1]=new kvbf_layer(1);
    layer[2]=new kvbf_layer(1);
}

kvbf_cell::~kvbf_cell(){
    delete(layer[0]);
    delete(layer[1]);
    delete(layer[2]);
    free(layer);
}

/*
 * write in parallel maybe accelarate query
 */
void kvbf_cell::get(byte* answer){
    // set the answer's all bits to 1
	*answer=0;
    *answer = *(layer[0]->get()) | *(layer[1]->get()) | *(layer[2]->get());
}


/*
 * write in parallel may be accelarate insertion
 */
void kvbf_cell::ins(byte* _Value){
    *(layer[0]->get()) ^= *(_Value);
    *(_Value) &= *(layer[0]->get());
    *(layer[1]->get()) ^= *(_Value);
    *(_Value) &= *(layer[1]->get());
    *(layer[2]->get()) ^= *(_Value);
    *(_Value) &= *(layer[2]->get());
}

/*
 * write in parallel maybe accelarate deletion
 */
void kvbf_cell::del(byte* _Value){
    *(layer[0]->get()) ^= *(_Value);
    *(_Value ) &= ~(*(layer[0]->get()));
    *(layer[1]->get()) ^= *(_Value);
    *(_Value ) &= ~(*(layer[1]->get()));
    *(layer[2]->get()) ^= *(_Value);
    *(_Value ) &= ~(*(layer[2]->get()));
}


