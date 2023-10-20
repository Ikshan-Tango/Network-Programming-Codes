#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
	char str1[50], str2[50];
	struct sockaddr_in serv;
	
	bzero(&serv, sizeof(serv));
	
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	int serv_len = sizeof(serv);
	while(1){
		fgets(str1, 50, stdin);
		sendto(sock, str1, 50, 0, (struct sockaddr* )&serv, serv_len);
		printf("CLIENT: %s", str1);
		if(strstr(str1, "bye")!=NULL){
			break;
		}
		printf("here 1\n");
		bzero(str2, 50);
		recvfrom(sock, str2, 50, 0, (struct sockaddr* )&serv, &serv_len);
		printf("here 2\n");
		printf("SERVER: %s", str2);
		bzero(str1, 50);		

	}
	close(sock);
	printf("CLOSING CLIENT!\n");
	
	return 0;
}
