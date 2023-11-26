// Multicasting code of server side
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int sock;
    struct sockaddr_in serv;

    char str[100];
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    serv.sin_addr.s_addr = inet_addr("224.1.1.5"); // 224.1.1.5 belongs to class D which is used for multicasting
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);

    // Add the server to a group now for multicasting
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5");
    mreq.imr_interface.s_addr = INADDR_ANY;
    
    // Set this socket option now
    setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

        while (1)
    {
        bzero(str, 100);
        printf("Do you want to send data: ");
        fgets(str, 100, stdin);

        if(strncmp(str, "yes", 3) == 0){
            bzero(str, sizeof(str));

            printf("Enter data: ");
            fgets(str, 100, stdin);

            sendto(sock, str, sizeof(str), 0, (struct sockaddr*)&serv, sizeof(serv));

        }
        else{
            bzero(str, sizeof(str));
            strcpy(str, "bye");
            sendto(sock, str, sizeof(str), 0, (struct sockaddr*)&serv, sizeof(serv));
            break;
        }
            
    }
    close(sock);

}