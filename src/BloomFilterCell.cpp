#include"BloomFilterCell.h"

BloomFilterCell::BloomFilterCell(){
    Value=0;
}

unsigned char BloomFilterCell::get(){
    return Value;
}

void BloomFilterCell::insert(unsigned char _Value){
    Value|=_Value;
}

BloomFilterCell::~BloomFilterCell(){

}
