//
//  ChatStruct.h
//  GameBoard
//
//  Created by Matthew Dunn on 1/20/2019
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//


//This file contains the data structures for the chess game



#ifndef CHATSTRUCT_H
#define CHATSTRUCT_H
#include "ChessStruct.h"

#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>




typedef struct UserList ULIST;
typedef struct FriendList FLIST;
typedef struct MessageList MSLIST;
typedef struct FriendListClient FLISTC;
typedef struct Account ACCOUNT;
typedef struct FriendEntry FENTRY;
typedef struct FriendEntryClient FENTRYC;  // this is the friend struct for the client side. It contains an additional game struct.
typedef struct MessageEntry MENTRY;
typedef struct ClientInfo CLIENT;

#define MESSAGE 500
#define PASSLENGTH 16
#define USERLENGTH 16
#define BUFFER 1500
	
//Struct for the head of the list
struct UserList{
    ACCOUNT *first;
    ACCOUNT *last;
    int length;
};


//Struct for the friend list
struct FriendList{
    FENTRY *first;
    FENTRY *last;
    int length;
};

//Struct for the friend list client side
struct FriendListClient{
    FENTRYC *first;
    FENTRYC *last;
    int length;
};



//Struct for the message history list
struct MessageList{
    MENTRY *first;
    MENTRY *last;
    int length;
};


//Struct for user account 
struct Account{
    ULIST *list;
    ACCOUNT *next;
    char username[USERLENGTH];
    char password[PASSLENGTH];
    char buffer[BUFFER];
    FLIST *friendlist;
    int status;   //0 for offline, 1 for online, 2 for inactive
};



//Struct for client side main account 
struct ClientInfo{
    char username[PASSLENGTH];
    char password[USERLENGTH];
    char buffer[BUFFER];
    FLISTC *friendlist;
    MSLIST *userlist;
    MSLIST *friendrequest;
    int status;   //0 for offline, 1 for online, 2 for inactive
};





//Struct for the friend list entry
struct FriendEntry{
    FLIST *list;
    FENTRY *next;
    char username[USERLENGTH];
    MSLIST *history;
};


//Struct for the friend list entry on client side
struct FriendEntryClient{
    FLISTC *list;
    FENTRYC *next;
    char username[USERLENGTH];
    GtkWidget *Chat_window;
    GtkWidget *text;
    GtkWidget *message_entry;
    GtkTextBuffer *buffer;
    MSLIST *history;
    GAME *game;  //chess game struct for playing chess.
    int status;
};




//Struct for the message history list entry
struct MessageEntry{
    MSLIST *list;
    MENTRY *next;
    char message[MESSAGE];
};





#endif	
//EOF    	
	
