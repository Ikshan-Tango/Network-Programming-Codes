#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<netdb.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int b = 1, sock;
    struct sockaddr_in serv;

    char str[100];
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &b, sizeof(b));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("255.255.255.255");

    // bind(sock, (struct sockaddr *)&serv, sizeof(serv));

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