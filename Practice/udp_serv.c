#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(){
	char str[50];
	struct sockaddr_in serv, client;
	int sock;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(1234);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sock, (struct sockaddr*)&serv, sizeof(serv));
	int cli_len = sizeof(client);
	
	while(1){
		recvfrom(sock, str, 50, 0,(struct sockaddr*) &client, &cli_len);
		printf("CLIENT:%s", str);
		
		if(strstr(str, "bye") != NULL){
			break;
		}
		
		bzero(str,50);
		
		printf("SERVER:");
		fgets(str, 50, stdin);
		sendto(sock, str, 50, 0,(struct sockaddr*) &client, sizeof(client));
	}
	close(sock);
	return 0;
}
