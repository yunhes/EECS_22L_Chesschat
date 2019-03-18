                                                                   
//ClientList.c source file for client list functions                    
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ClientList.h"


// Create a new account entry
CLIENT *CreateClient(void){
    CLIENT *client = NULL;
    client = malloc(sizeof(CLIENT));
    FLISTC *friendl;
    MSLIST *userlist;
    MSLIST *request;
    friendl = CreateClientFlist();
    userlist = CreateMessageList();
    request = CreateMessageList();
    if(!client) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    memset(client->password,' ',sizeof(client->password));
    memset(client->username,' ',sizeof(client->username));
    memset(client->buffer, ' ', sizeof(client->buffer));
    client->friendlist = friendl;
    client->userlist = userlist;
    client->friendrequest = request;
    client->status = 0;
    return client;
}



//Create a new friend list entry
FENTRYC *CreateClientFriend(char *username){
    FENTRYC *entry = NULL;
    entry = malloc(sizeof(FENTRYC));
    if(!entry){
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    entry->Chat_window = NULL;
    entry->Chat_window = NULL;
    entry->text = NULL;
    entry->buffer = NULL;
    entry->next = NULL;
    strcpy(entry->username,username);
    entry->game = NULL;   
    return entry;
}


/*
//Create a new message entry
MENTRY *CreateMessageEntry(char *message){
    MENTRY *entry;
    entry = malloc(sizeof(MENTRY));
    if(!entry){
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    strcpy(entry->message,message);
    return entry;
}





// Delete message entry
void DeleteMessageEntry(MENTRY *entry){
    assert(entry);
    free(entry);
    return;
}
*/
/*
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
}*/





void DeleteClientFriend(FENTRYC *entry){
    assert(entry);
    FENTRYC *temp;
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
void DeleteClientFriend(FENTRYC *entry){
    assert(entry);
    FENTRYC *temp;
    if(entry->history){
        DeleteMessageList(entry->history);
    }
    if(entry->list->last == entry){
        if(entry->list->first == entry){
            entry->list->length--;
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
    } else {
        temp=entry->list->first;
        while(temp->next != entry){
            temp=temp->next;
        }
        temp->next=entry->next;
    }}
    entry->list->length--;
    free(entry);
    return;    
}

*/

//Delete friend list
void DeleteClientFlist(FLISTC *list){
    assert(list);
    FENTRYC *friend1, *friend2;
    friend1 = list->first;
    while(friend1) {
        friend2 = friend1->next;
        DeleteClientFriend(friend1);
        friend1 = friend2;
    }
    free(list);
    return;
}





//Delete account and all friends and messages
void DeleteClient(CLIENT *client){
    assert(client);
    if(client->friendlist){
        DeleteClientFlist(client->friendlist);
    }
    if(client->userlist){
        DeleteMessageList(client->userlist);
    }
    free(client);
    return;
}





// Create a new friend list 
FLISTC *CreateClientFlist(void)
{
    FLISTC *list;
    list = malloc(sizeof(FLISTC));
    if(!list) {
        perror("Out of memory! Aborting...\n");
        exit(10);
    }
    list->length = 0;
    list->first = NULL; 
    list->last = NULL;  
    return list;
}

/*
// Create a new userlist 
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
*/



//Insert a friend at the end of the list
void AppendClientFriend(FLISTC *list, FENTRYC *frnd){
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


/*
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
}*/



/* EOF */
