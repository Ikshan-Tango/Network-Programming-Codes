#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/stat.h>

int main(){

    int sock;
    struct sockaddr_in serv;
    char str[100];

    bzero(&serv, sizeof(serv));
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);


    // Add the server to a group now for multicasting
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5");
    mreq.imr_interface.s_addr = INADDR_ANY;
    
    // Set this socket option now
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));


    bind(sock, (struct sockaddr*)&serv, sizeof(serv));

    while(1){
        bzero(str, 100);
        recvfrom(sock, str, 100, 0, NULL, NULL);
        printf("SERV: %s", str);
        if(strstr(str, "bye") != NULL){
            break;
        }

    }
    close(sock);
}