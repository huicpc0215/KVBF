/*=============================================================================
#     FileName: sbf.cpp
#         Desc: sbf.cpp
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-19 19:20:57
#      History:
=============================================================================*/
#include"sbf.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define DK 0xFF

sbf::sbf(size_t _hash_num=3,size_t totol_size=65536){
    printf("construction with %d cells!",totol_size);

    cell = (byte *) malloc(totol_size);
    memset( cell, 0x00, sizeof(cell) );

    count = (byte *)malloc(totol_size);
    memset( count , 0x00 , sizeof(count) );

    for(int i=0;i<totol_size;i++){
        cell[i]=(unsigned char)0;
        count[i]=(unsigned char)0;
    }
    m = totol_size;
    hash_num = _hash_num;

    init_seed=rand()%(m/hash_num);
}

sbf::~sbf(){
    free(count);
    free(cell);
}

void sbf::get(const char * key, byte * answer){
    size_t each_cell = m/hash_num;
    size_t tmp=init_seed,now=0;
    *answer = DK;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if( cell[now+tmp] != DK ){
            if( *answer!=DK && *answer!=cell[now+tmp] ){
                *answer = 0;
                break;
            }
            else if( *answer==DK ){
                *answer = cell[ now + tmp];
            }
        }
        now+=each_cell;
    }
}

void sbf::ins(const char *key,byte * _Value){
    size_t each_cell = m / hash_num;
    size_t tmp=init_seed,now=0;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if( count[now+tmp] == 0){
            count[now+tmp]=1;
            //memcpy( (char *)&cell[i], (const char *)_Value, 1 );
            cell[now+tmp]=*_Value;
        }
        else if( cell[now+tmp] == DK ){
            count[now+tmp]++;
        }
        else if( *_Value == cell[now+tmp] ){
            count[now+tmp]++;
        }
        else if( *_Value != cell[now+tmp] ){
            count[now+tmp]++;
            cell[now+tmp]=DK;
        }
        now+=each_cell;
    }
}

void sbf::del(const char *key, byte* _Value){
    size_t each_cell = m / hash_num;
    size_t tmp=init_seed,now=0;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if( count[now+tmp] == 1 ) cell[ now+tmp] = 0 ;
        if( count[now+tmp] > 0 ) count[now+tmp]--;
        now+=each_cell;
    }
}

void sbf::mdf(const char *key,byte* newValue){
    size_t each_cell = m / hash_num;
    size_t tmp=init_seed,now=0;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if(cell[now+tmp]!=DK){
            if(count[now+tmp] == 1){
                cell[now+tmp] = *newValue;
            }
            else cell[now+tmp] = DK;
        }
        now+=each_cell;
    }
}

size_t sbf::get_hash(const char * key,int seed){
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    int len = strlen(key);

    // Initialize the hash to a 'random' value
    unsigned int h = seed ^ len;
    // Mix 4 bytes at a time into the hash
    const unsigned char * data = (const unsigned char *)key;
    while(len >= 4)
    {
        unsigned int k = *(unsigned int *)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }
    // Handle the last few bytes of the input array
    switch(len)
    {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
            h *= m;
    };
    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;
    return h;
}

