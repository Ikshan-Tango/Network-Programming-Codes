#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

//Include appropriate header files.

int main(){

    char str[50];
    // create a socket

    int sockid;
    sockid = socket(AF_INET, SOCK_STREAM, 0); 

    // make a server 
    struct sockaddr_in serv;
    bzero(&serv, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(8001);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind the address and port 
    bind(sockid, (struct sockaddr *)&serv, sizeof(serv));

    //listen() system call 
    listen(sockid, 10);

    //accept system call
    int comm_fd;

    comm_fd = accept(sockid, (struct sockaddr*) NULL, NULL);

    //normal process flow of communication 

    bzero(str, 50);

    // receive from the client
    recv(comm_fd, str, 50, 0);

    // print the message received from the client
    printf("CLIENT: %s\n", str);

    while (strstr(str, "exit")== NULL)
    {        
        printf("SERVER:");
        bzero(str, 50);

        fgets(str, 50, stdin);
        send(comm_fd, str, strlen(str), 0);

        bzero(str, 50);
        recv(comm_fd, str, 50, 0);

        printf("CLIENT: %s\n", str);
    }

    close(comm_fd);
    close(sockid);
}