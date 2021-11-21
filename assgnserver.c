#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> //WRITE
#include <time.h>

#define BACKLOG 5	//TO SPECIFIES THE NUMBER OF PENDING CONNECTIONS THE QUEUE 
			//WILL HOLD
int main(int argc, char *argv[])
{
	if(argc != 2)//TO DISPLAY AN ERROR IF THE NUMBER OF COMMAND LINE ARGUMENTS IS NOT 2
	{
		printf("Usage: %s <port>\n", argv[0]);
		exit(0);
	}

	int portnum = atoi(argv[1]);	//TO CONVERT CHAR STRING TO AN INT VALUE
	printf("Port Number: %d\n", portnum);
	
	int sock_desc;
	struct sockaddr_in server;

	//CREATING SOCKET
	sock_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_desc == -1)
	{
		printf("SOCKET FAILED TO CREATE!!!");
	}

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons( portnum );

	//BIND
	if(bind(sock_desc,(struct sockaddr*)&server,sizeof(server))<0)
	{
		puts("BIND FAILED");
		return 1;
	}
	puts("BIND SUCCESS");

	//LISTEN
	listen(sock_desc,BACKLOG);
	
	//SEND BACK THE REQUEST TO CLIENT
	int clientcount;
	int i = 1;
	while(i)
	{
		int client_sock = accept(sock_desc,NULL, NULL);
		time_t currTime; //TO DEFINE currTime TO STORE SYSTEM TIME VALUE
		time(&currTime); //TO RETURN CURRENT CALENDAR TIME AS A OBJECT OF TYPE time_t
		clientcount++;
		//TO DISPLAY THE LIST OF CLIENT, THAT REQUESTED FOR TIME
		printf("Client %d  requested for time at %s",clientcount, ctime(&currTime));
		//TO SEND BACK THE DAYTIME TO THE CLIENT
		send(client_sock, ctime(&currTime), 100, 0);
	}
	return 0;
}
/*SOURCES AND REFERENCES USED IN ORDER TO COMPLETE THIS INDIVIDUAL ASSIGNMENT
1. https://github.com/nikhilroxtomar/Day-Time-Sever-Client-in-C/blob/master/server.c
2. ITT440 LAB ACTIVITIES*/
