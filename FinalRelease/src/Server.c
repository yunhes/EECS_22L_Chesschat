/* GTK_ClockServer.c: GUI example TCP/IP server with timeout support
 * Author: Rainer Doemer, 2/23/17 (based on simple ClockServer.c)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <math.h>
#include "UserList.h"
#include "ServerFunctions.h"
#include <poll.h>
#include "ServerLog.h"
/* #define DEBUG */	/* be verbose */
#define BUFFSIZE 256
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/*** type definitions ****************************************************/

typedef void (*ClientHandler)(int DataSocketFD, ULIST *userlist);
typedef void (*TimeoutHandler)(void);
struct pollfd mypoll = {STDIN_FILENO,POLLIN|POLLPRI};
/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;
int Shutdown		/* keep running until Shutdown == 1 */
	= 0;
char servercontrol[5];

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

int MakeServerSocket(		/* create a socket on this server */
	uint16_t PortNo)
{
    int ServSocketFD;
    struct sockaddr_in ServSocketName;

    /* create the socket */
    ServSocketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (ServSocketFD < 0)
    {   FatalError("service socket creation failed");
    }
    /* bind the socket to this server */
    ServSocketName.sin_family = AF_INET;
    ServSocketName.sin_port = htons(PortNo);
    ServSocketName.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ServSocketFD, (struct sockaddr*)&ServSocketName,
		sizeof(ServSocketName)) < 0)
    {   FatalError("binding the server to a socket failed");
    }
    /* start listening to this socket */
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError("listening on socket failed");
    }
    return ServSocketFD;
} /* end of MakeServerSocket */

void ProcessRequest(		/* process a time request by a client */
	int DataSocketFD, ULIST *userlist)
{
    int  l, n;
    char RecvBuf[5000];	/* message buffer for receiving a message */
    char SendBuf[5000];	/* message buffer for sending a response */

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0) 
    {   FatalError("reading from data socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received message: %s\n", Program, RecvBuf);
#endif
 
    ProcessInStream(RecvBuf,SendBuf,n,userlist);
    l = strlen(SendBuf);
    printf(" in the server l is %d\n",l);
#ifdef DEBUG
    printf("%s: Sending response: %s.\n", Program, SendBuf);
#endif
    n = write(DataSocketFD, SendBuf, l);
    printf("The size of the data send is: %d\n",n);
    memset(SendBuf,' ',sizeof(SendBuf));
    if (n < 0)
    {   FatalError("writing to data socket failed");
    }
} /* end of ProcessRequest */

void ServerMainLoop(		/* simple server main loop */
	int ServSocketFD,		/* server socket to wait on */
	ClientHandler HandleClient,	/* client handler to call */
        ULIST *userlist,
	int Timeout)			/* timeout in micro seconds */
{
    int DataSocketFD;	/* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
	ClientAddress;	/* client address we connect with */
    fd_set ActiveFDs;	/* socket file descriptors to select from */
    fd_set ReadFDs;	/* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res, i;

    FD_ZERO(&ActiveFDs);		/* set of active sockets */
    FD_SET(ServSocketFD, &ActiveFDs);	/* server socket is active */
    while(!Shutdown)
    {
        if(poll(&mypoll,1,1)){
            scanf("%s4",servercontrol);
            if(0 == strcmp(servercontrol,"exit")){
                Shutdown = 1;
            }
        } else {
            
        }
	ReadFDs = ActiveFDs;
	TimeVal.tv_sec  = Timeout / 1000000;
	TimeVal.tv_usec = Timeout % 1000000;
	/* bloc until input arrives on active sockets or until timeout */
	res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
	if (res < 0)
	{   FatalError("wait for input or timeout (select) failed");
	}
	if (res == 0)	/* timeout occurred */
	{
#ifdef DEBUG
     //      printf("Timeout occurred..\n");
#endif
	}
	else		/* some FDs have data ready to read */
	{   for(i=0; i<FD_SETSIZE; i++)
	    {   if (FD_ISSET(i, &ReadFDs))
		{   if (i == ServSocketFD)
		    {	/* connection request on server socket */
#ifdef DEBUG
			printf("%s: Accepting new client...\n", Program);
#endif
			ClientLen = sizeof(ClientAddress);
			DataSocketFD = accept(ServSocketFD,
				(struct sockaddr*)&ClientAddress, &ClientLen);
			if (DataSocketFD < 0)
			{   FatalError("data socket creation (accept) failed");
			}
#ifdef DEBUG
			printf("%s: New client connected from %s:%hu.\n",
				Program,
				inet_ntoa(ClientAddress.sin_addr),
				ntohs(ClientAddress.sin_port));
#endif
			FD_SET(DataSocketFD, &ActiveFDs);
		    }
		    else
		    {   /* active communication with a client */
#ifdef DEBUG
			printf("%s: Dealing with client on FD%d...\n",
				Program, i);
#endif
			HandleClient(i,userlist);
#ifdef DEBUG
			printf("%s: Closing client connection FD%d.\n",
				Program, i);
#endif
			close(i);
			FD_CLR(i, &ActiveFDs);
		    }
		}
	    }
	}
    }
} /* end of ServerMainLoop */

/*** main function *******************************************************/

int main(			/* the main function */
	int argc,
	char *argv[])
{
    int ServSocketFD;	/* socket file descriptor for service */
    int PortNo;		/* port number */

    ULIST *userlist;
   
    userlist = CreateUserList();
    loadLog(userlist);
 /*
    ACCOUNT *account1, *account2, *account3;
    account1 = CreateAccount("james10","password");
    account2 = CreateAccount("nima13","password");
    account3 = CreateAccount("sally66","password");


    FENTRY *friend1, *friend2, *friend3, *friend4;

    friend1 = CreateFLISTEntry("nima13");
    friend2 = CreateFLISTEntry("sally66");
    friend3 = CreateFLISTEntry("james10");
    friend4 = CreateFLISTEntry("james10");
 
//    strcpy(account2->buffer,"This was in nima13 buffer");
    AppendAccount(userlist,account1);
    AppendAccount(userlist,account2);
    AppendAccount(userlist,account3);


    AppendFriend(userlist->first->friendlist,friend1);
    AppendFriend(userlist->first->friendlist,friend2);
    AppendFriend(userlist->first->next->friendlist,friend3);
    AppendFriend(userlist->first->next->next->friendlist,friend4);
*/

    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", Program);
#endif
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", Program);
	exit(10);
    }
    PortNo = atoi(argv[1]);	/* get the port number */
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating the server socket...\n", Program);
#endif
    ServSocketFD = MakeServerSocket(PortNo);

#ifdef DEBUG
    printf("%s: Server is initialized %d...\n", Program, PortNo);
#endif
    ServerMainLoop(ServSocketFD,ProcessRequest,userlist,250000);
#ifdef DEBUG
    printf("\n%s: Shutting down.\n", Program);
#endif
    close(ServSocketFD);
    saveLog(userlist);
    DeleteUserList(userlist);
    return 0;
} /* end of main */

//EOF
