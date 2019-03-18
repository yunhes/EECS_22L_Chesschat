//ClientList.c the function headers for creating the datastructures on th client side
//
//
#ifndef CLIENTLIST_H
#define CLIENTLIST_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ChatStruct.h"


//Create a new client data struct
CLIENT *CreateClient(void);

//Create a new friend list entry
FENTRYC *CreateClientFriend(char *username);

//Create a new message entry
MENTRY *CreateMessageEntry(char *message);

// Delete message entry
void DeleteMessageEntry(MENTRY *entry);

//Delete message list
void DeleteMessageList(MSLIST *list);

//Delete friend entry for client
void DeleteClientFriend(FENTRYC *entry);

//Delete friend list for client
void DeleteClientFlist(FLISTC *list);

//Delete client and all friends and messages
void DeleteClient(CLIENT *client);

//Create the client friend list
FLISTC *CreateClientFlist(void);

/* Create a new userlist */
MSLIST *CreateMessageList(void);

//Insert a friend at the end of the list
void AppendClientFriend(FLISTC *list, FENTRYC *frnd);

//Insert a message at the end of the list
void AppendMessage(MSLIST *list, MENTRY *message);
 
//#endif

#endif

