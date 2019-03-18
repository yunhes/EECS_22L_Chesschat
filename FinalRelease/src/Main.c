//modified by Yunhe Shao
//Deep Core Dumped


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include "UserList.h"
#include "ClientList.h"
#include "ServerFunctions.h"
#include "simple.h"





/*Global Variables */
CLIENT *clientglobal;
char ChessRequest_UN[20];
gchar FriendName[20];
gchar out_buffer[2000];

//Friend Request variable
char FR_username[500];

const char *Program = NULL;//Descriptive Diagnostics
struct sockaddr_in ServerAddress;	/* server address we connect with */

GtkWidget *view;
GtkTreeModel *model; 
GtkWidget *window ;
GtkWidget *fixed ;
GtkWidget *chess_icon ;
GtkWidget *table ;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *board_fixed;
GtkWidget *Friendlist;
GtkWidget *Register_window;
GtkWidget *Chat_window;
GtkWidget *Login_window;

//static GtkWidget *text;
//static GtkWidget *message_entry;

GtkTextBuffer *buffer;

//static GtkWidget* entry1;
//static GtkWidget* entry2;

//static GtkWidget* reg_entry1;
//static GtkWidget* reg_entry2;
//static GtkWidget* reg_entry3;


char Coord_buffer[6];
char ChessRequest_UN[20];



gchar *username[20];
gchar *password;
gchar FriendName[20];

gchar out_buffer[2000];


//gchar *message_receive;
gchar buffer_message_display[1000];
//gchar *buffer_message_display;
gint *Message_Length;

#define BUFFSIZE 2000


enum GRID Board[8][8];
enum GRID BoardLocation[3][2]; //setting a new array to store clicking location. 0,0 is selectclick.
enum {COLUMN = 0, NUM_COLS};

//testing changed main
int
main (int   argc,
      char *argv[])
{
  window = NULL;
  Login_window = NULL;
  Friendlist = NULL;
  Register_window = NULL;
  Chat_window = NULL;
  int PortNo;
  struct hostent *Server;
  FR_username[0] = '\0';

 //Creating the data structure for the client variables.
 clientglobal = CreateClient();


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

  g_print("went in gtk almost\n");
  gtk_init_check(&argc, &argv);
  g_print("went in gtk !\n");
  //window = Create_Board();
  //Register_window = Create_register_window();
  Login_window = Create_login_window();
  //Chat_window = Create_Chatbox();
  Friendlist = Create_Friendlist(clientglobal);
  //chang_background(Login_window, 480,270, "./chess_icon/BackGroud_Login.jpg");
  //chang_background(Register_window, 480,270, "./chess_icon/BackGroud_Login.jpg");

  //chang_background(Friendlist, 676,401, "./chess_icon/BackGroud_Login.jpg");

  gtk_widget_show_all(Login_window);
  //gtk_widget_show_all(Friendlist);
  gtk_main() ;
  DeleteClient(clientglobal);

  return 0 ;
}









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






char *Talk2Server(		// communicate with the server
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
}


//EOF
