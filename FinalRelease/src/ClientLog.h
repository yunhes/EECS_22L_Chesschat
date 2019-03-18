#ifndef ClientLog_h
#define ClientLog_h

#include <stdio.h>
#include <stdlib.h>
#include "ChatStruct.h"

// for regsiter the account
int sign_up(char *username, char *password, ULIST *list);

//for login
int Login (char *username, char *password, ULIST *list);

//for logout

void logout(CLIENT *account, char *username, ULIST *list);

int AddFriendList(CLIENT *client,char *input,int increment);

void add_history(CLIENT *client, char *input);

int AddUserList(CLIENT *client,char *input,int increment);

int AddMessageList(CLIENT *client,char *input,int increment); 

int DelFriendList(CLIENT *client,char *input,int increment);
 
void GetUsername(char *str1, char *str2);

#endif
