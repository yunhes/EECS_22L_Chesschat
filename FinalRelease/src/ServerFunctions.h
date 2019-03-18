//ServerFunctions.h

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include "ChatStruct.h"



int stringCopyN(char *recieve, int position, char *message);


void UserUpdate(ULIST *userlist, char *senderUN, char *outbuffer);


int BufferMessage(ULIST *userlist, char *senderUN, char *recieverUN, char *message);


int LoginUser(ULIST *userlist, char *username, char *password, char *outbuffer);


void ProcessInStreamTemp(char *recieve, char *messageout, int length, char *username);


void ProcessInStream(char *recieve, char *send, int length, ULIST *userlist);


void AddMessageReciever(FLIST *friendlist, char *senderUN, char *recieverUN, char *message);


void AddMessageSender(ULIST *userlist, char *senderUN, char *recieverUN, char *message);


int LogOutUser(ULIST *userlist, char *username, char *outbuffer);


int RegisterUser(ULIST *userlist, char *username, char *password, char *outbuffer);


void SendFriendList(ULIST *userlist, char *recieverUN, char *send);

void FriendRequest(ULIST *userlist, char *senderUN, char *recieverUN);


void FriendAccept(ULIST *userlist, char *senderUN, char *recieverUN);

void ChessRequest(ULIST *userlist, char *senderUN, char *recieverUN,char *color);


int BufferChessMove(ULIST *userlist, char *senderUN, char *recieverUN, char *move);

void SendMessageList(ULIST *userlist, char *recieverUN, char *send);
 
void ChessAccept(ULIST *userlist, char *senderUN, char *recieverUN);

void DeleteSenderFriend(ULIST *userlist, char *senderUN, char *recieverUN);

void DeleteReceiverFriend(ULIST *userlist, char *senderUN, char *recieverUN);
 
#endif
