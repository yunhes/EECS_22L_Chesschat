
#ifndef USERLIST_H
#define USERLIST_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ChatStruct.h"

//Create a new account entry
ACCOUNT *CreateAccount(char *username, char *password);

//Create a new friend list entry
FENTRY *CreateFLISTEntry(char *username);

//Create a new message entry
MENTRY *CreateMessageEntry(char *message);

// Delete message entry
void DeleteMessageEntry(MENTRY *entry);

//Deletes only the first message in the list.
void DeleteFirstMessage(MSLIST *list); 

//Delete message list
void DeleteMessageList(MSLIST *list);

//Delete friend entry
void DeleteFriendEntry(FENTRY *entry);

//Delete friend list
void DeleteFriendList(FLIST *list);

//Delete account
void DeleteAccount(ACCOUNT *account);

//Delete user list
void DeleteUserList(ULIST *list);

/* Create a new userlist */
ULIST *CreateUserList(void);

/* Create a new friend list */
FLIST *CreateFriendList(void);

/* Create a new userlist */
MSLIST *CreateMessageList(void);

//Insert a account at the end of the list
void AppendAccount(ULIST *list, ACCOUNT *account);

//Insert a friend at the end of the list
void AppendFriend(FLIST *list, FENTRY *frnd);

//Insert a message at the end of the list
void AppendMessage(MSLIST *list, MENTRY *message);
 
#endif
