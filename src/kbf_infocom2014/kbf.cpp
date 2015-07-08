#include"kbf.h"

#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<set>
#include<time.h>
#include<vector>
#include<algorithm>
using namespace std;
#define DK 0xFF

kbf::kbf(size_t _hash_num=3,size_t totol_size=65536){

    cell = ( byte *) malloc( totol_size );
    memset( cell , 0 ,sizeof (cell) );

    count = ( byte *) malloc( totol_size );
    memset( count , 0 ,sizeof ( count) );

    m = totol_size ;
    hash_num = _hash_num;

    for(int i=0;i<totol_size;i++){
        cell[i]=(unsigned char)0;
        count[i]=(unsigned char)0;
    }
    //init_seed = rand()%(m/hash_num);
    //init_seed = rand()%(m/hash_num);
    init_seed = 10;
}

kbf::~kbf(){
    free(count);
    free(cell);
}

void kbf::get(const char *key,byte* answer){
    size_t each_cell = m / hash_num;
    size_t tmp = init_seed , now = 0;
    *answer = 0xFF;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if( count[now+tmp] == 0 ){
            *answer = 0;
        }
        else if( count[now+tmp] == 1 ){
            *answer &= cell[now+tmp];
        }
        else if( count[now+tmp] == 2 ){
            if( cell[now+tmp] != 0 )
                *answer &= cell[now+tmp];
        }
        else if( count[now+tmp] == 3 ){
            if( ( cell[now+tmp] & ((cell[now+tmp])-1) ) != 0 )
                *answer &= cell[now+tmp];
        }
        now+=each_cell;
    }
}

void kbf::ins(const char *key,byte* _Value){
    size_t each_cell = m / hash_num;
    size_t tmp = init_seed , now = 0;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        count[ now + tmp ] ++;
        cell[ now + tmp] ^=*_Value;
        now+=each_cell;
    }
}

void kbf::del(const char *key,byte* _Value){
    size_t each_cell = m / hash_num;
    size_t tmp = init_seed , now = 0;
    for(int i=0;i<hash_num;i++){
        tmp = get_hash(key,tmp)%each_cell;
        if( count[ now + tmp ] > 0 ){
            count[ now + tmp ]--;
            cell[now+tmp] ^= *_Value;
        }
        if( count[ now + tmp ] == 0 )
            cell[ now + tmp ] = 0;
        //else printf(" there is an error in kbf delete!\n");
        now += each_cell;
    }
}

void kbf::mdf(const char *key,byte* newValue){
    byte query;
    get(key,&query);
    if(query != 0 && query != 0xFF )del(key,&query);
    ins(key,newValue);
}

size_t kbf::get_hash(const char * key,int seed){
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

