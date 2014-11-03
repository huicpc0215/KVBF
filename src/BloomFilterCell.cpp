#include"BloomFilterCell.h"

BloomFilterCell::BloomFilterCell(){
    cnt=INF;
    BFlength=512;
    next=-1;
}
BloomFilterCell::BloomFilterCell(int _cnt=INF,int _BFlength=512,int _next=-1){
    cnt=_cnt;
    BFlength=_BFlength;
    next=_next;
}
BloomFilterCell::~BloomFilterCell(){

}

void BloomFilterCell::init(){
    cnt=this->INF;
    next=-1;
}

int BloomFilterCell::get_cnt(){
    return this->cnt;
}

void BloomFilterCell::increase_cnt(){
    cnt++;
    if(cnt>=this->INF)init();
}

void BloomFilterCell::set_next(int _next){
    cnt=0;
    next=_next;
}

int BloomFilterCell::check_next(){
    return next;
}
