//
//  GameStuct.h
//  GameBoard
//
//  Created by Matthew Dunn on 1/20/2019
//  Copyright © 2019 DeepCoreDumped. All rights reserved.
//


//This file contains the data structures for the chess game



#ifndef CHESSSTRUCT_H
#define CHESSSTRUCT_H



typedef struct TreeNode TNODE;
typedef struct MovesList MLIST;
typedef struct ListNode LNODE;
typedef struct GameBoard GBOARD;
typedef struct Game GAME;



//Node in the tree
struct TreeNode{ 
    MLIST *list;
    GBOARD *board;
    TNODE *back;
    int depth;	
};

	
//Struct for the head of the list
struct MovesList{
    TNODE *parent;
    LNODE *first;
    LNODE *last;
    int length;
};

//Node in the double linked list
struct ListNode{
    MLIST *head;
    LNODE *next;
    LNODE *prev;
    TNODE *tnode;
};

//Struct for the game board
struct GameBoard{
    char colum;
    char pcolum;
    int row;
    int prow;
    int playerflag;
    int aimove;
    char piece[64];
    int castling[6];
};

//Struct for game
struct Game{
    TNODE *log;
    GBOARD *currentBoard;
    int gameType; //This is for the type of game easy, medium or difficult.
    int difficultyLevel;
    int win;
};


#endif	
//EOF    	
	
