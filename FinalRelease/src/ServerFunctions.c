//ServerFunctions.c


#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ServerFunctions.h"
#include "UserList.h"

#define BUFFERSIZE 2000
#define MESSAGESIZE 500
#define HISTORYSIZE 499
//function to copy from the input stream, this function copies up to a \n char and then returns the lenth of the string that was copied



int stringCopyN(char *recieve, int position, char *message){
    int length = 0;

    while((recieve[length + position] != '\n')){
        message[length] = recieve[length + position];
        length++;
    }
    message[length] = '\0';
    return (length + 1);
}





//Adds the message to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
void AddMessageSender(ULIST *userlist, char *senderUN, char *recieverUN, char *message){
    assert(userlist);
    MENTRY *mentry;
    char temp[HISTORYSIZE];

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,senderUN)){
            //calling function with the usernames reversed to ensure taht message goes in the sender history also.
            FENTRY *friend1, *friend2;
            friend1 = account1->friendlist->first;
            while(friend1) {
                friend2 = friend1->next;
                if(0 == strcmp(friend1->username,recieverUN)){
                    strncpy(temp,senderUN,(strlen(senderUN)));
                    strcat(temp,": ");
                    strncat(temp,message,(strlen(message)));
                    mentry = CreateMessageEntry(temp);
                    AppendMessage(friend1->history,mentry);
                return;
                }
                friend1 = friend2;
            }

        }
        account1 = account2;
    }
    return;
}






//Function to send the list of all users to the client.
void SendUserList(ULIST *userlist, char *username, char *outbuffer){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    if(account1){
        if(outbuffer[0] == '\0'){
            strcpy(outbuffer,"F_U_L\n");
        } else {
            strcat(outbuffer,"F_U_L\n");
        }
    }
    while(account1){
        account2 = account1->next;
        strcat(outbuffer,"U_");
        strcat(outbuffer,account1->username);
        if(account1->status == 1){
            strcat(outbuffer,"_ONLINE\n");
        }
        if(account1->status == 0){
            strcat(outbuffer,"_OFFLINE\n");
        }
        account1 = account2;
    }
    strcat(outbuffer,"E_N_D\n");
    return;
}







//Sends the friendlist of a user to to establish on the client side
void SendFriendList(ULIST *userlist, char *recieverUN, char *send){
    assert(userlist);
    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            if(account1->friendlist->first){
            FENTRY *entry1 = NULL;
            FENTRY *entry2 = NULL;
            entry1 = account1->friendlist->first;
            if(send[0] == '\0'){
                strcpy(send,"C_F_L\n");
            } else {
                strcat(send,"C_F_L\n");
            }
            while(entry1){
                entry2 = entry1->next;
                strncat(send,entry1->username,(strlen(entry1->username)));
                ACCOUNT *temp, *temp1;
                temp = userlist->first;
                while(temp){
                    temp1 = temp->next;
                    if(0 == strcmp(temp->username,entry1->username)){
                       if(temp->status == 1){
                           strcat(send,"_ONLINE\n");
                       }
                       if(temp->status == 0)
                           strcat(send,"_OFFLINE\n");
                       }
                    temp = temp1;
                }
                entry1 = entry2;
            }
            strcat(send,"E_N_D\n");
            return;
        } else {
             if(send[0] == '\0'){
                 strcpy(send,"C_F_L\nE_N_D\n");
             } else {
                 strcat(send,"C_F_L\nE_N_D\n");
             }
        }
        }
        account1 = account2;
    }
    return;
}





//Sends the friendlist of a user to to establish on the client side
void SendMessageList(ULIST *userlist, char *recieverUN, char *send){
    assert(userlist);
    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            FENTRY *entry1 = NULL;
            FENTRY *entry2 = NULL;
            entry1 = account1->friendlist->first;
            if(entry1){
            if(send[0] == '\0'){
                strcpy(send,"M_H\n");
                } else {
                    strcat(send,"M_H\n");
                }
            } 
            while(entry1){
                entry2 = entry1->next;
                MENTRY *temp, *temp1;
                temp = entry1->history->first;
                strcat(send,"U_N\n");
                strcat(send,entry1->username);
                strcat(send,"\n");
                int count = 0;
                while(temp){
                    temp1 = temp->next;
                    if((entry1->history->length - count) < 10){
                        strcat(send,temp->message);
                        strcat(send,"\n");
                    }
                    count++;
                    temp = temp1;
                }
                entry1 = entry2;
            }
            strcat(send,"E_N_D\n");
            return;
        }
        account1 = account2;
    }
    return;
}



