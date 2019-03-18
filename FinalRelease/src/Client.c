//
//  Client.c
//  Client
//
//  Created by Richard Duong on 2/28/19.
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//
#include "Client.h"

//Parses the input from the server
int Parsing(char *input,int length){
    char friend[USERSIZE];
    char protocol[PROTO];
    char buffer[SIZE];
    char temp[SIZE];
    char pmove[4];
    char move[4];
    int i=0;
    int flag = 0;
    do{
        //Protocols the server will send
        strcpyn(protocol,input + i);
        i=i+strlen(protocol)+1;
        //Incoming sender
        if(0 == strcmp(protocol,"S_N_D")){
            strcpyn(friend,input + i);
            i=i+strlen(friend)+1;
        }
        //Incoming message
        else if(0 == strcmp(protocol,"M_S_G")){
            strcpyn(buffer,input + i);
            i=i+strlen(buffer)+1;
            RecieveMes(clientglobal,buffer,friend);
            strcpy(temp,"From ");
            strcat(temp,friend);
            strcat(temp,":");
            strcat(temp,buffer);
            strcat(temp,"\n");
            on_receive(friend,temp);
        }
        //Check for success on login/update/logout
        else if(0 == strcmp(protocol,"SUCCESS")){
            flag = 0;
        }
        //Check for failure on login/update/logout
        else if(0 == strcmp(protocol,"FAIL")){
            flag = 1;
        }
        //Incoming Friend request
        else if(0 == strcmp(protocol,"F_N_R")){
            strcpyn(friend,input + i);
            i=i+strlen(friend)+1;
            RecFReq(clientglobal,friend);
printf("Length of request list: %d\n",clientglobal->friendrequest->length);
        }
        //Incoming Friend's list
        else if(0 == strcmp(protocol,"C_F_L")){
            DelFriendList(clientglobal,input,i);
            i = AddFriendList(clientglobal,input,i);
//    printf("This is in client the length of friendlist is:%d\n",clientglobal->friendlist->length);
        }
        else if(0 == strcmp(protocol,"F_U_L")){
            i = AddUserList(clientglobal,input,i);
//printf("This is in client the length of the userlist is:%d\n",clientglobal->userlist->length);
        }
        else if(0 == strcmp(protocol,"M_H")){
            i = AddMessageList(clientglobal,input,i);
        }
        //Chess game request
        else if(0 == strcmp(protocol,"C_S")){
            strcpyn(friend,input + i);
            i=i+strlen(friend)+1;
            ChessReq(friend,temp);
        }
        else if(0 == strcmp(protocol,"C_A")){
            strcpyn(friend,input + i);
            i=i+strlen(friend)+1;
            ChessReq(friend,temp);
        } 
        //Incoming chess move
        else if(0 == strcmp(protocol,"C_M")){
            strcpyn(friend,input + i);
            i=i+strlen(friend)+1;
            strcpyn(pmove,input + i);
            i=i+strlen(pmove)+1;
            strcpyn(move,input + i);
            i=i+strlen(move)+1;
         //   RChessMove(friend, pmove, move);
        }
        //Message history
        else if(strcmp(protocol,"M_H_S")){

        }
    }while(i < length);

    return flag;
}// End of Parsing








/*
//SENDING FUNCTIONS
//Fuction to prepare a message to send
void SendFReq(char *friend){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    strcpyn(buffer,"F_N_R");
    i=i+strlen("F_N_R");
    buffer[i]="\n";
    i++;

    strcat(buffer,username);
    i=i+strlen(username);
    buffer[i]="\n";
    i++;

    strcat(buffer,friend);
    i=i+strlen(friend);
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);
}//End of SendFReq

//Fuction to delete a friend
void Deletefriend(char *friend){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    //change the protocol to delete a friend
    strcpyn(buffer,"F_N_D");
    i=i+strlen("F_N_D");
    buffer[i]="\n";
    i++;

    strcat(buffer,username);
    i=i+strlen(username);
    buffer[i]="\n";
    i++;

    strcat(buffer,friend);
    i=i+strlen(friend);
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);
}//End of Deletefriend

//Function to prep a text message to friend
void SendMes(char *friend, char *message){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    strcpyn(buffer,"S_N_D");
    i=i+strlen("S_N_D");
    buffer[i]="\n";
    i++;

    strcat(buffer,username);
    i=i+strlen(username);
    buffer[i]="\n";
    i++;

    strcat(buffer,"R_C_V");
    i=i+strlen("R_C_V");
    buffer[i]="\n";
    i++;

    strcat(buffer,friend);
    i=i+strlen(friend);
    buffer[i]="\n";
    i++;

    strcat(buffer,"M_S_G");
    i=i+strlen("M_S_G");
    buffer[i]="\n";
    i++;

    strcat(buffer, message);
    i=i+strlen(message);
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);

}//End of SendMessage

//Send a request to play chess to a friend
void ReqChess(char *friend){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    strcpyn(buffer,"C_S");
    i=i+strlen("C_S");
    buffer[i]="\n";
    i++;

    strcat(buffer,username);
    i=i+strlen(username);
    buffer[i]="\n";
    i++;

    strcat(buffer,friend);
    i=i+strlen(friend);
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);

}//End of ReqChess

//Sends a Chessmove
void SChessmove(char *friend, char* pmove, char *move){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    strcpyn(buffer,"C_M");
    i=i+strlen("C_M");
    buffer[i]="\n";
    i++;

    strcat(buffer,username);
    i=i+strlen(username);
    buffer[i]="\n";
    i++;

    strcat(buffer,friend);
    i=i+strlen(friend);
    buffer[i]="\n";
    i++;

    strcat(buffer,pmove);
    i=i+strlen(piece1);
    buffer[i]="\n";
    i++;

    strcat(buffer,move);
    i=i+strlen(move1);
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);
}//End of SChessmove
*/




