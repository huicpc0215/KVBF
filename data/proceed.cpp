#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/if_ether.h>
#include<pcap.h>
#include<linux/ip.h>
#include<linux/tcp.h>
#include<iostream>
#include<fstream>
using namespace std;
char ts[10];
ofstream of;
void pcap_callback(u_char* user, const struct pcap_pkthdr *h, const u_char * bytes){
    if( bytes == NULL ){
        //printf("now packet is empty!\n");
        return ;
    }
    struct in_addr srcaddr;
    struct in_addr desaddr;
    char * data;
    const struct ether_header * eptr = ( struct ether_header * ) bytes;
    u_char * ptr;
    if( ntohs(eptr-> ether_type) == ETHERTYPE_IP ){
        //printf("Now is IP\n");
        struct iphdr * ipptr=(struct iphdr *)(bytes + sizeof(struct ether_header));
        srcaddr.s_addr=ipptr->saddr;
        desaddr.s_addr=ipptr->daddr;
        if( ipptr->protocol==IPPROTO_TCP ){
            //printf("now is tcp/ip protocol\n");
            //printf("srcip = %s\n",inet_ntoa(srcaddr));
            //printf("desip = %s\n",inet_ntoa(desaddr));
            struct tcphdr* tcpptr = ( struct tcphdr *)(bytes + sizeof( struct ether_header )+
                    sizeof( struct iphdr ) );
            int status=((tcpptr->syn)<<0)|((tcpptr->ack)<<1)|((tcpptr->fin)<<2);
            of<<inet_ntoa(srcaddr)<<" ";
            of<<inet_ntoa(desaddr)<<" "<<status<<endl;
            //printf("status = %d\n",status);
        }
        else fprintf(stderr,"now is not tcp protocol\n");
    }
    else fprintf(stderr , "Now is not IP\n");
    //scanf("%s",ts);
}

int main(int argc,char *argv[]){
    if( argc < 2 ){
        fprintf(stdout,"please input pcap file name\n");
        return 0;
    }
    of.open("all.out");
    fprintf(stdout,"pcap file name = %s \n",argv[1]);
    char str[100];
    char ebuf[PCAP_ERRBUF_SIZE];
    char filter_rgx[]="tcp";
    struct bpf_program filter;
    pcap_t *handle =  NULL ;
    handle = pcap_open_offline(argv[1],ebuf);
    if( NULL == handle ){
        fprintf(stderr,"Error:%s\n",ebuf);
        return (EXIT_FAILURE);
    }
    // compile the regluar expression
    if(pcap_compile( handle , &filter , filter_rgx , 1 , 0 )!=0){
        fprintf(stderr , " compile regluar expression error \n");
        return 0;
    }

    // set the regular expression
    if(pcap_setfilter(handle,&filter)!=0){
        fprintf(stderr , " set regular expression error \n");
        return 0;
    }

    pcap_loop( handle , -1 , pcap_callback , NULL);

    pcap_close(handle);
    return 0;
}