/*

//send 10 message from the history side to the client, ask for the friend name and load 10 message as their history
//the output message could be:M_H\nUsername\nS_N_D\nUsername\nM_S_G\nHistory\nS_N_D\nUsername2\nM_S_G\nHistory2\n
void SendHistory(ULIST *userlist, char *username, char *sendM){
	assert(userlist);
	ACCOUNT *account1, *account2;
        account1 = userlist->first;
	
	while(account1){
		account2 = account1 -> next;
		 if(0 == strcmp(account1->username,username)){
			FENTRY *entry1 = NULL;
                        FENTRY *entry2 = NULL;
                        entry1 = account1->friendlist->first;
                        if(entry1){
                            if(send[0] == '\0'){
                                strcpy(send,"C_F_L\n");
                            } else {
                                strcat(send,"C_F_L\n");
                            }
 
                            strcpy(
			while (entry1){
				 entry2 = entry1 ->next;
                                 strcat(sendM,"U_N\n");
                                 
				 int count = 0;
				 MENTRY *message1, *message2;
                                 message1 = entry1->history->first;
                                 while(message1){
                                     message2 = message1->next;
				     if((count - entry1->history->length) < 10){
					 strcat(sendM,entry1->history->first->message);
                                     }
                                     count++;
			             message1 = message2;
				 }
                                 entry1 = entry2;
                       }


				 if (count 
			
				 strcat(sendM, "E_N_D\n");
				 while(1){ //in this we figure the 10 messages. 
					count = stringCopyN(sendM,count, temp);
					 if(0 == strcmp(temp, "S_N_D")){
						 strcpy(buffer, temp);
						 strcat(buffer,"\n");
						 count = stringCopyN(send, count, temp);//username
						 strcat(buffer, temp);
						 strcat(buffer, "\n");
						 count = stringCopyN(send, count, temp);//M_S_G
						 strcat(buffer, temp);
						 strcat(buffer, "\n");
						 count = stringCopyN(send, count, temp);//history1
						 strcat(buffer, temp);
						 strcat(buffer, "\n");
						length ++;
					 }
					 if (length == 9){
						 strcat(buffer,"E_N_D\n");
						 strcpy(send, buffer);
						 break;
					 }
					 if(0 == strcmp(temp1, "E_N_D")){
						 strcat(buffer,"E_N_D\n");
						 strcpy(send, buffer);
						 break;
					 }
				 }
				 entry1 = entry2;
			}
			strcat(sendM, "E_N_D_D\n");//to make the whole string end.
			return;
		 }
	}
	return;
}

*/


void AddMessageReciever(FLIST *friendlist, char *senderUN, char *recieverUN, char *message){
    assert(friendlist);
    MENTRY *mentry;
    char temp[HISTORYSIZE];

    FENTRY *friend1, *friend2;
    friend1 = friendlist->first;
    while(friend1) {
        friend2 = friend1->next;
        if(0 == strcmp(friend1->username,senderUN)){
            strcpy(temp,"From ");
            strncat(temp,senderUN,(strlen(senderUN)));
            strcat(temp,": ");
            strncat(temp,message,(strlen(message)));
            mentry = CreateMessageEntry(temp);
            AppendMessage(friend1->history,mentry);
            return;
        }
        friend1 = friend2;
    }
    return;
}





//Adds the message to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
int BufferMessage(ULIST *userlist, char *senderUN, char *recieverUN, char *message){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            //adding the message to the message log for both clients involved
            AddMessageSender(userlist,senderUN,recieverUN,message);
            AddMessageReciever(account1->friendlist,senderUN,recieverUN,message);
            if(account1->status == 1){
            if(account1->buffer[0] == '\0'){
                strcpy(account1->buffer,"S_N_D\n");
            } else {
                strcat(account1->buffer,"S_N_D\n");
            }
            strncat(account1->buffer,senderUN,(strlen(senderUN)));
            strcat(account1->buffer,"\nM_S_G\n");
            strncat(account1->buffer,message,(strlen(message)));
            strcat(account1->buffer,"\n");
            }
            return 0;
        }
        account1 = account2;
    }
    return 1;
}


 
//Adds the message to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
void DeleteRecieverFriend(ULIST *userlist, char *senderUN, char *recieverUN){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            FENTRY *entry1, *entry2;
            entry1 = account1->friendlist->first;
            while(entry1){
                entry2 = entry1->next;
                if(0 == strcmp(entry1->username,senderUN)){
printf("The entry is deleted on the Receiver\n");
                    DeleteFriendEntry(entry1);
                    return;
                }
                entry1 = entry2;
            }
        }
        account1 = account2;
    }
    return;
}