//RECEIVING FUNCTIONS
//Function if recieve text message
void RecieveMes(CLIENT *client1,char *message,char *friend){
    assert(client1);
    char tempmessage[499];
    char temp[18];
    FENTRYC *entry, *entry1;
    MENTRY *messageentry;

    entry = client1->friendlist->first;
    while(entry){
        entry1 = entry->next;
        GetUsername(temp,entry->username);
        if(0 == strcmp(temp,friend)){
            if(entry->history->length == HISTORYLENGTH){
                DeleteFirstMessage(entry->history);
            }
            strcpy(tempmessage,"From ");
            strcat(tempmessage,friend);
            strcat(tempmessage,": ");
            strcat(tempmessage,message); 
            messageentry = CreateMessageEntry(tempmessage); 
            AppendMessage(entry->history,messageentry);
            return;
        }
        entry = entry1;
    }
    return; 
}//End of RecieveMes







//Function to append the outgoing message to the message history
void AppendMes(MSLIST *list,const gchar *message,char *username){
    assert(list);
    char tempmessage[200];
    MENTRY *messageentry;

            if(list->length == HISTORYLENGTH){
                DeleteFirstMessage(list);
            }
            strcpy(tempmessage,username);
            strcat(tempmessage,": ");
            strcat(tempmessage,message);
            messageentry = CreateMessageEntry(tempmessage);        
            AppendMessage(list,messageentry);
    return; 
}//End of RecieveMes







//Receives chess request
void  ChessReq(char *friend, char *temp){
    strcpy(temp,"**Chess Request** From ");
    strcat(temp,friend);
    strcat(temp,":");
    strcat(temp,"Press ""accept"" to play");
    strcat(temp,"\n");
    strcpy(ChessRequest_UN,friend);
    RecieveMes(clientglobal,temp,friend); 
    if(0 == strcmp(FriendName,friend)){
        on_receive(FriendName,temp);
    }
    return;    
}//End of ChessReq
/*
//Receives chess move and updates the board
void RChessMove(char *friend, char *pmove, char *move){
    FENTRYC *temp;
    temp=Account->friendlist->first;
    while(0!=strcmp(temp->username,friend)){
        temp=temp->next;
    }
    otherplayerssmove(temp->game, pmove, move);
}//End of RChessMove
*/



//Recieved friend request, ask for confirmation, then adds friend
void RecFReq(CLIENT *client, char *username){
    char temp[25];
    assert(client);
    MENTRY *request;
    strcpy(temp,"F_R:");
    strcat(temp,username);
    request = CreateMessageEntry(temp);
    AppendMessage(client->friendrequest,request);
    return;
}//End of RecFReq



/*
//Check for periodic updates
char *update(){
    char buffer[SIZE];
    char username[USERSIZE];
    int i=0;

    username=Account->username;

    strcpyn(buffer,"U_P_D");
    i=i+strlen("U_P_D");
    buffer[i]="\n";
    i++;

    buffer[i]="\0";
    i++;

    Writetoserver(buffer);
    return Readfromserver(buffer);
}//End of Update

*/

//CLIENT LIBRARY
//Function to copy a string
void strcpyn(char *str1, char *str2){
    int i = 0;
    while(str2[i]!='\n' && str2[i]!='\0'){
        str1[i]=str2[i];
        i++;
    }
    str1[i]='\0';
    return;
}//End of strcpyn
/*
//Function to writetoserver
void Writetoserver(char *message){
    int n;
    int SocketFD;

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFD < 0){
        FattalError("socket creation failed");
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
}//End of Writetoserver

//Function to read from server and return buffer
char *Readfromserver(char *buffer){
    int n;
    int SocketFD;

    SocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (SocketFD < 0){
        FattalError("socket creation failed");
    }
#ifdef DEBUG
    printf("%s: Waiting for response...\n", Program);
#endif
    n = read(SocketFD, buffer, BUFF-1);
    if (n < 0)
    {   FatalError("reading from socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received response: %s\n", Program, buffer);
    printf("%s: Closing the connection...\n", Program);
#endif
    close(SocketFD);
    return(buffer);
}//End of Readtoserver
*/
/* EOF Client.c */
