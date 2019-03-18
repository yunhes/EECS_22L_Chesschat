/* GTK_ClockClient.c: GUI example interactive TCP/IP client for ClockServer
 * Author: Rainer Doemer, 2/22/17 (based on simple ClockClient.c)
 */

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "ClientList.h"
#include "simple.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>
#include "ClientList.h"
#include "ChatStruct.h"
//#include "ServerFunctions.h"
#include <poll.h>
#include "Client.h"

CLIENT *clientglobal;

char ChessRequest_UN[20];
char FriendName[20];



/* #define DEBUG */	/* be verbose */
#define BUFFSIZE 5000

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
struct sockaddr_in
	ServerAddress;	/* server address we connect with */

/*** global functions ****************************************************/

void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

char *Talk2Server(		/* communicate with the server */
	const char *Message,
	char *RecvBuf)
{
    int n;
    int SocketFD;

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFD < 0)
    {   FatalError("socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Connecting to the server at port %d...\n",
		Program, ntohs(ServerAddress.sin_port));
#endif
    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		sizeof(struct sockaddr_in)) < 0)
    {   FatalError("connecting to server failed");
    }
#ifdef DEBUG
    printf("%s: Sending message '%s'...\n", Program, Message);
#endif
    n = write(SocketFD, Message, strlen(Message));
    if (n < 0)
    {   FatalError("writing to socket failed");
    }
#ifdef DEBUG
    printf("%s: Waiting for response...\n", Program);
#endif
    n = read(SocketFD, RecvBuf, BUFFSIZE-1);
    if (n < 0) 
    {   FatalError("reading from socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received response: %s\n", Program, RecvBuf);
    printf("%s: Closing the connection...\n", Program);
#endif
    close(SocketFD);
    return(RecvBuf);
} /* end of Talk2Server */


int main(			/* the main function */
	int argc,
	char *argv[])
{
    //struct pollfd mypoll = {STDIN_FILENO,POLLIN|POLLPRI};

    char recieve[5000];
    char send[5000];

    int PortNo;
    struct hostent *Server;
    clientglobal = CreateClient(); 
    FENTRYC *f;
    f = CreateClientFriend("nima13");
    AppendClientFriend(clientglobal->friendlist,f);
    Program = argv[0];
#ifdef DEBUG
    printf("%s: Starting...\n", argv[0]);
#endif
    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", Program);
	exit(10);
    }
    Server = gethostbyname(argv[1]);
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];

       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHello How are you James?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
  printf("Parsing now:\n");
       Parsing(recieve,strlen(recieve));



 
/*
       printf("Login request:\n");
            strcpy(send,"L_I\n");
            strcat(send,"sally66\n");
            strcat(send,"password\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);



       printf("Registration request:\n");
            strcpy(send,"R_E_G\n");
            strcat(send,"matt55\n");
            strcat(send,"55&&8hello\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Registration request:\n");
            strcpy(send,"R_E_G\n");
            strcat(send,"melissa77\n");
            strcat(send,"mel778\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Registration request:\n");
            strcpy(send,"R_E_G\n");
            strcat(send,"sally83\n");
            strcat(send,"password\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);



       printf("Login request:\n");
            strcpy(send,"L_I\n");
            strcat(send,"sally83\n");
            strcat(send,"password\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
*/

            
       printf("Login request:\n");
            strcpy(send,"L_I\n");
            strcat(send,"james10\n");
            strcat(send,"password\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));


       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nWhats up\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));





printf("*************Username for first client: %s\n",clientglobal->friendlist->first->username);

printf("*************FirstMessage for nima13: %s\n",clientglobal->friendlist->first->history->first->message);
       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));




       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHow are you?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));


printf("*************FirstMessage for nima13: %s\n",clientglobal->friendlist->first->history->first->message);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));



       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nmsg2?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));


printf("*************FirstMessage for nima13: %s\n",clientglobal->friendlist->first->history->first->message);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));



       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHellou?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));


printf("*************FirstMessage for nima13: %s\n",clientglobal->friendlist->first->history->first->message);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));



       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nYo man?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
       Parsing(recieve,strlen(recieve));








       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

  printf("Parsing now:\n");
       Parsing(recieve,strlen(recieve));

printf("*************Username for first client: %s\n",clientglobal->friendlist->first->username);
printf("*************FirstMessage for nima13: %s\n",clientglobal->friendlist->first->history->first->message);



printf("The length of the list is: %d\n",clientglobal->friendlist->length);
printf("The length of the list is: %d\n",clientglobal->userlist->length);
printf("The the friendlist for james and nima is: %d\n",clientglobal->friendlist->first->history->length);


/*
       printf("Friend Request:\n");
            strcpy(send,"F_N_R\n");
            strcat(send,"james10\n");
            strcat(send,"sally83\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"sally83\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Recieve request:\n");
            strcpy(send,"F_N_A\n");
            strcat(send,"sally83\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Friend Request:\n");
            strcpy(send,"F_N_R\n");
            strcat(send,"matt55\n");
            strcat(send,"melissa77\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"melissa77\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Recieve request:\n");
            strcpy(send,"F_N_A\n");
            strcat(send,"melissa77\n");
            strcat(send,"matt55\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"matt55\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);




       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHello How are you?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Logout request:\n");
            strcpy(send,"L_O\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);



       printf("Login request:\n");
            strcpy(send,"L_I\n");
            strcat(send,"james10\n");
            strcat(send,"password\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Chess request:\n");
            strcpy(send,"C_S\n");
            strcat(send,"sally83\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Chess accept:\n");
            strcpy(send,"C_A\n");
            strcat(send,"james10\n");
            strcat(send,"sally83\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"sally83\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Chess move:\n");
            strcpy(send,"C_M\n");
            strcat(send,"a3b5\n");
            strcat(send,"sally83\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"james10\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"melissa77");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"matt55");
                strcat(send,"\n");
                strcat(send,"M_S_G\nI cant live with out you!! lol\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);


       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"melissa77");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"matt55");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHello what is going on?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"sally66");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nHello dude?\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Send message:\n");
                strcpy(send,"S_N_D\n");
                strcat(send,"nima13");
                strcat(send,"\n");
                strcat(send,"R_C_V\n");
                strcat(send,"james10");
                strcat(send,"\n");
                strcat(send,"M_S_G\nYo man\n");
                Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);

       printf("Update request:\n");
            strcpy(send,"U_P_D\n");
            strcat(send,"matt55\n");
            Talk2Server(send,recieve);
       printf("Return: %s\n",recieve);
*/

DeleteClient(clientglobal); 
    return 0;
} //end of main

// EOF
