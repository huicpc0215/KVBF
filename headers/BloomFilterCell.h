/*=============================================================================
#     FileName: BloomFilter.h
#         Desc: Basic units in the BloomFilter
#       Author: WenShi(huicpc0215)
#        Email: huicpc0215@gmail.com
#     HomePage: https://github.com/huicpc0215
#      Version: 0.0.1
#   LastChange: 2014-10-31 23:49:48
#      History:
=============================================================================*/

#ifndef TimeBloomFilter_headers_BloomFilterCell_H_
#define TimeBloomFilter_headers_BloomFilterCell_H_
class BloomFilterCell{
    private:
    //use INF to show that the element in the cell is no longer useful to now.
    //type : int
    //default value : 10;
    static const int INF=10;

    //use cnt to count the number of how many digits has hashed into this
    //type : int
    //0: the element has just insert into the Cell
    //INF: initiation value , means that the information has no use
    int cnt;

    //use pointer to  another single Cell that save one Cell
    //type:  int
    //-1: initiation  with no use in the cell
    //0-m-1: the next single Cell
    //m: the Cell has two or more information.
    int next;

    public:

    // defaul construction
    BloomFilterCell();

    // construction function
    BloomFilterCell(int _cnt,int _next);

    // destory function
    ~BloomFilterCell();

    // init this cell
    // return : void
    // usage : init the cell
    void init();

    // get cnt
    // return int
    // usage : get count number of the cell
    int get_cnt();

    // increase cnt by one
    // return : void
    // usage : increase count number by one
    void increase_cnt();

    // set next pure cell ,
    // if setzero=true then set the cell cnt to zero
    // else not to set the cnt to zero
    // return : void
    // usage : set next cell
    void set_next(int _next,bool setzero);

    // check_next
    // return : int(0,1,2)
    // -1 : NULL
    // 0-m-1 : pure cell
    // -2 : mixed cell
    // usage: check the cell state
    int check_next();
};
#endif
