/*=============================================================================
#     FileName: BloomFilterCell.h
#         Desc: Basic units in the BloomFilter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-12-21 10:17:14
#      History:
=============================================================================*/

#ifndef TimeBloomFilter_headers_BloomFilterCell_H_
#define TimeBloomFilter_headers_BloomFilterCell_H_
class BloomFilterCell{
    private:
    // value saved in this cell
    // type : char
    unsigned char Value;
    public:

    // defaul construction
    BloomFilterCell();

    // get Cell value
    // parameters : void
    // return : unsigned char
    unsigned char get();

    // insert Cell with _Value
    // parameters : unsigned char _Value
    // return : void
    void insert(unsigned char _Value);

    // destory function
    ~BloomFilterCell();
};
#endif
