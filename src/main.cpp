/*=============================================================================
#     FileName: main.cpp
#         Desc: simulation main function
#       Author: huicpc0215
#        Email: huicpc0215@gmail.com
#     HomePage: http://huicpc0215.uni.me
#      Version: 0.0.1
#   LastChange: 2015-05-06 18:46:30
#      History:
=============================================================================*/
#include "proceed/proceed.h"
#include "kvbf/kvbf.h"
#include "sbf_sigcomm2006/sbf.h"
#include "kbf_infocom2014/kbf.h"
#include<string.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<map>
#include<time.h>
typedef unsigned char byte;
//size_t kvbf_block::cl_num=0;
map<string,byte> mp;
map<int,int> valuecnt;
map<int,int> valuemx;
map<int,int> vmp;
map<int,int>::iterator it;
clock_t start,end;
int mxsize;
ifstream fi;
ofstream fo;
//#define COMPARE_OTHERS
#define hash_default 4
#define cell_default 2772000
#define layer_default 3
#define tms_default 1

int hash_num_begin=hash_default;
int hash_num_end=hash_default;
int cell_begin=cell_default;
int cell_end=cell_default;
int layer_num_per_cell_begin=layer_default;
int layer_num_per_cell_end=layer_default;

int main(int argc,char *argv[]){
    if( argc < 3 ){
        fprintf(stdout,"no input file name or change type\n");
        return 0;
    }
    int p = atoi(argv[2]);
    if( p==0 ){
        printf("please choose hash_num(default %d) range[,]:\n",hash_default);
        scanf("%d%d",&hash_num_begin,&hash_num_end);
    }
    else if( p==1 ){
        printf("please choose cell_num(default %d) range[,]:\n",cell_default);
        scanf("%d%d",&cell_begin,&cell_end);
    }
    else if( p==2 ){
        printf("please choose layer_num(default %d) range[,]:\n",layer_default);
        scanf("%d%d",&layer_num_per_cell_begin,&layer_num_per_cell_end);
    }
    else {
        printf("no %d options\n",p);
        return 0;
    }
    proceed(argv[1]);
    srand(time(NULL));
    fo.open("result_statusbf.out");
	printf("now proceed ends");
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_begin;j<=cell_end;j+=cell_default){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                printf(" in statusbf test: \ntotal cell = %d, hash_num = %d, layer_num = %d\n",j,i,k);
                int statusbf_exist_wrong_query=0 , statusbf_noexist_wrong_query=0;
                int total_query = 0;
                clock_t clk_cnt = 0;
                //KVBF = new kvbf( i , j , k , 1 );
                kvbf_construction( i , j , k , 1 );
                fi.open("data.in");
                mp.clear();
                string s;
                byte statusbf_answer,real_answer,bytev;
                int v;
                while( fi >>s ){
                    total_query++;
                    if( total_query %500000==0 ) printf("proceed = %d\n",total_query);
                    fi>>v;
                    bytev = (byte)v;
                    real_answer=mp[s];

                    // time ************* begin
                    start = clock();
                    //KVBF->get(s.c_str(),&statusbf_answer);
                    kvbf_get(s.c_str(),&statusbf_answer);
                    end = clock();
                    // time ************* end

                    clk_cnt += end - start;
                    if( real_answer != 0 )
                        if(real_answer!=statusbf_answer)
                            statusbf_exist_wrong_query++;
                    if( real_answer == 0 )
                        if(real_answer!=statusbf_answer)
                            statusbf_noexist_wrong_query++;
                    mp[s]=bytev;

                    // time ************ begin
                    start = clock();
                    //if( real_answer > 0) KVBF->del(s.c_str(),&real_answer);
                    //if( v > 0 )KVBF->ins(s.c_str(),&bytev);
                    if( real_answer > 0 ) kvbf_del( s.c_str(),&real_answer );
                    if( v > 0 ) kvbf_ins( s.c_str() , & bytev );
                    end = clock();
                    // time ************ end
                    clk_cnt += end - start;
                }
                printf("total_query=%d\n",total_query);
                double statusbf_false_positive=1.0*statusbf_noexist_wrong_query/total_query,
                       statusbf_false_nagetive=1.0*statusbf_exist_wrong_query/total_query;
                double duration = 1.0*(long long)clk_cnt / CLOCKS_PER_SEC;
                printf("total_query=%d\n",total_query);
                fo<<j<<" "<<i<<" "<<k<<" "<<statusbf_false_positive<<" "<<statusbf_false_nagetive<<" "<<total_query<<" "<<duration<<" "<<duration/total_query<<endl;
                printf(" statusbf_false_positive = %lf statusbf_false_nagetive = %lf duration = %lf total_packet = %d\n duration_per_packet=%lf\n"
                        ,statusbf_false_positive ,statusbf_false_nagetive,duration,total_query,duration/total_query );
                printf("end statusbf test\n");
                fi.close();
                kvbf_destruction();
            }
        }
    }
    fo.close();

    //srand(time(NULL));
    fo.open("result_sbf.out");
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_begin;j<=cell_end;j+=cell_default){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                printf(" in sbf test: \ntotal cell = %d, hash_num = %d\n",j,i);
                int sbf_exist_wrong_query=0 , sbf_noexist_wrong_query=0;
                int total_query=0;
                clock_t clk_cnt=0;
                sbf* SBF;
                SBF = new sbf( i , j );
                fi.open("data.in");
                mp.clear();
                string s;
                byte sbf_answer,real_answer,bytev;
                int v;
                while( fi >>s ){
                    total_query++;
                    if( total_query %500000==0 ) printf("proceed = %d\n",total_query);
                    fi>>v;
                    bytev = (byte)v;
                    real_answer=mp[s];

                    // time ************* begin
                    start = clock();
                    SBF->get(s.c_str(),&sbf_answer);
                    end = clock();
                    // time ************* end

                    clk_cnt += end - start;
                    if( real_answer != 0 )
                        if(real_answer!=sbf_answer)
                            sbf_exist_wrong_query++;
                    if( real_answer == 0 )
                        if(real_answer!=sbf_answer)
                            sbf_noexist_wrong_query++;
                    mp[s]=bytev;

                    // time ************ begin
                    start = clock();
                    if( real_answer > 0 ) SBF->del(s.c_str(),&real_answer);
                    if( v > 0 ) SBF->ins(s.c_str(),&bytev);
                    end = clock();
                    // time ************ end
                    clk_cnt += end - start;
                }
                printf("total_query=%d\n",total_query);
                double sbf_false_positive=1.0*sbf_noexist_wrong_query/total_query,
                       sbf_false_nagetive=1.0*sbf_exist_wrong_query/total_query;
                double duration = 1.0*(long long)clk_cnt / CLOCKS_PER_SEC;
                printf("total_query=%d\n",total_query);
                fo<<j<<" "<<i<<" "<<sbf_false_positive<<" "<<sbf_false_nagetive<<" "<<total_query<<" "<<duration<<" "<<duration/total_query<<endl;
                printf(" sbf_false_positive = %lf sbf_false_nagetive = %lf duration = %lf total_packet = %d\n duration_per_packet=%lf\n"
                        ,sbf_false_positive ,sbf_false_nagetive,duration,total_query,duration/total_query );
                printf("end sbf test\n");
                fi.close();
                delete(SBF);
            }
        }
    }
    fo.close();

    //srand(time(NULL));
    fo.open("result_kbf.out");
    for(int i=hash_num_begin;i<=hash_num_end;i++){
        for(int j=cell_begin;j<=cell_end;j+=cell_default){
            for(int k=layer_num_per_cell_begin;k<=layer_num_per_cell_end;k++){
                printf(" in kbf test: \ntotal cell = %d, hash_num = %d, cell_num=%d\n",j,i,j/i);
                int kbf_exist_wrong_query=0 , kbf_noexist_wrong_query=0;
                int total_query=0;
                clock_t clk_cnt=0;
                kbf * KBF;
                KBF = new kbf( i , j );
                fi.open("data.in");
                mp.clear();
                string s;
                byte kbf_answer,real_answer,bytev;
                int v;
                while( fi >>s ){
                    total_query++;
                    if( total_query %500000==0 ) printf("proceed = %d\n",total_query);
                    fi>>v;
                    bytev = (byte)v;
                    real_answer=mp[s];

                    // time ************* begin
                    start = clock();
                    KBF->get(s.c_str(),&kbf_answer);
                    end = clock();
                    // time ************* end

                    clk_cnt += end - start;
                    //if( real_answer != 0 )
                        //if(real_answer!=kbf_answer)
                            //kbf_exist_wrong_query++;
                    //if( real_answer == 0 )
                        //if(real_answer!=kbf_answer)
                            //kbf_noexist_wrong_query++;
                    if( real_answer != kbf_answer ){
                         if( real_answer != 0 ) kbf_exist_wrong_query++;
                         else kbf_noexist_wrong_query++;
                    }
                    mp[s]=bytev;

                    // time ************ begin
                    start = clock();
                    if( real_answer > 0 )KBF->del(s.c_str(),&real_answer);
                    if( bytev > 0 ) KBF->ins(s.c_str(),&bytev);
                    end = clock();
                    // time ************ end
                    clk_cnt += end - start;
                }
                printf("total_query=%d\n",total_query);
                double kbf_false_positive=1.0*kbf_noexist_wrong_query/total_query,
                       kbf_false_nagetive=1.0*kbf_exist_wrong_query/total_query;
                double duration = 1.0*(long long)clk_cnt / CLOCKS_PER_SEC;
                printf("total_query=%d\n",total_query);
                fo<<j<<" "<<i<<" "<<kbf_false_positive<<" "<<kbf_false_nagetive<<" "<<total_query<<" "<<duration<<" "<<duration/total_query<<endl;
                printf(" kbf_false_positive = %lf kbf_false_nagetive = %lf duration = %lf total_packet = %d\n duration_per_packet=%lf\n"
                        ,kbf_false_positive ,kbf_false_nagetive,duration,total_query,duration/total_query );
                printf("end kbf test\n");
                fi.close();
                delete(KBF);
            }
        }
    }

    fo.close();
    return 0;
}
