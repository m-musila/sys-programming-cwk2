#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/utsname.h>
#include <dirent.h>


//  **** Obtain your Student ID from the server prefixed by the server IP address ****

// get hostname for the server
void getHostName(int hostname)
{
	if (hostname == -1)
	{
		perror("gethostname");
		exit(EXIT_FAILURE);
	}
}

// get host information this server 
void getHostEntry(struct hostent * hostentry)
{
	if (hostentry == NULL)
	{
		perror("gethostbyname");
		exit(EXIT_FAILURE);
	}
}

// Convert IPv4 address to decimal format
void getIPbuffer(char *IPbuffer)
{
	if (NULL == IPbuffer)
	{
		perror("inet_ntoa");
		exit(EXIT_FAILURE);
	}
}

// **** Obtain 5 random numbers and pass it back to the client. ****
int *randomNumbers() { 
	// make available throughout program using static. Hence the function returns the actual memory location of the variable 'randomArr'
	static int randomArr[5];
	
	for (int i = 0; i < 5; i++)
	{
		randomArr[i] = rand() % 1000 + 1;
	}
	return randomArr;
}

// **** Obtain the server \u201cuname\u201d information and pass it back to the client. ****
void ServerUnameInformation() {
	struct utsname uts;

    	if (uname(&uts) == -1) {
		perror("uname error");
		exit(EXIT_FAILURE);
    	}
	
	printf("Server uname information\n");
    	printf("Node name:    %s\n", uts.nodename);
    	printf("System name:  %s\n", uts.sysname);
    	printf("Release:      %s\n", uts.release);
    	printf("Version:      %s\n", uts.version);
    	printf("Machine:      %s\n", uts.machine);

}

// **** Obtain file names in the server current working directory and pass them back to the client. ****
void serverFileNames()
{
    DIR *dir;
    if ((dir = opendir(".")) == NULL) {
	perror("error");
	exit(EXIT_FAILURE);
    }

    struct dirent *entry = NULL;
    
    printf("File and Subdirectories in Server\n");
    // returns NULL when dir contents all processed
    while ((entry = readdir(dir)) != NULL) 
	printf("%s\n", entry->d_name);

}

int main(void)
{
    printf("\n\n\t\tClient-Server Communication\n\n");
    int choice;
    
    while(1)
    {
    	printf("\n\n\n");
    	printf("*-----------------------------------------------*\n");
        printf("Get specific data from server through client\n");
		printf("1. Student ID\n");
        printf("2. Random Numbers\n");
        printf("3. Server File and Directory Names\n");
		printf("4. Uname Server Information\n");
        printf("5. Exit Programme\n\n");
        printf("Enter your choice :  \n");
        printf("*-----------------------------------------------*\n\n");
        
        
        scanf("%d",&choice);
        
        
        switch(choice)
        {
        case 1:
		//  ****** Obtain your Student ID from the server prefixed by the server IP address ***
		printf("\n");
		char ID[50] = " s2034964";
        	char hostbuffer[256];
		char *IPbuffer;
		struct hostent *host_entry;
		int hostname;

		// get hostname
		hostname = gethostname(hostbuffer, sizeof(hostbuffer));
		getHostName(hostname);

		//get host information
		host_entry = gethostbyname(hostbuffer);
		getHostEntry(host_entry);

		// ASCII string
		IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

    		//concatenates student ID and server IP
    		strcat(IPbuffer, ID);
    		printf("Concatenated student ID and server IP: %s\n", IPbuffer);
                
        break;
        case 2:
		// **** Obtain 5 random numbers and pass it back to the client. ****
		printf("\n");

		int *pointerToArray = randomNumbers();
		printf("The 5 random numbers generated are: \n");
		for (int i = 0; i < 5; i++)
		{
			printf("%i\n", pointerToArray[i]);
		}
	break;
	case 3:
		// **** Obtain file names in the server current working directory and pass them back to the client. ****
	        printf("\n");
		serverFileNames();
	break;
        case 4:
                // **** Obtain the server \u201cuname\u201d information and pass it back to the client. ****
		printf("\n");
		ServerUnameInformation();   
        break;
        case 5:
                printf("\n\n\t\t\tExited is client programme!\n\n\n");
                exit(0);    // terminates programme
	
	default:
		printf("Try again! Your entry is not part of the menu");
	break;	
        }
    }
    return 0;
}