#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<sys/socket.h>

int count(char str[50]){
    int i;
    char vow[5] = {'A', 'E', 'I', 'O', 'U'};
    int count=0;

    for(i=0; i<50;i++){
        int j;
        int flag = 0;
        for(j=0; j<5;j++){
            if(str[i] == vow[j])
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            count+=1;
    }

    return count;
}

int main(){
    char str[50];

    struct sockaddr_in serv;
    int listen_fd, comm_fd;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv, sizeof(serv));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listen_fd, (struct sockaddr*) &serv, sizeof(serv));

    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    bzero(str, 50);

    recv(comm_fd, str, 50, 0);
    printf("CLIENT :%s", str);

    while(strstr(str, "bye")==NULL){
        printf("Server:");

        int to_send = count(str);
        bzero(str, 50);
        sprintf(str, "%d", to_send);
        send(comm_fd, str, 50, 0);

        bzero(str, 50);
        recv(comm_fd, str, 50, 0);
        printf("CLIENT :%s", str);
    }
    close(comm_fd);
    close(listen_fd);
    printf("Server closed");
}