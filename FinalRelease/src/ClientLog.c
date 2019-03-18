#include "ClientLog.h"
#include "ClientList.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ServerFunctions.h"
/*

//for the register function ex:R_E_G\njame123\npassword\n, return 0 for success, 1 for faild
int sign_up(char *username, char *password, ULIST *list){
    assert(list);
    CLIENT *client;
    char send[256];
    char receive[256];
    char temp[256];
    char *signup;
    int a = 0;
    while (a ==0){
        strcpy(send,"R_E_G");
        strcat(send,"\n");
        strcat(send,username);
        strcat(send,"\n");
        strcat(send,password);
        strcat(send,"\n");
        Talk2Server(send, receive);
        strcpy(temp, receive);
        if (0 == strcmp(temp,"SUCCESS")){
            printf("SUCCESS");
            client = CreateClient();
            strcpy(client->username,username);
            strcpy(client->password,password);
            FENTRYC *friendlistE;
            friendlistE = CreateClientFriend(username);
            MENTRY *mE;
            mE = CreateMessageEntry(signup);
            a = 1;
            return 0;
        }
        if (a ==1){
            printf("SIGN UP SUCCESS\n");
            break;
        }
        else{
        printf("FAIL");
        return 1;
        }
    }
}

//for login EX: L_I\njame123\npassword\n, if its success, retuurn 0, not return 1
int Login (char *username, char *password, ULIST *list){
    assert(list);
    char send[256];
    char receive[256];
    char temp[256];
    char *temp2;
    CLIENT *account;
    int count = 0;
    
    strcpy(send,"L_I");
    strcat(send,"\n");
    strcat(send,username);
    strcat(send,"\n");
    strcat(send,password);
    strcat(send,"\n");
    Talk2Server(send, receive);
    count = stringCopyN(receive,count,temp);
    if (0 == strcmp(temp,"SUCCESS")){
            while(1){
            count = stringCopyN(receive, count, temp);
            if (0 == strcmp(temp, "C_F_L")){//C_F_L\nusername\nusername\n
                while(0 != strcmp(temp,"M_H")){
                    count = stringCopyN(receive, count, temp);
                    strcat(temp, "\n");
                    strcat(temp2, temp);
                }
                AddFriendList(account, temp2, 0);
            }
            if (0 == strcmp(temp, "S_N_D")){
                while (0 != strcmp(temp, "E_N_D_D")){
                    strcpy(temp2, "S_N_D\n");
                    count = stringCopyN(receive, count, temp);
                    strcat(temp, "\n");
                    strcat(temp2, temp);
                }
                add_history(account, temp2);
            }
            printf("LOGIN SUCCESS\n");
            return 0;
            }
    }
    else{
        printf("LOGIN FAILD");
        return 1;
    }

}

//for logout EX: L_O\njame123\npassword\n
void logout(CLIENT *account, char *username, ULIST *list){
    assert(list);
    char send[256];
    char receive[256];
    char temp[256];
    strcpy(send,"L_O");
    strcat(send,"\n");
    strcat(send,username);
    strcat(send,"\n");
    Talk2Server(send, receive);
    stringCopyN(receive,0,temp);
    if (0 == strcmp(temp,"SUCCESS")){
        DeleteClient(account);
        printf("LOGOUT success\n");
    }
}

//this is to put the input message into the friends list history
//S_N_D\nUsername\nM_S_G\nHistory1\nS_N_D\nUsername\nM_S_G\nHistory1\nS_N_D\nE_N_D;
void add_history(CLIENT *client,char *input){
    assert(client);
    char *name;
    char *temp;
    char *Fhistory;
    int count;
    
    FENTRYC *friend;
    FENTRYC *friend2;
    friend = client ->friendlist ->first;
    friend2 = friend ->next;
    while (friend){
        count = stringCopyN(input, count, temp);
            while(0 == strcmp(temp, "S_N_D")){
                strcpy(Fhistory, temp);
                strcat(Fhistory, "\n");
                while (1){
                    if (0 == strcmp(temp, "E_N_D")){
                        strcat(Fhistory, "E_N_D\n");
                        strcpy(friend ->history ->first ->message, Fhistory);
                        break;
                    }
                    count = stringCopyN(input, count, temp);
                    strcat(Fhistory,temp);
                    strcat(Fhistory, "\n");
                }
                if (0 != strcmp(temp, "S_N_D")){
                    friend = friend2;
                    break;
                }
            }
    }
}*/


//get just username
//1 for out, 2 for origional
void GetUsername(char *str1, char *str2){
    int i = 0;
    while((str2[i]!='_') && (str2[i] != '\0') && (str2[i] != '\n')){
        str1[i]=str2[i];
        i++;
    }
    str1[i]='\0';
    return;
}//End of strcpyn


