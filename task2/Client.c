// Client side implementation of UDP client-server model 
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
	char *hello = "Hello from client"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	connect (sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)); 
	int n, len; 
	// file

	char c[1000];
    FILE *fptr;
    if ((fptr = fopen("fileData.txt", "r")) == NULL) 
	{
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);
    }

    // reads text until newline is encountered
    fscanf(fptr, "%[^\n]", c);
    printf("Data from the file:\n%s", c);

	 printf("\n");

	for(int i=0;i!=8;++i)
	{
	   if(c[i] >= 65 && c[i] <= 90 && c[i] != '\0')
        		c[i] = c[i] + 3; 
	   else if(c[i] >= 97 && c[i] <= 122 && c[i] != '\0')
			c[i] = c[i] + 2;
	   else
		c[i]=c[i]+1;
	}
	 printf("Encrypted Data from the file:\n%s", c);
	printf("\n");
        
	hello=&c[0];
	
	// sending to server
	send(sockfd, (const char *)hello, strlen(hello),0); 
	printf("Encrypted message sent to server.\n"); 
		
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0'; 
	printf("Decrypted message from Server : %s\n", buffer); 
	
	
	close(sockfd); 
	fclose(fptr);
	return 0; 
} 

