// Server side implementation of TCP client-server model 
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
#define NO_OF_CHARS 256

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello;
	char *hello1; 
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
	int i;
	while(1)
	{
		int len= sizeof(cliaddr), n; 
		newfd= accept(sockfd, (struct sockaddr*) &cliaddr, &len);
		
		int p_id;
		p_id= fork();
		i=1;
		if(p_id == 0)
		{
			close(sockfd);
			n = recv(newfd, (char *)buffer, MAXLINE,0); 
			buffer[n] = '\0'; 
			printf("Client with port %d: %s\n",ntohs(cliaddr.sin_port),  buffer); 
			//printf("Client %d",i," with port %d: %s\n",ntohs(cliaddr.sin_port),  buffer);
			//i++;
			int count[NO_OF_CHARS] = { 0 };
			for (int i = 0; buffer[i]; i++)
				count[buffer[i]]++;
			int odd = 0;
			for (int i = 0; i < NO_OF_CHARS; i++) 
			{
				if (count[i] & 1)
					odd++;

				if (odd > 1)
					hello="string cannot be a plaindrom\n";
			}

			
			hello="string can be a plaindrom\n";


			send(newfd, (const char *)hello, strlen(hello),0); 
			printf("\nInformation message sent.\n"); 
			close(newfd);
			exit(-1);
		}
		if(p_id > 0)
		{
			close(newfd);
			//exit();
		}
		else
		{
			printf("Fork call failed\n");
		}
	}
	return 0; 
} 

