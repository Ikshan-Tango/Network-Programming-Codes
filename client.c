#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    char str[50];
    int sock;

    struct sockaddr_in serv;
    sock = socket(AF_INET, SOCK_STREAM, 0); // we are using the TCP protocol

    bzero(&serv, sizeof(serv)); // initialise serv to 0
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345); // htons converts host to network byte order
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); // SERVER IS LISTENING FROM ALL AVAILABLE INTERFACES

    // connect to the server
    connect(sock, (struct sockaddr *) &serv, sizeof(serv));;

    // read and write to the socket, initialise str to 0
    bzero(str, 50);

    // send a message to the server
    printf("Enter a message to send to the server: ");
    fgets(str, 50, stdin);

    send(sock, str, strlen(str), 0);

    while (strstr(str, "bye") == NULL)
    {
        // receive from the server
        recv(sock, str, 50, 0);

        // print the message received from the server
        printf("Message received from server: %s\n", str);

        // send a message to the server
        printf("Enter a message to send to the server: ");
        bzero(str, 50);

        fgets(str, 50, stdin);
        send(sock, str, strlen(str), 0);

    }

    // close the socket
    close(sock);
    printf("Client closed\n");    
}
