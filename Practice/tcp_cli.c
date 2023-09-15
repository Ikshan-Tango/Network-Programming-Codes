#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(){

    int sock_id;
    char str[50];

    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_id, (struct sockaddr*) &serv, sizeof(serv));

    bzero(str, 50);
    printf("CLIENT:");
    fgets(str, 50, stdin);
    send(sock_id ,str, 50,0);

    while(strstr(str, "bye")==NULL){
        bzero(str, 50);

        recv(sock_id, str, 50, 0);
        printf("SERVER:%s", str);
        bzero(str, 50);

        printf("CLIENT:");
        fgets(str, 50, stdin);
        send(sock_id ,str, 50,0);

    }
    close(sock_id);
    printf("Client closed");
}