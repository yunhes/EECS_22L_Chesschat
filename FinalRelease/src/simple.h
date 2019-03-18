/***********************************************************
*
*A simple GTK example
*simple.h: show a 2x2 board and move the king by clicking
*author: Weiwei Chen
*initial version: 01/22/13 EECS22L Winter 2013
*
***********************************************************/


#ifndef _SIMPLE_H
#define _SIMPLE_H

#include "ChatStruct.h"

#define MAX_MSGLEN  100
#define SQUARE_SIZE 50
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 8*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 8*BOARD_BORDER)

extern CLIENT *client;

enum GRID
{
	BLACK = 0,
	WHITE = 1,
	WKing,
	BKing,
	WPawn,
	BPawn,
	BRook,
	BBishop,
	BKnight,
	WBishop,
	WRook,
	WKnight,
	WQueen,
	BQueen
};

void InitBoard();

void checkColor(int i, int j);

void ReverseGridColor(int g_x, int g_y);

void callback(GtkWidget *widget,gpointer data);

void DrawBoard();

void GUIMove(int s_x, int s_y, int g_x, int g_y);

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y);

void SelectCoordToGrid(int c_x, int c_y, int *s_x, int *s_y);

void chang_background(GtkWidget *widget, int w, int h, const gchar *path);

//static gboolean
//on_delete_event (GtkWidget *widget,
 //        GdkEvent  *event,
   //      gpointer   data);

void destroy(GtkWidget *widget,gpointer data);

void hide (GtkWidget *widget);

void select_click(GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data);

gint area_click (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data);

GtkWidget *Create_Board();

void show_board_window(GtkWidget *widget);

void show_register_window(GtkWidget *widget);

void Login_on_button_clicked (GtkWidget* button,gpointer data);

void on_delete_friend(GtkButton *button,GtkWidget *data);

GtkWidget *Create_accept_window(gchar *UN);

GtkWidget *Create_login_window();

GtkWidget *Create_register_window();

GtkWidget *Friend_list();

void on_send (GtkButton *button, gpointer *data);

GtkWidget *Create_Chatbox(gchar *UN,FENTRYC *frnd);

GtkWidget *Create_Friendlist(CLIENT *client);

//static GtkWidget *create_view_and_model(CLIENT *client);

//static GtkTreeModel *create_and_fill_model(CLIENT *client);

void message_into_window(MSLIST *list,GtkTextBuffer *tempbuffer);

void view_onRowActivated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata);

void add_command(gchar *string, gchar * command);

void insert_substring(gchar *a, gchar *b, gint position);

char *substring(char *string, int position, int length);

char* concat(const char *s1, const char *s2);

void on_receive (gchar *Receiver, gchar *Msg);

void hide_register (GtkWidget *widget);

void reopen_register();


//static void pop_up_window(int data);

GtkWidget *Create_Friend_Request(gchar *UN);

GtkWidget *Accpet_Friend_Request(gchar *UN);

void on_send_friend(GtkButton *button,GtkWidget *data);

void on_accept_friend(GtkButton *button,GtkWidget *data);

void destroy_window(GtkWidget *widget);


#endif
