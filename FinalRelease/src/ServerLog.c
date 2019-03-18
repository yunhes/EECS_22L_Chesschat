// Ameya Pandit
// ID: 74877526
// EECS22L Team04

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "UserList.h"
#include "ServerLog.h"

// the main that I created here was just for me to test the functionality of saveLog and loadLog.
/*
int main()	{
	ULIST *test = CreateUserList();
	ACCOUNT *account1 = CreateAccount("mattd", "lawls");
	ACCOUNT *account2 = CreateAccount("ameyap", "hi");
	ACCOUNT *account3 = CreateAccount("coding", "imbad");
	AppendAccount(test, account1);
	AppendAccount(test, account2);
	AppendAccount(test, account3);

	account1->friendlist = CreateFriendList();
	strcpy(account1->buffer, "SUCCESS\nR_C_V\njsmes\npasswllll\nM_S_Gkjkjkjkjkj\n"); 
	FENTRY *firstFriend = CreateFLISTEntry("pandy");
	FENTRY *secondFriend = CreateFLISTEntry("matt");
	AppendFriend(account1->friendlist, firstFriend);
	AppendFriend(account1->friendlist, secondFriend);

	account2->friendlist = CreateFriendList();
	strcpy(account2->buffer, "want want want want want");
	FENTRY *thirdFriend = CreateFLISTEntry("yuming");
	FENTRY *fourthFriend = CreateFLISTEntry("shao");
	AppendFriend(account2->friendlist, thirdFriend);
	AppendFriend(account2->friendlist, fourthFriend);
	
	account3->friendlist = CreateFriendList();
	strcpy(account3->buffer, " go go go out of this world");
	FENTRY *fifthFriend = CreateFLISTEntry("richard");
	FENTRY *sixthFriend = CreateFLISTEntry("mike");
	AppendFriend(account3->friendlist, fifthFriend);
	AppendFriend(account3->friendlist, sixthFriend);

	firstFriend->history = CreateMessageList();
	MENTRY *messageOne = CreateMessageEntry("yo whats up man! 1");
	AppendMessage(firstFriend->history, messageOne);
	MENTRY *messageTwo = CreateMessageEntry("I hope everything is alright! 2");	
	AppendMessage(firstFriend->history, messageTwo);

	secondFriend->history = CreateMessageList();
	MENTRY *messageThree = CreateMessageEntry("I miss you man! 3");
	AppendMessage(secondFriend->history, messageThree);
	MENTRY *messageFour = CreateMessageEntry("memes? memes. 4");
	AppendMessage(secondFriend->history, messageFour);

	thirdFriend->history = CreateMessageList();
	MENTRY *messageFive = CreateMessageEntry("lawls! everything is good. 5");
	AppendMessage(thirdFriend->history, messageFive);
	MENTRY *messageSix = CreateMessageEntry("miss you my guy! 6");
	AppendMessage(thirdFriend->history, messageSix);

	fourthFriend->history = CreateMessageList();
	MENTRY *messageSeven = CreateMessageEntry("is love binary? 7");
	AppendMessage(fourthFriend->history, messageSeven);
	MENTRY *messageEight = CreateMessageEntry("can you obtain love? 8");
	AppendMessage(fourthFriend->history, messageEight);

	fifthFriend->history = CreateMessageList();
	MENTRY *messageNine = CreateMessageEntry("love is allowing someone to destroy you... 9");
	AppendMessage(fifthFriend->history, messageNine);
	MENTRY *messageTen = CreateMessageEntry("and trusting them to not do so. 10");
	AppendMessage(fifthFriend->history, messageTen);

	sixthFriend->history = CreateMessageList();
	MENTRY *messageEleven = CreateMessageEntry("you will find it once more. 11");
	AppendMessage(sixthFriend->history, messageEleven);
	MENTRY *messageTwelve = CreateMessageEntry("keep going! 12");
	AppendMessage(sixthFriend->history, messageTwelve);
	
	saveLog(test);
	loadLog(test);
	//saveLog(test);
}*/

void saveLog(ULIST *list)	{	// saveLog function. This function iterates through the data structure and notes the account, the account's friends,
					// and the messages between the friends into a text file.
			
	FILE *fp;	//file management
	fp = fopen("AccountCredentials.txt", "w");

	ACCOUNT *accountOne, *accountTwo;	// account iterators
	accountOne = list->first;

	while(accountOne != NULL)	{	// while there are accounts in the data structure
		accountTwo = accountOne->next;		
	
		fprintf(fp, "U_S_N: %s\n", accountOne->username);	// print username
		fprintf(fp, "P_W_D: %s\n", accountOne->password);	// print password
				
		conversionSpace(accountOne->buffer);			// converts space character in buffer to ~
		conversionNewline(accountOne->buffer);			// converts newline character in buffer to `
	
		fprintf(fp, "B_F_R: %s\n", accountOne->buffer);		// print buffer
	
		FENTRY *friendOne, *friendTwo;				// friend iterators
		friendOne = accountOne->friendlist->first;

		while(friendOne != NULL)	{	// while there are friends (while account has friends)
			friendTwo = friendOne->next;
		
			fprintf(fp, "F_N_D: %s\n", friendOne->username);

			MENTRY *msgOne, *msgTwo;	// message iterators
			msgOne = friendOne->history->first;

			while (msgOne != NULL)	{	// while there are messages (while account has friends who have messages)
				msgTwo = msgOne->next;

				conversionSpace(msgOne->message);	// converts space character in message to ~
				conversionNewline(msgOne->message);	// converts newline character in message to ~
				
				fprintf(fp, "M_S_G: %s\n", msgOne->message);	// print message

				msgOne = msgTwo;
			}			
		
			friendOne = friendTwo;
		}	
		fprintf(fp, "///////////////////////////////////////////////////\n");
		accountOne = accountTwo;	
	}
	fclose(fp);
}

