/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 128 
#define RSIZ 10 

int main(void) 
{
    char line[RSIZ][LSIZ];
    char line2[RSIZ][LSIZ];
	char fname[20];
    FILE *fptr = NULL; 
    int i = 0;
    int tot = 0;
    printf("\n\n Read the file and store the lines into an array :\n");
	printf("------------------------------------------------------\n"); 
	printf(" Input the filename to be opened : ");
	scanf("%s",fname);	

    fptr = fopen(fname, "r");
    while(fgets(line[i], LSIZ, fptr)) 
	{
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;
	printf("\n The content of the file %s  are : \n",fname);    
    for(i = 0; i < tot; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");

	for(i=0;i<tot;++i)
	{
	   if(i < 100 && line[i] != '\0')
        		line[i] = line[i] + 3; 
	   else if(i > 100 && line[i] != '\0')
			line[i] = line[i] + 2;
	   else
		line[i]=line[i]+1;
	}

	printf("\n The content of the file after %s  are : \n",fname);    
    for(i = 0; i < tot; ++i)
    {
        printf(" %s\n", line[i]);
    }
    printf("\n");
	
    return 0;
}*/




#include <stdio.h>
#include <stdlib.h> // For exit() function
int main() {
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
    fclose(fptr);

    return 0;
}
