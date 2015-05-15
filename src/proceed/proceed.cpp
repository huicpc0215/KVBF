#include "proceed.h"
#include <set>

ofstream of;
set<int> st;
set<int>::iterator it;

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
        if( ipptr->protocol==IPPROTO_TCP ){
            struct tcphdr* tcpptr = ( struct tcphdr *)(bytes + sizeof( struct ether_header )+
                    sizeof( struct iphdr ) );
            int status=((1&(tcpptr->syn))<<0)|((1&(tcpptr->ack))<<1)|((1&(tcpptr->fin))<<2);
            of<<inet_ntoa(srcaddr)<<"_";
            of<<inet_ntoa(desaddr)<<" "<<((1<<status))<<endl;
            st.insert(status);
        }
        else fprintf(stderr,"now is not tcp protocol\n");
    }
    else fprintf(stderr , "Now is not IP\n");
    //scanf("%s",ts);
}

int proceed(const char *filename){
    of.open("data.in");
    fprintf(stdout,"now proceeding %s ...\n",filename);
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
    for(it=st.begin();it!=st.end();it++){
        fprintf(stdout,"status have %d\n",*it);
    }
    fprintf(stdout,"proceeding  ends\n");

    return 0;
}
