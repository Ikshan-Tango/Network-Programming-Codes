// Server program
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    struct sockaddr_in serv, client;

    char str[50];

    int tcp_socket, udp_socket;
    fd_set rset;

    pid_t childpid;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(5000);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    bind(tcp_socket, (struct sockaddr*)&serv, sizeof(serv));
    listen(tcp_socket, 10);
    bind(udp_socket, (struct sockaddr*)&serv, sizeof(serv));

    FD_ZERO(&rset);

    // get maxfd
    int maxfdp1 = max(tcp_socket, udp_socket) + 1;
    for(;;){
        FD_SET(tcp_socket, rset);
        FD_SET(udp_socket, rset);

        //select systemmm call

        select(maxfdp1, rset, NULL, NULL, NULL);

        // if tcp socket is recieved

        if(FD_ISSET(tcp_socket, rset)){
            
            int comm_fd = accept(tcp_socket, (struct sockaddr*) &client, sizeof(client));

            if((childpid = fork()) == 0){
                close(tcp_socket);
                while(1){
                    bzero(str, sizeof(str));
                    read(comm_fd, str, sizeof(str));
                    puts(str);
                    bzero(str);
                    fgets(str, sizeof(str), stdin);
                    write(comm_fd, str, sizeof(str));
                }
                close(comm_fd);
                exit(0);
            }
        }

        if(FD_ISSET(udp_socket, rset)){
            int clilen = sizeof(client);
            bzero(str, sizeof(str));
            recvfrom(udp_socket, str, sizeof(str), 0, (struct sockaddr*) &client, &clilen);

            // normal flow of event 
        }
    }
}