void loadLog(ULIST *list)	{	// loadLog function. This reads the text file created by saveLog and creates the data structure as set-up before server shutdown
	FILE *fp;	// file management
   	 if(access("AccountCredentials.txt",F_OK) != -1){
		fp = fopen("AccountCredentials.txt", "r");

	char dummy[28];	// dummy variable created for storing username


	ACCOUNT *newAccount;	//account global object
	FENTRY *newFriend;	//friend global object
	MENTRY *newMessage;	//message global object
				//I use these to create and update the data structure
	
	if (fp)	{
		char string[1000];	// helps iterate through the file line by line
		
		while (fgets(string, 1000, fp) != NULL)	{
			if (strstr(string, "U_S_N: ") != NULL)	{	//if the string contains username
				char *username;
				username = strchr(string, ' ');	//username variable stores the username from file
				spaceRemove(username);	//remove any spaces in the username
				strcpy(dummy, username);	//dummy variable holds username for later use
			}
			if (strstr(string, "P_W_D: ") != NULL)	{	//if string contains password
				char *password;	
				password = strchr(string, ' ');	//password variable stores the password from file
				spaceRemove(password);	//remove any spaces in the password
				newAccount = CreateAccount(dummy, password);	//create an account with username (stored in dummy) and password
				AppendAccount(list, newAccount);	//append the account onto the userlist
			}
			if (strstr(string, "B_F_R: ") != NULL)	{	//if string contains buffer
				char *buffer;
				buffer = strchr(string, ' ');	//buffer variable stores the buffer from file
				spaceRemove(buffer);	//remove spaces in the buffer (in the beginning and end of string)
				conversionSpaceBack(buffer);	//convert the ~ characters in the buffer back to the space character
				conversionNewlineBack(buffer);	//convert the ` characters in the buffer back to newline character
				strcpy(newAccount->buffer, buffer);	//assign the buffer to the account created before
			}
			if (strstr(string, "F_N_D: ") != NULL)	{	//if string contains friend
				char *friend;			
				friend = strchr(string, ' ');	//friend variable stores the friend from the file
				spaceRemove(friend);	//remove spaces from friend
				newFriend = CreateFLISTEntry(friend);	//creating friend to be added to the list of friends
				AppendFriend(newAccount->friendlist, newFriend);	//adding friend to list of friends
			}
			if (strstr(string, "M_S_G: ") != NULL)	{	//if string contains message
				char *message;				
				message = strchr(string, ' ');	//message variables stores the message from the file
				spaceRemove(message);	//remove the extra spaces in the message
				conversionSpaceBack(message);	//convert the ~ characters back to space characters
				conversionNewlineBack(message);	//convert the ` characters back to newline characters
				newMessage = CreateMessageEntry(message);	//creating message to be added to list of messages
				AppendMessage(newFriend->history, newMessage);		//adding message to the list of messages	
			}
		}		
	}
	fclose(fp);
        printf("Database loaded\n");
    } else {
        printf("Database file will be generated on exit\n");
    }
    return;
}

void conversionSpace(char *string)	{	//just converts the space characters in the passed string to ~ 
						//done so that there are no issues sending messages (issues with space characters)
	for (int i = 0; i < (int)strlen(string); i++)	{
		if (string[i] == ' ')	{
			string[i] = '~';
		}
	}
}

void conversionSpaceBack(char *string)	{	//converting the ~ characters back to ' '
	for (int i = 0; i < (int)strlen(string); i++)	{
		if (string[i] == '~')	{
			string[i] = ' ';
		}
	}
}

void conversionNewline(char *string)	{	//converts the newline characters in the passed string to `
						//done so that there are no issues sending messages (issues with newline characters)
	for (int i = 0; i < (int)strlen(string); i++)	{
		if (string[i] == '\n')	{
			string[i] = '`';
		}
	}
}

void conversionNewlineBack(char *string)	{	//converts the ` characters back to \n
	for (int i = 0; i < (int)strlen(string); i++)	{
		if (string[i] == '`')	{
			string[i] = '\n';
		}
	}
}

void spaceRemove(char *removeString)	{		//removes the extraneous space characters in the beginning and end of the string
	int count = 0;
	for (int i = 0; removeString[i]; i++)	{
		if (removeString[i] != ' ')	{
			removeString[count++] = removeString[i];
		}		
	}	
	removeString[count] = '\0';
	int length = (int)strlen(removeString);
	removeString[length-1] = '\0';
}
