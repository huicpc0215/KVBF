#include "proceed.h"
#include <set>
#include <string.h>
#include <map>

ofstream of;
set<int> st;
set<int>::iterator st_it;
map<int,int> tms;
struct timeval starttime;
struct timeval endtime;
bool FirstCapture=true;
int flowcnt=0;
int tcpflowcnt=0;
int ipflowcnt=0;
void pcap_callback(u_char* user, const struct pcap_pkthdr *h, const u_char * bytes){
    if( bytes == NULL ){
        return ;
    }
    if(FirstCapture){
        FirstCapture=false;
        starttime=h->ts;
    }
    endtime=h->ts;
	if( flowcnt% 500000 == 0 )
		printf(" flowcnt = %d\n",flowcnt);
	flowcnt++;
    struct in_addr srcaddr;
    struct in_addr desaddr;
    char * data;
    const struct ether_header * eptr = ( struct ether_header * ) bytes;
    u_char * ptr;
	fprintf(stdout , "ETHERTYPE_IP == %hx\n",ETHERTYPE_IP );
	fprintf(stdout , "now_type == %hx\n", ntohs(eptr-> ether_type) );
	for( int i=0;i<6;i++){
		fprintf(stdout , "now_src mac == %x \n", eptr->ether_shost[i]);
	}
    if( ntohs(eptr-> ether_type) == ETHERTYPE_IP ){
        struct iphdr * ipptr=(struct iphdr *)(bytes + sizeof(struct ether_header));
		ipflowcnt++;
        srcaddr.s_addr=ipptr->saddr;
        desaddr.s_addr=ipptr->daddr;
        if( ipptr->version == 4 && ipptr->protocol== IPPROTO_TCP ){
			tcpflowcnt++;
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
        //else fprintf(stderr,"now is not tcp protocol\n");
    }
	else if( ntohs(eptr-> ether_type) == 0 ){
        struct iphdr * ipptr=(struct iphdr *)(bytes + sizeof(struct ether_header)+2);
		ipflowcnt++;
        srcaddr.s_addr=ipptr->saddr;
        desaddr.s_addr=ipptr->daddr;
        if( ipptr->version == 4 && ipptr->protocol== IPPROTO_TCP ){
			tcpflowcnt++;
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
        else {
			fprintf(stderr,"now is not tcp protocol\n");
			while(1);	
		}
	}
    else {
		fprintf(stdout , "Now is not IP == %hx\n",ntohs(eptr->ether_type) );
		while(1);
	}
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
    //if(pcap_compile( handle , &filter , filter_rgx , 1 , 0 )!=0){
    //    fprintf(stderr , " compile regluar expression error \n");
    //    return -1;
    //}

    // set the regular expression
    //if(pcap_setfilter(handle,&filter)!=0){
    //    fprintf(stderr , " set regular expression error \n");
    //    return -1;
    //}

    pcap_loop( handle , -1 , pcap_callback , NULL);
    pcap_close(handle);
    for(st_it=st.begin();st_it!=st.end();st_it++){
        fprintf(stdout,"status have %d times=%d\n",*st_it,tms[*st_it]);
    }
	printf("packets=%d , tcp packets=%d, ip packets=%d\n",flowcnt,tcpflowcnt,ipflowcnt);
    printf("packet start at: \n");
    struct tm * timeinfo;
    timeinfo = localtime(&starttime.tv_sec);
    printf("%s",asctime(timeinfo));
    timeinfo = localtime(&endtime.tv_sec);
    printf("packet end at: \n");
    printf("%s",asctime(timeinfo));
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
	//exit(0);
    return 0;
}
