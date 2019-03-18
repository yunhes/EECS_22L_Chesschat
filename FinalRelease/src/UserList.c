                                                                   
//UserList.c source file for user list functions                    

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "UserList.h"
#include "ClientList.h"

/* Create a new account entry */
ACCOUNT *CreateAccount(char *username, char *password)
{
    ACCOUNT *account = NULL;
    account = malloc(sizeof(ACCOUNT));
    if(!account) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    account->list = NULL;
    account->next = NULL; 
    strcpy(account->username,username);
    strcpy(account->password,password);
    memset(account->buffer, ' ', sizeof(account->buffer));
    account->buffer[0] = '\0';
    account->friendlist = NULL;
    account->status = 0;
    return account;
}





//Create a new friend list entry
FENTRY *CreateFLISTEntry(char *username){
    FENTRY *entry = NULL;
    entry = malloc(sizeof(FENTRY));
    if(!entry){
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    entry->next = NULL;
    strcpy(entry->username,username);
    return entry;
}



//Create a new message entry
MENTRY *CreateMessageEntry(char *message){
    MENTRY *entry;
    entry = malloc(sizeof(MENTRY));
    if(!entry){
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    strcpy(entry->message,message);
    entry->next = NULL;
    return entry;
}

/*
// Delete message entry
void DeleteMessageEntry(MENTRY *entry){
    assert(entry);
    free(entry);
    return;
}

*/

void DeleteMessageEntry(MENTRY *entry){
    assert(entry);
    MENTRY *temp;
    if(entry->list->last == entry){
        if(entry->list->first == entry){
            entry->list->length--;
            entry->list->first = NULL;
            entry->list->last = NULL;
            free(entry);
            return;
        }
        temp=entry->list->first;
        while(temp->next != entry){
            temp=temp->next;
        }
        temp->next=NULL;
        temp->list->last=temp;
    } else {
    if(entry->list->first == entry){
        entry->list->first = entry->next;
        entry->list->length--;
        free(entry);
        return;
    } else {
        temp=entry->list->first;
        while(temp->next != entry){
            temp=temp->next;
        }
        temp->next=entry->next;
        temp->list->length--;
        free(entry);
    }}
    return;    
}







//Delete the first entry
void DeleteFirstMessage(MSLIST *list){
    MENTRY *entry;
    entry = list->first;
    DeleteMessageEntry(entry);
    return;
}




//Delete message list
void DeleteMessageList(MSLIST *list){
    assert(list);
    MENTRY *msg1, *msg2;
    msg1 = list->first;
    while(msg1) {
        msg2 = msg1->next;
        DeleteMessageEntry(msg1);
        msg1 = msg2;
    }
    free(list);
    return;
}

void DeleteFriendEntry(FENTRY *entry){
    assert(entry);
    FENTRY *temp;
    if(entry->history){
        DeleteMessageList(entry->history);
    }
    if(entry->list->last == entry){
        if(entry->list->first == entry){
            entry->list->length--;
            entry->list->first = NULL;
            entry->list->last = NULL;
            free(entry);
            return;
        }
        temp=entry->list->first;
        while(temp->next != entry){
            temp=temp->next;
        }
        temp->next=NULL;
        temp->list->last=temp;
    } else {
    if(entry->list->first == entry){
        entry->list->first = entry->next;
        entry->list->length--;
        free(entry);
        return;
    } else {
        temp=entry->list->first;
        while(temp->next != entry){
            temp=temp->next;
        }
        temp->next=entry->next;
        temp->list->length--;
        free(entry);
    }}
    return;    
}


/*
//Delete friend entry
void DeleteFriendEntry(FENTRY *entry){
    assert(entry);
    if(entry->history){
        DeleteMessageList(entry->history);
    }
    free(entry);
    return;    
}
*/


//Delete friend list
void DeleteFriendList(FLIST *list){
    assert(list);
    FENTRY *friend1, *friend2;
    friend1 = list->first;
    while(friend1) {
        friend2 = friend1->next;
        DeleteFriendEntry(friend1);
        friend1 = friend2;
    }
    free(list);
    return;
}





//Delete account
void DeleteAccount(ACCOUNT *account){
    assert(account);
    if(account->friendlist){
        DeleteFriendList(account->friendlist);
    }
    free(account);
    return;
}




//Delete user list
void DeleteUserList(ULIST *list){
    assert(list);
    ACCOUNT *account1, *account2;
    account1 = list->first;
    while(account1) {
        account2 = account1->next;
        DeleteAccount(account1);
        account1 = account2;
    }
    free(list);
    return;
}






/* Create a new userlist */
ULIST *CreateUserList(void)
{
    ULIST *list;
    list = malloc(sizeof(ULIST));
    if(!list) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    list->length = 0;
    list->first = NULL;
    list->last = NULL;   
    return list;
}




/* Create a new friend list */
FLIST *CreateFriendList(void)
{
    FLIST *list;
    list = malloc(sizeof(FLIST));
    if(!list) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    list->length = 0;
    list->first = NULL; 
    list->last =  NULL;  
    return list;
}


/* Create a new userlist */
MSLIST *CreateMessageList(void)
{
    MSLIST *list;
    list = malloc(sizeof(MSLIST));
    if(!list) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    list->length = 0;
    list->first = NULL;  
    list->last = NULL; 
    return list;
}




//Insert a account at the end of the list
void AppendAccount(ULIST *list, ACCOUNT *account){
    assert(list);
    assert(account);
    FLIST *friendlist;
    friendlist = CreateFriendList();
    if(list->last) {
        account->list = list;
        account->next = NULL;
        list->last->next = account;
        list->last = account;
        account->friendlist = friendlist;
    } else {
        account->list = list;
        list->first = account;
        list->last = account;
        account->next = NULL;
        account->friendlist = friendlist;
    }
    list->length++;
    return;
}




//Insert a friend at the end of the list
void AppendFriend(FLIST *list, FENTRY *frnd){
    assert(list);
    assert(frnd);
    MSLIST *history;
    history = CreateMessageList();
    if(list->last) {
        frnd->list = list;
        frnd->next = NULL;
        list->last->next = frnd;
        list->last = frnd;
        frnd->history = history;
    } else {
        frnd->list = list;
        list->first = frnd;
        list->last = frnd;
        frnd->next = NULL;
        frnd->history = history;
    }
    list->length++;
    return;
}



//Insert a message at the end of the list
void AppendMessage(MSLIST *list, MENTRY *message){
    assert(list);
    assert(message);
    if(list->last) {
        message->list = list;
        message->next = NULL;
        list->last->next = message;
        list->last = message;
    } else {
        message->list = list;
        list->first = message;
        list->last = message;
        message->next = NULL;
    }
    list->length++;
    return;
}



/* EOF */
