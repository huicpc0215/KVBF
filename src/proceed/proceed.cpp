#include "proceed.h"
#include <set>
#include <string.h>
#include <map>

ofstream of;
set<int> st;
set<int>::iterator st_it;
map<int,int> tms;
void pcap_callback(u_char* user, const struct pcap_pkthdr *h, const u_char * bytes){
    if( bytes == NULL ){
        return ;
    }
    struct in_addr srcaddr;
    struct in_addr desaddr;
    char * data;
    const struct ether_header * eptr = ( struct ether_header * ) bytes;
    u_char * ptr;
    if( ntohs(eptr-> ether_type) == ETHERTYPE_IP ){
        struct iphdr * ipptr=(struct iphdr *)(bytes + sizeof(struct ether_header));
        srcaddr.s_addr=ipptr->saddr;
        desaddr.s_addr=ipptr->daddr;
        if( ipptr->version == 4 && ipptr->protocol== IPPROTO_TCP ){
            struct tcphdr* tcpptr = ( struct tcphdr *)(bytes + sizeof( struct ether_header )+
                    sizeof( struct iphdr ) );
            int status=((1&(tcpptr->syn))<<0)|((1&(tcpptr->ack))<<1)|((1&(tcpptr->rst))<<2);
            //printf("source = %s,%d \n",inet_ntoa(srcaddr),ntohs(tcpptr->source));
            //printf("dest = %s,%d \n",inet_ntoa(desaddr),ntohs(tcpptr->dest));
            of<<inet_ntoa(srcaddr)<<"_";
            of<<ntohs(tcpptr->source)<<"_";
            of<<inet_ntoa(desaddr)<<"_";
            of<<ntohs(tcpptr->dest)<<" ";
            if( tcpptr->fin ) of<<0<<endl;
            else of<<((1<<status))<<endl;
            st.insert(1<<status);
            tms[1<<status]++;
        }
        else fprintf(stderr,"now is not tcp protocol\n");
    }
    else fprintf(stderr , "Now is not IP\n");
}

int proceed(const char *filename){
    of.open("data.in");
    fprintf(stdout,"now proceeding %s ...\n",filename);
    for(int i=0;i<10;i++)tms[i]=0;
    char str[100];
    char ebuf[PCAP_ERRBUF_SIZE];
    char filter_rgx[]="tcp";
    struct bpf_program filter;
    pcap_t *handle =  NULL ;
    handle = pcap_open_offline(filename,ebuf);
    if( NULL == handle ){
        fprintf(stderr,"Error:%s\n",ebuf);
        return -1;
    }
    // compile the regluar expression
    if(pcap_compile( handle , &filter , filter_rgx , 1 , 0 )!=0){
        fprintf(stderr , " compile regluar expression error \n");
        return -1;
    }

    // set the regular expression
    if(pcap_setfilter(handle,&filter)!=0){
        fprintf(stderr , " set regular expression error \n");
        return -1;
    }

    pcap_loop( handle , -1 , pcap_callback , NULL);
    pcap_close(handle);
    for(st_it=st.begin();st_it!=st.end();st_it++){
        fprintf(stdout,"status have %d times=%d\n",*st_it,tms[*st_it]);
    }
    fprintf(stdout,"proceeding  ends\n");
    ifstream fii;
    fii.open("data.in");
    string strings;
    int v;
    int maxsize=0;
    map<string,int> mp;
    while(fii>>strings){
        fii>>v;
        mp[strings]=v;
        if(v==0){
            if( mp.find(strings) != mp.end() )
                mp.erase( mp.find(strings) );
        }
        maxsize = max( (int)mp.size() , maxsize );
    }
    printf(" maxsize = %d\n",maxsize);
    fii.close();
    return 0;
}