//Adds the message to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
void DeleteSenderFriend(ULIST *userlist, char *senderUN, char *recieverUN){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,senderUN)){
            FENTRY *entry1, *entry2;
            entry1 = account1->friendlist->first;
            while(entry1){
                entry2 = entry1->next;
                if(0 == strcmp(entry1->username,recieverUN)){
 printf("THe entry is deleted on the sender\n");
                    DeleteFriendEntry(entry1);
                    return;
                }
                entry1 = entry2;
            }
        }
        account1 = account2;
    }
    return;
}






//Adds the chessmove to the buffer for a certain client. Returns a 0 if successful, returns 1 if failure;
int BufferChessMove(ULIST *userlist, char *senderUN, char *recieverUN, char *move){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            if(account1->buffer[0] == '\0'){
                strcpy(account1->buffer,"C_M\n");
            } else {
                strcat(account1->buffer,"C_M\n");
            }
            strncat(account1->buffer,move,(strlen(move)));
            strcat(account1->buffer,"\n");
            strncat(account1->buffer,senderUN,(strlen(senderUN)));
            strcat(account1->buffer,"\n");
            return 0;
        }
        account1 = account2;
    }
    return 1;
}



//Adds the chess request to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
void ChessRequest(ULIST *userlist, char *senderUN, char *recieverUN, char *color){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            //adding the message to the message log for both clients involved
            if(account1->buffer[0] == '\0'){
                strcpy(account1->buffer,"C_S\n");
            } else {
                strcat(account1->buffer,"C_S\n");
            }
            strncat(account1->buffer,senderUN,(strlen(senderUN)));
            strcat(account1->buffer,"\n");
            if(0 == strcmp(color,"w")){
            strcat(account1->buffer,"b");
            } else {
                strcat(account1->buffer,"w");
            } 
            strcat(account1->buffer,"\n");         
            return;
        }
        account1 = account2;
    }
    return;
}






//Adds the chess request to the buffer for a certain client. Returns 0 if successful, returns 1 if failure.
void ChessAccept(ULIST *userlist, char *senderUN, char *recieverUN){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            //adding the message to the message log for both clients involved
            if(account1->buffer[0] == '\0'){
                strcpy(account1->buffer,"C_A\n");
            } else {
                strcat(account1->buffer,"C_A\n");
            }
            strncat(account1->buffer,senderUN,(strlen(senderUN)));
            strcat(account1->buffer,"\n");
            return;
        }
        account1 = account2;
    }
    return;
}





//Adds the friend request to the buffer for a certain client.
void FriendRequest(ULIST *userlist, char *senderUN, char *recieverUN){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            //adding the message to the message log for both clients involved
            if(account1->buffer[0] == '\0'){
                strcpy(account1->buffer,"F_N_R\n");
            } else {
                strcat(account1->buffer,"F_N_R\n");
            }
            strncat(account1->buffer,senderUN,(strlen(senderUN)));
            strcat(account1->buffer,"\n");
            return;
        }
        account1 = account2;
    }
    return;
}







//Adds the friend request to the buffer for a certain client.
void FriendAccept(ULIST *userlist, char *senderUN, char *recieverUN){
    assert(userlist);
    ACCOUNT *account1, *account2;
    account1 = userlist->first;

    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,senderUN)){
            FENTRY* entry;
            entry = CreateFLISTEntry(recieverUN);
            AppendFriend(account1->friendlist,entry);
            break;
        }
        account1 = account2;
    }
    account1 = userlist->first;

    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,recieverUN)){
            FENTRY* entry;
            entry = CreateFLISTEntry(senderUN);
            AppendFriend(account1->friendlist,entry);
            return;
        }
        account1 = account2;
    }
    return;
}







