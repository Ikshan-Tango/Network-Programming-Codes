#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    char str[50];

    int sock_id;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8001);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_id,(struct sockaddr *)&serv, sizeof(serv));

    bzero(str, 50);
    printf("CLIENT:");
    fgets(str, 50, stdin);

    send(sock_id, str, strlen(str), 0);

    int count = 1;

    while(count != 4){
        // recv(sock_id, str, 50, 0);

        // print the message received from the server
        // printf("Enter another number:");
        // printf("SERVER: %s\n", str);

        // send a message to the server
        printf("Enter another number: ");
        bzero(str, 50);

        fgets(str, 50, stdin);
        send(sock_id, str, strlen(str), 0);
        count ++;
    }
    printf("Sent all numbers now closing!");
    close(sock_id);
}