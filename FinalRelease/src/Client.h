//
//  Client.h
//  Client
//
//  Created by Richard Duong on 2/28/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//

#ifndef Client_h
#define Client_h
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ChatStruct.h"
#include "ChessStruct.h"
#include "ClientLog.h"
#include "ClientList.h"
#include "UserList.h"
#include "simple.h"
//#include "playersmove.h"

//extern gchar FriendName[20];
extern CLIENT *clientglobal;
extern char ChessRequest_UN[20];
extern char FriendName[20];
extern gchar username[20];

#define BUFF 5000
#define SIZE 5000
#define USERSIZE 18
#define PROTO 10
#define HISTORYLENGTH 10
 
//Parses the input from the server
int Parsing(char *input,int length);

//Fuction to prepare a message to send
void SendFReq(char *friend);

//Function to delete friend
void Deletefriend(char *friend);

//Function to prep a text message to friend
void SendMes(char *friend, char *message);

//Function if recieve text message
void RecieveMes(CLIENT *client1,char *message,char *friend);

void AppendMes(MSLIST *list,const gchar *message,char *username); 
 
//Send a request to play chess to a friend
void ReqChess(char *friend);

void  ChessReq(char *friend, char *temp);
 
//Sends a Chessmove
void SChessmove(char *friend, char *pmove, char *move);

//Recieves chess move and updates the board
void RChessMove(char *friend, char *pmove, char *move);

//Recieved friend request, ask for confirmation, then adds friend
void RecFReq(CLIENT *client, char *username);

//Put the message history in the window.
void message_into_window(MSLIST *listi,GtkTextBuffer *tempbuffer);
 
//Check for periodic updates
char *update();

//Function for copying a str
void strcpyn(char *str1, char *str2);
 
void Writetoserver(char *message);

char *Readfromserver(char *buffer);

#endif /* Client.h */