//This function is to add the friend list to the CLIENT struct. 
//The struct is checked to ensure that the friend does not exist and then added
int AddMessageList(CLIENT *client,char *input,int increment){
    char temp[250];
    char username[20];
    temp[0] = '\0';
    int i = increment;
    int l = 0;
    FENTRYC *entry1 = NULL;
    FENTRYC *entry2 = NULL;
 
    l = stringCopyN(input,i,temp);
    i = (i + l);
    while(0 != strcmp(temp,"E_N_D")){
        if(0 == strcmp(temp,"U_N")){
            l = stringCopyN(input,i,username);
            i = (i + l);
        }
        char actualuser[20];
        entry1 = client->friendlist->first;
        while(entry1){
            entry2 = entry1->next;
            GetUsername(actualuser,entry1->username);
            if(0 == strcmp(username,actualuser)){
                l = stringCopyN(input,i,temp);
                i = (i + l);
                while((0 != strcmp(temp,"U_N")) && (0 != strcmp(temp,"E_N_D"))){ 
                    //strcat(temp,"\n");
                    MENTRY *message = CreateMessageEntry(temp);
                    AppendMessage(entry1->history,message);              
                    l = stringCopyN(input,i,temp);
                    i = (i + l);
                }
                    break;         
            }
            entry1 = entry2;
        }
    }
    return i;
}

 







//This function is to add the friend list to the CLIENT struct. 
//The struct is checked to ensure that the friend does not exist and then added
int AddFriendList(CLIENT *client,char *input,int increment){
    char temp[16];
    char actualuser[16];
    temp[0] = '\0';
    int i = increment;
    int l = 0;
    int occurrence = 0;
    FENTRYC *friend;

    l = stringCopyN(input,i,temp);
    i = (i + l);
    GetUsername(actualuser,temp);
//printf("username in add friend: %s\n",actualuser);
    while(0 != strcmp(temp,"E_N_D")){
//printf("Friends: %s\n",temp);
        FENTRYC *temp2, *temp3;
        char actualuser2[16];

        temp2 = client->friendlist->first;
        while(temp2){
            temp3 = temp2->next;
            GetUsername(actualuser2,temp2->username);
// printf("username of the list: %s\n",actualuser2);
            if(0 == strcmp(actualuser,actualuser2)){
                strcpy(temp2->username,temp);
                occurrence = 1;
                break;
            }
            temp2 = temp3;
        }
//printf("Occurrence %d\n",occurrence);
        if(occurrence == 0){
            friend = CreateClientFriend(temp);
            AppendClientFriend(client->friendlist,friend);
        }
        l = stringCopyN(input,i,temp);
        i = (i + l);
        GetUsername(actualuser,temp);
        occurrence = 0;
    }
//printf("End\n");
    return i;
}



//This function is to delete the friend list to the CLIENT struct. 
//The struct is checked to ensure that the friend does exist and then delete
int DelFriendList(CLIENT *client,char *input,int increment){
    char temp[16];
    char actualuser[16];
    temp[0] = '\0';
    int i = increment;
    int l = 0;
    int reset = i;
    int occurrence = 0;
    FENTRYC *temp2, *temp3;
    char actualuser2[16];

    temp2 = client->friendlist->first;
//printf("username in add friend: %s\n",actualuser);
    while(temp2){
//printf("Friends: %s\n",temp);
        l = stringCopyN(input,i,temp);
        i = (i + l);
        if((0 == strcmp(temp,"E_N_D") && (occurrence == 0))){
            DeleteClientFlist(client->friendlist);
            client->friendlist = CreateClientFlist();
            return i;
        }
        GetUsername(actualuser, temp2->username);
        temp3 = temp2->next;
        while(0 != strcmp(temp,"E_N_D")){
            GetUsername(actualuser2,temp);
// printf("username of the list: %s\n",actualuser2);
            if(0 == strcmp(actualuser,actualuser2)){
                occurrence = 1;
                break;
            }
            l = stringCopyN(input,i,temp);
            i = (i + l);
        }
        if(occurrence == 0){
            DeleteClientFriend(temp2);
        }
        temp2=temp3;
        i=reset;
        occurrence = 0;
    }
    return i;
}


//This function is to add the user list to the CLIENT struct. 
//The struct is checked to ensure that the friend does not exist and then added
int AddUserList(CLIENT *client,char *input,int increment){
    char temp[16];
    char actualuser[16];
    temp[0] = '\0';
    int i = increment;
    int l = 0;
    int occurrence = 0;
    MENTRY *user;

    l = stringCopyN(input,i,temp);
    i = (i + l);
    GetUsername(actualuser,(temp + 2));
//printf("username in add user: %s\n",actualuser);
    while(0 != strcmp(temp,"E_N_D")){
//printf("Friends: %s\n",temp);
        MENTRY *temp2, *temp3;
        char actualuser2[16];

        temp2 = client->userlist->first;
        while(temp2){
            temp3 = temp2->next;
            GetUsername(actualuser2,(temp2->message + 2));
// printf("username of the list: %s\n",actualuser2);
            if(0 == strcmp(actualuser,actualuser2)){
                strcpy(temp2->message,temp);
                occurrence = 1;
                break;
            }
            temp2 = temp3;
        }
        if(occurrence == 0){
            user = CreateMessageEntry(temp);
            AppendMessage(client->userlist,user);
        }
        l = stringCopyN(input,i,temp);
        i = (i + l);
        GetUsername(actualuser,(temp + 2));
        occurrence = 0;
    }
    return i;
}



//EOF