//Logs in the user and sends the initialization for friends, users, and messages.
int LoginUser(ULIST *userlist, char *username, char *password, char *outbuffer){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if((0 == strcmp(account1->username,username)) && (0 == strcmp(account1->password,password))){
            account1->status = 1;  //user is logged in
            if(account1->buffer[0] == '\0'){
                strcpy(outbuffer,"SUCCESS\n");
            } else {
                strcat(outbuffer,"SUCCESS\n");
            }
                SendFriendList(userlist,username,outbuffer);
                SendUserList(userlist,username,outbuffer);
                SendMessageList(userlist,username,outbuffer);  
                strcat(outbuffer,account1->buffer);
                memset(account1->buffer,' ',sizeof(account1->buffer));
                account1->buffer[0] = '\0';
                return 0;
            }
        account1 = account2;
    }
    strcpy(outbuffer,"FAIL\n");
    return 1;
}





//Logs in the user
int LogOutUser(ULIST *userlist, char *username, char *outbuffer){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,username)){
            account1->status = 0;  //user is logged in
            strcpy(outbuffer,"SUCCESS\n");
            return 0;
        }
        account1 = account2;
    }
    strcpy(outbuffer,"FAIL\n");
    return 1;
}







//Logs in the user
int RegisterUser(ULIST *userlist, char *username, char *password, char *outbuffer){
    assert(userlist);
    ACCOUNT *account;

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if((0 == strcmp(account1->username,username)) && (0 == strcmp(account1->password,password))){
            strcpy(outbuffer,"FAIL\n");
            return 1;
        }
        account1 = account2;
    }
    account = CreateAccount(username,password);
    AppendAccount(userlist,account);
    strcpy(outbuffer,"SUCCESS\n");
    return 0;
}







//Sets the outgoing buffer for recieveing
void UserUpdate(ULIST *userlist, char *senderUN, char *outbuffer){
    assert(userlist);

    ACCOUNT *account1, *account2;
    account1 = userlist->first;
    while(account1) {
        account2 = account1->next;
        if(0 == strcmp(account1->username,senderUN)){
            if(account1->buffer[0] != '\0'){
                strcpy(outbuffer,account1->buffer);
                memset(account1->buffer,' ',sizeof(account1->buffer));
                account1->buffer[0] = '\0';
                break;
            } else {
                strcpy(outbuffer,"SUCCESS\n");
                break;
            }
        }
        account1 = account2;
    }
    return;
}





