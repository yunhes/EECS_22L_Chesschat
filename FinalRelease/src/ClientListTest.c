

#include <stdlib.h>
#include <stdio.h>
#include "ClientList.h"
#include "UserList.h"

int main(void){
    char username[6];
    char clientusername[6];
    char message[30];

    strcpy(message, "how are you? I am good.."); 
    strcpy(username, "uname");
    strcpy(clientusername, "client");

    char username2[6];
    char message2[30];

    strcpy(message2, "hey whats up?.."); 
    strcpy(username2, "uname2");


    CLIENT *list;
    list = CreateClient();
    strcpy(list->username,clientusername);

    FENTRYC *account, *account2;
    account = CreateClientFriend(username);
    account2 = CreateClientFriend(username2);

    AppendClientFriend(list->friendlist,account);
    AppendClientFriend(list->friendlist,account2);


    MENTRY *mess, *mess2;
    mess = CreateMessageEntry(message);
    mess2 = CreateMessageEntry(message2);
 
    AppendMessage(list->friendlist->first->history,mess);
    AppendMessage(list->friendlist->first->next->history,mess2);


    printf("Client Username:  %s\n",list->username);
    printf("Friend1 Username: %s\n Friend2 Username: %s\n",list->friendlist->first->username,list->friendlist->first->next->username);
    printf("Friend1 message: %s\n Friend2 message: %s\n",list->friendlist->first->history->first->message,list->friendlist->first->next->history->first->message);

    DeleteClient(list);

    return 0;
}




