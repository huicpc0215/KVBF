#include"BloomFilterCell.h"

#define NONE_VALUE -1
BloomFilterCell::BloomFilterCell(){
    cnt=this->INF;
    next=-1;
}
BloomFilterCell::BloomFilterCell(int _cnt=INF,int _next=-1){
    cnt=_cnt;
    next=_next;
}

BloomFilterCell::~BloomFilterCell(){

}

void BloomFilterCell::init(){
    cnt=this->INF;
    next=NONE_VALUE;
}

int BloomFilterCell::get_cnt(){
    return this->cnt;
}

void BloomFilterCell::increase_cnt(){
    cnt++;
    if(cnt>=this->INF)init();
}

void BloomFilterCell::set_next(int _next,bool f){
    if(f)cnt=0;
    next=_next;
}

int BloomFilterCell::check_next(){
    return next;
}
