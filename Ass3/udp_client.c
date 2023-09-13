#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    int temp;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
   
int main(){
    int sock;
    struct sockaddr_in serv;
    char strsend[100], strrecv[100];

    bzero(strsend, 100);
    bzero(strrecv, 100);
    bzero(&serv, sizeof(serv));

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    int serv_len = sizeof(serv);
    
    while(1){
        fgets(strsend, 100, stdin);
        sendto(sock, strsend, strlen(strsend), 0, (struct sockaddr *) &serv, serv_len);
        printf("Sent message to Server -> %s \n", strsend);

        if(strstr(strsend,"bye") !=NULL)
            break;
        
        bzero(strsend, 100);
        recvfrom(sock, strrecv, 100, 0, (struct sockaddr *) &serv, &serv_len);
        printf("Received data is %s \n", strrecv);
        bzero(strrecv, 100);
    }

    close(sock);
}