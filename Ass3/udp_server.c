#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int convert(char *str) {
    int num = atoi(str);
    return num;
}

int main(){

    int sock, clientLen;

    int num1,num2;

    struct sockaddr_in serv, cli;
    char str[100];

    bzero(str, 100);
    bzero(&serv, sizeof(serv));

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock,( struct sockaddr*) &serv, sizeof(serv));

    clientLen = sizeof(cli);
    recvfrom(sock,str, 100, 0, (struct sockaddr *)&cli, &clientLen);
    num1 = convert(str);
    printf("num1 = %d\n", num1);

    char* clientip = inet_ntoa(cli.sin_addr); //network byte to ascii conversion
    printf("Client IP address is %s\n", clientip);
    printf("Recieved data is %s\n", str); 


    while(strstr(str, "bye") == NULL){
        bzero(str, 100);
        fgets(str, 100, stdin);

        sendto(sock, str, sizeof(str), 0, (struct sockaddr*) &cli, clientLen);

        recvfrom(sock,str, 100, 0, (struct sockaddr *)&cli, &clientLen);
        num2 = convert(str);
        printf("num2 = %d\n", num2);
        printf("Total = %d\n", num1+num2);
        
        char* clientip = inet_ntoa(cli.sin_addr); //network byte to ascii conversion
        printf("Client IP address is %s \n", clientip);
        printf("Recieved data is %s \n", str);
    }

    close(sock);
}