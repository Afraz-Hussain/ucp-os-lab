// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	listen (sockfd,5);
	int newfd;
	while(1)
	{
		int len= sizeof(cliaddr), n; 
		newfd= accept(sockfd, (struct sockaddr*) &cliaddr, &len);
		
		n = recv(newfd, (char *)buffer, MAXLINE,0); 
		buffer[n] = '\0'; 
		
		printf("Client : %s\n", buffer); 
		// Decryption
		for(int i=0;i!=8;++i)
		{
		   if(buffer[i] >= 65 && buffer[i] <= 90 && buffer[i] != '\0')
				buffer[i] = buffer[i] - 3; 
		   else if(buffer[i] >= 97 && buffer[i] <= 122 && buffer[i] != '\0')
				buffer[i] = buffer[i] - 2;
		   else
			buffer[i]=buffer[i]-1;
		}



		hello=&buffer[0];
		
		send(newfd, (const char *)hello, strlen(hello),0); 
		printf("Decrypted message sent.\n"); 
		close(newfd);
	}
	return 0; 
} 

