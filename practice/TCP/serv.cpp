#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
    char str[50];
    struct sockaddr_in serv;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr*)&serv, sizeof(serv));

    listen(sock, 10);

    int comm_fd = accept(sock, (struct sockaddr*) NULL, NULL);

    while(1){
        bzero(str , 50);
        recv(comm_fd, str, 50, 0);
        printf("CLIENT: %s", str);

        if(strstr(str, "bye")!=NULL){
            break;
        }

        bzero(str, 50);
        printf("SERVER: ");
        fgets(str, 50, stdin);

        send(comm_fd, str, 50, 0);
    }

    close(comm_fd);
    close(sock);
}