//Processes the incoming stream of data finds keywords and calls appropriate functions to handle the messages.
void ProcessInStream(char *recieve, char *send, int length, ULIST *userlist){
    char senderUN[18];
    char recieverUN[18];
    char password[18];
    char buffer[BUFFERSIZE];
    char message[MESSAGESIZE];
    char chessmove[6];
    int flag = 0;
    char color[3];
 
    int i = 0;
    int l = 0;

    memset(send,' ',sizeof(send));
    send[0] = '\0';

    while(i < length){
        l = stringCopyN(recieve,i,buffer);
        i = (i + l);
        if(0 == strcmp(buffer, "S_N_D")) {//username of the person sending a message
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
#ifdef DEBUG
            printf("Client username recieved: %s\n",senderUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "R_C_V")){//username of the person recieving a message
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
#ifdef DEBUG
           printf("Reciever username recieved: %s\n",recieverUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "L_I")){//login a user
            flag = 0;
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,password);
            i = (i + l);
            flag = LoginUser(userlist,senderUN,password,send);
#ifdef DEBUG
            printf("Client login recieved, username: %s password: %s\n",senderUN,password);
            printf("The return flag is: %d\n",flag);
            printf("The send buffer after login: %s\n the size of the buffer is %zd\n",send,strlen(send));
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "L_O")){//log out a user
            flag = 0;
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            flag = LogOutUser(userlist,senderUN,send);
#ifdef DEBUG
            printf("Client logout recieved, username: %s\n",senderUN);
            printf("The return flag is: %d\n",flag);
            printf("The send buffer after logout: %s\n the size of the buffer is %zd\n",send,strlen(send));
#endif
            continue;
        } else {

        if(0 == strcmp(buffer, "M_S_G")){//send a message
            l = stringCopyN(recieve,i,message);
            i = (i + l);
            flag = BufferMessage(userlist,senderUN,recieverUN,message);
            UserUpdate(userlist,senderUN,send);
#ifdef DEBUG
            printf("Clients message recieved: %s\n",message);
            printf("The return flag is: %d\n",flag);
#endif
            continue;
        } else {
       if(0 == strcmp(buffer, "U_P_D")){//update the user
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            UserUpdate(userlist,senderUN,send);
            SendFriendList(userlist,senderUN,send);
            SendUserList(userlist,senderUN,send);
            //do we want to send the userlist here also?
#ifdef DEBUG
            printf("Client recieve username: %s\n",senderUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "R_E_G")){//register an account
            flag = 0;
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,password);
            i = (i + l);
            flag = RegisterUser(userlist,senderUN,password,send);
            SendUserList(userlist,senderUN,send);
#ifdef DEBUG
            printf("Client registration recieved, username: %s password: %s\n",senderUN,password);
            printf("The return flag is: %d\n",flag);
            printf("The send buffer after registration: %s\n the size of the buffer is %zd\n",send,strlen(send));
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "F_N_R")){//friend request
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
            FriendRequest(userlist,senderUN,recieverUN);
#ifdef DEBUG
            printf("Client FR recieved, Sender username: %s Reciever username: %s\n",senderUN,recieverUN);
#endif
            continue;
        } else {
         if(0 == strcmp(buffer, "F_N_A")){//accept a friend request
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
            FriendAccept(userlist,senderUN,recieverUN);
            SendFriendList(userlist,senderUN,send);
#ifdef DEBUG
            printf("Client FA recieved, Sender username: %s Reciever username: %s\n",senderUN,recieverUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "C_S")){//request for  a chess game
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
            l = stringCopyN(recieve,i,color);
            i = (i + l);  
            ChessRequest(userlist,senderUN,recieverUN,color);
#ifdef DEBUG
            printf("Client FR recieved, Sender username: %s Reciever username: %s\n",senderUN,recieverUN);
#endif
            continue;
        } else {
         if(0 == strcmp(buffer, "C_M")){//move for a chess game
            l = stringCopyN(recieve,i,chessmove);
            i = (i + l);
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l); 
            BufferChessMove(userlist,senderUN,recieverUN,chessmove);
#ifdef DEBUG
            printf("Client FR recieved, Sender username: %s Reciever username: %s\n",senderUN,recieverUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "C_A")){//request for  a chess game
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
            ChessAccept(userlist,senderUN,recieverUN);
#ifdef DEBUG
            printf("Client FR recieved, Sender username: %s Reciever username: %s\n",senderUN,recieverUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "D_F_N")){//register an account
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            l = stringCopyN(recieve,i,recieverUN);
            i = (i + l);
            DeleteRecieverFriend(userlist,senderUN,recieverUN);
            DeleteSenderFriend(userlist,senderUN,recieverUN);
            SendFriendList(userlist,senderUN,send);
#ifdef DEBUG
            printf("Client registration recieved, username: %s password: %s\n",senderUN,password);
            printf("The return flag is: %d\n",flag);
            printf("The send buffer after registration: %s\n the size of the buffer is %zd\n",send,strlen(send));
#endif
            continue;
        } else {
            printf("Unknown Flag\n");
        }}}}}}}}}}}}}
    }
    if(send[0] == '\0'){
        UserUpdate(userlist,senderUN,send);
    }
}




void ProcessInStreamTemp(char *recieve, char *messageout, int length, char *username){
    char senderUN[10];
    char buffer[1000];
    char message[1000];
    
    int i = 0;
    int l = 0;

    while(i < length){
        l = stringCopyN(recieve,i,buffer);
        i = (i + l);
        if(0 == strcmp(buffer, "S_N_D")) {
            l = stringCopyN(recieve,i,senderUN);
            i = (i + l);
            strcpy(username,senderUN);
#ifdef DEBUG
           // printf("Client username recieved: %s\n",senderUN);
#endif
            continue;
        } else {
        if(0 == strcmp(buffer, "M_S_G")){
            l = stringCopyN(recieve,i,message);
            i = (i + l);
            strcpy(messageout,message);
            printf("          Message Recieved\n");
            printf("From: %s Message: %s\n",senderUN,message);

#ifdef DEBUG
          //  printf("Clients message recieved: %s\n",message);
#endif
       continue;
       } else {
       if(0 == strcmp(buffer, "SUCCESS\n")){
       } else {
       if(0 == strcmp(buffer, "FAIL\n")){
           printf("Login failed\n");
       }}}}
    }
    return;
}





//EOF
