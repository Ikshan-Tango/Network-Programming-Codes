#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

//Include appropriate header files.

// 2 5 1 3 7
// 2 5 1 3 7
// 2 1 5 3 7 
// 2 1 3 5 7
// 2 1 3 5 7 


void sort(int *arr, int size){
    //bubble sort -> choose the largest number and send it to last
    int i,j;
    
    for(i=0; i<size;i++){
        for(j = 1; j<size; j++){
            if(arr[j-1] > arr[j]){
                //swap

                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}

int convert(char str[50]){
    return atoi(str);
}

int main(){

    char str[50];
    int arr[3];
    int size = 3;
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
    int count = 0;

    // receive from the client
    recv(comm_fd, str, 50, 0);
    arr[count] = convert(str);
    count++;

    // print the message received from the client
    printf("CLIENT: %s\n", str);

    while (count!=size)
    {        
        // printf("SERVER:");
        bzero(str, 50);


        // str = "";
        // send(comm_fd, str, strlen(str), 0);

        // bzero(str, 50);
        recv(comm_fd, str, 50, 0);

        printf("CLIENT: %s\n", str);
        arr[count] = convert(str);
        count++;
    }
    
    int *ptr = arr;
    
    sort(ptr,size);
    printf("The sorted array is: ");
    for(int i=0; i<size;i++){
        printf("%d ", arr[i]);
    }

    close(comm_fd);
    close(sockid);
}