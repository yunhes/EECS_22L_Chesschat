

#ifndef TEST_CLIENT_H 
#define TEST_CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>

/* #define DEBUG */	/* be verbose */
//#define BUFFSIZE 256

/*** global variables ****************************************************/

//void FatalError(const char *ErrorMsg);	


char *Talk2Server(		/* communicate with the server */
	const char *Message,
	char *RecvBuf);	


#endif	
