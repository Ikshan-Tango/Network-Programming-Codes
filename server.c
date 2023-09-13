#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    char str[50];
    int listen_fd , comm_fd;

    struct sockaddr_in serv;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); // we are using the TCP protocol

    bzero(&serv, sizeof(serv)); // initialise serv to 0

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345); // htons converts host to network byte order
    serv.sin_addr.s_addr = htonl(INADDR_ANY); // SERVER IS LISTENING FROM ALL AVAILABLE INTERFACES
    //binding the socket to this server

    bind(listen_fd, (struct sockaddr *) &serv, sizeof(serv));

    //server will listen now to the socket
    listen(listen_fd, 10); // 10 is the maximum number of clients that can be queued

    //accepting the connection
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // server is accessing the connection without knowing the client's address and size of address


    // read and write to the socket, initialise str to 0
    
    bzero(str, 50);

    // receive from the client
    recv(comm_fd, str, 50, 0);

    // print the message received from the client
    printf("Message from client: %s\n", str);

    while (strstr(str, "bye") == NULL)
    {
        // send a message to the client
        printf("Enter a message to send to the client: ");
        bzero(str, 50);

        fgets(str, 50, stdin);
        send(comm_fd, str, strlen(str), 0);

        // receive from the client
        bzero(str, 50);
        recv(comm_fd, str, 50, 0);
        printf("Message Recieved from client: %s\n", str);
    }
    

    // close the socket
    close(comm_fd);
    close(listen_fd);
    printf("Server closed\n");
}