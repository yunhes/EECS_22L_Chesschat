#Team 04 makefile for chat
#This file will make all of the object files and the executable


# Makefile: GUI example clock server with corresponding client
# Rainer Doemer, 2/22/17 (based on simple ClockServer example)

# compiler flags for GTK usage
#GTKINC	= `pkg-config --cflags gtk+-2.0`
#GTKLIBS	= `pkg-config --libs gtk+-2.0`

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

GFLAGS	= -Wall -ansi -std=c99  $(DEBUG) $(GTKINC) $(OPTS) -c
RFLAGS	= -Wall -ansi  $(DEBUG) $(GTKLIBS) $(OPTS)

CC     = gcc
DEBUG  = -DDEBUG
NDEBUG = -DNDEBUG
CFLAGS = -ansi -std=c99 -Wall -g -c
LFLAGS = -ansi -std=c99 -Wall -lm
AR     = ar rc
RANLIB = ranlib

OPTS	= -g

all:
	$(MAKE) -C src


simple.o: GUI_LC.c simple.h
	gcc -c GUI_LC.c $(GFLAGS) -o simple.o

Main.o: Main.c
	gcc -c Main.c $(GFLAGS) -o Main.o

Client: simple.o ClientLog.o Client.o ServerFunctions.o ClientList.o UserList.o Main.o
	gcc simple.o Client.o ClientLog.o  ServerFunctions.o ClientList.o UserList.o Main.o $(RFLAGS) -o Client

TestClient.o: TestClient.c
	gcc TestClient.c $(GFLAGS) -o TestClient.o

TestClient: TestClient.o  ClientList.o UserList.o Client.o ClientLog.o ServerFunctions.o
	gcc  TestClient.o ClientList.o UserList.o Client.o ClientLog.o ServerFunctions.o $(RFLAGS) -o TestClient

Server.o: Server.c
	gcc Server.c $(GFLAGS) -o Server.o

Server: Server.o ServerFunctions.o UserList.o ServerLog.o
	gcc Server.o ServerFunctions.o UserList.o ServerLog.o $(RFLAGS) $(DEBUG) -o Server

temp.o: test.c
	gcc test.c $(GFLAGS) -o temp.o

temp: test.o
	gcc test.o $(RFLAGS) -o temp


#Target to generate UserList.o
UserList.o: UserList.c UserList.h
	$(CC) $(GFLAGS) UserList.c -o UserList.o

#Target to generate ServerFunctions.o
ServerFunctions.o: ServerFunctions.c ServerFunctions.h UserList.h
	$(CC) $(GFLAGS) $(DEBUG) ServerFunctions.c -o ServerFunctions.o

#Target to generate Client.o
Client.o: Client.c Client.h
	$(CC) $(GFLAGS) $(DEBUG) Client.c -o Client.o

#Target to generate ClientLog.o
ClientLog.o: ClientLog.c ClientLog.h
	$(CC) $(GFLAGS) $(DEBUG) ClientLog.c -o ClientLog.o


#Target to generate ClientList.o
ClientList.o: ClientList.c ClientList.h
	$(CC) $(GFLAGS) ClientList.c -o ClientList.o

#Target to generate UserListTest.o
UserListTest.o: UserListTest.c
	$(CC) $(CFLAGS) UserListTest.c -o UserListTest.o

#Target to generate ServerLog.h
ServerLog.o: ServerLog.c ServerLog.h
	$(CC) $(GFLAGS) $(DEBUG) ServerLog.c -o ServerLog.o

#Target to generate ClientListTest.o
ClientListTest.o: ClientListTest.c
	$(CC) $(CFLAGS) ClientListTest.c -o ClientListTest.o

#Target to generate a test of the user list
TestList: UserList.o UserListTest.o
	$(CC) $(LFLAGS) UserList.o UserListTest.o -o TestList

#Target to generate a test of the client list
TestListC: ClientList.o ClientListTest.o UserList.o
	$(CC) $(LFLAGS) ClientList.o ClientListTest.o UserList.o -o TestListC

Tar: 
	gtar cvzf Chat_Beta_src.tar.gz bin doc src README.md Makefile Install.txt Copyright.txt


#r cvzf Chess_V1.0_src.tar.gz bin doc src README.md Makefile Install.txt Copyright.txtTarget to clean the directory
clean:
	
	rm -f cd src/*.o 
	rm -f cd src/TestList
	rm -f cd src/TestListC
	rm -f cd bin/Chat  
	rm -f cd bin/Server



