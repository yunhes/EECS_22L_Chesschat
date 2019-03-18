

#include <stdlib.h>
#include <stdio.h>
#include "UserList.h"


int main(void){
    char username[6];
    char password[6];
    char message[30];

    strcpy(message, "how are you? I am good.."); 
    strcpy(username, "uname");
    strcpy(password, "passw");

    char username2[6];
    char password2[6];
    char message2[30];

    strcpy(message2, "hey whats up?.."); 
    strcpy(username2, "uname2");
    strcpy(password2, "passw2");

    char usernamef[6];
    char usernamef2[6];

    strcpy(usernamef, "unamef1");
    strcpy(usernamef2, "unamef2");




    ULIST *list;
    list = CreateUserList();

    ACCOUNT *account;
    account = CreateAccount(username, password);
    ACCOUNT *account2;
    account2 = CreateAccount(username2, password2);
    printf("The buffer for account1 is:%s\n",account->buffer);
    printf("The size of the buffer is: %d\n",strlen(account->buffer));

    AppendAccount(list,account);
    AppendAccount(list,account2);

    FENTRY *friend, *friend2;
    friend = CreateFLISTEntry(usernamef);
    friend2 = CreateFLISTEntry(usernamef2);
    
    AppendFriend(list->first->friendlist,friend);
    AppendFriend(list->first->next->friendlist,friend2);

    MENTRY *mess, *mess2;
    mess = CreateMessageEntry(message);
    mess2 = CreateMessageEntry(message2);
 
    AppendMessage(list->first->friendlist->first->history,mess);
    AppendMessage(list->first->next->friendlist->first->history,mess2);

    printf("Account1:\n username: %s\n password %s\n",list->first->username,list->first->password);
    printf("Account2:\n username: %s\n password %s\n",list->first->next->username,list->first->next->password);
 
    printf("Account1 friend username:%s\nAccount2 friend username:%s\n",list->first->friendlist->first->username,list->first->next->friendlist->first->username);
    printf("Account1 message history:%s\nAccount2 message history:%s\n",list->first->friendlist->first->history->first->message,list->first->next->friendlist->
    first->history->first->message);

    DeleteUserList(list);

    return 0;
}




