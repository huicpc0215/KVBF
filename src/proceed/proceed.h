#ifndef PROCEED_H
#define PROCEED_H

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

//recall function to pcap_loop
void pcap_callback(u_char *user,const struct pcap_pkthdr *h,const u_char *bytes);

//proceed function
int proceed(const char * filename);

#endif
