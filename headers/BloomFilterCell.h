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

class BloomFilterCell{
    private:
    //use INF to show that the element in the cell is no longer useful to now.
    //type : int
    //default value : 10;
    const int INF=10;

    //use cnt to count the number of how many digits has hashed into this
    //type : int
    //0: the element has just insert into the Cell
    //INF: initiation value , means that the information has no use
    int cnt;

    //use BFlength  to save the length of all the BloomFilter
    //type: int
    //default : 512
    int BFlength=512;
    //use pointer to  another single Cell that save one Cell
    //type:  int
    //-1: initiation  with no use in the cell
    //0-m-1: the next single Cell
    //m: the Cell has two or more information.
    int next;

    public:
    // construction function
    BloomFilterCell(int _cnt=INF,int _BFlength=512,int _next=-1){
        cnt=_cnt;
        BFlength=_BFlength;
        next=_next;
    }
    // init this cell
    // return : void
    // usage : init the cell
    void init(){
        cnt=INF;
        next=-1;
    }
    // get cnt
    // return int
    // usage : get count number of the cell
    int get_cnt(){
        return cnt;
    }
    // increase cnt by one
    // return : void
    // usage : increase count number by one
    void Increase_cnt(){
        cnt++;
        if(cnt==INF)init();
    }
    // set next pure cell
    // return : void
    // usage : set next cell
    void set_next(int _next){
        next=_next;
    }
    // check_next
    // return : int(0,1,2)
    // 0 : NULL
    // 1 : pure cell
    // 2 : mixed cell
    // usage: check the cell state
    int check_next(){
        if(next==-1) return 0;
        else if(next==BFlength) return 2;
        return 1;
    }
};

int main(){

    return 0;
}

