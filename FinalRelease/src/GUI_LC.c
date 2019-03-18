//modified by Yunhe Shao
//Deep Core Dumped
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <gtk/gtk.h>
#include <string.h>
#include "simple.h"
#include "TestClient.h"
#include "ServerFunctions.h"
#include "ChessStruct.h"
#include "Client.h"
#include "ClientLog.h"

GtkTreeModel *model1;

GtkWidget *view;//added
GtkWidget *window;
GtkWidget *fixed;
GtkWidget *chess_icon;
GtkWidget *table;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *board_fixed;
GtkWidget *Friendlist;
GtkWidget *Register_window;
//GtkWidget *Chat_window; commented out because created in the struct
GtkWidget *Login_window;
GtkWidget *Pop_ups;

GtkTextIter iter;

static GtkWidget* entry1;
static GtkWidget* entry2;

static GtkWidget* reg_entry1;
static GtkWidget* reg_entry2;
static GtkWidget* reg_entry3;

extern gchar username[20];
gchar password[20];
extern gchar FriendName[20];
extern gchar out_buffer[2000];

gchar message_receive[2000];
gchar buffer_message_display[2000];
gint *Message_Length;

#define BUFFSIZE 5000

static gboolean update_from_server(void);


//extern char Coord_buffer[6];
extern char ChessRequest_UN[20];
char Chess_flag[3];

enum GRID Board[8][8];
enum GRID BoardLocation[3][2]; //setting a new array to store clicking location. 0,0 is selectclick.
enum {COLUMN = 0, NUM_COLS};

char *Talk2Server(		/* communicate with the server */
	const char *Message,
	char *RecvBuf);

void InitBoard(){
int i, j;
for(i=0;i<8;i++)
        {
                for(j=0;j<8;j++)
                {
                        if(0 != i%2)
                        {
                                if(0 != j%2)
                                {
                                        Board[i][j] = WHITE;
                                }
                                else
                                {
                                        Board[i][j] = BLACK;
                                }
                        }
                        else
                        {
                if(0 != j%2)
                                {
                                        Board[i][j] = BLACK;
                                }
                                else
                                {
                                        Board[i][j] = WHITE;
                                }
                        }
                }
        }
   for(i = 0; i < 8; i++){
	Board[i][1] = BPawn;
	Board[i][6] = WPawn;
	}
   Board[0][0] = Board[7][0] = BRook;
   Board[0][7] = Board[7][7] = WRook;
   Board[1][0] = Board[6][0] = BKnight;
   Board[1][7] = Board[6][7] = WKnight;
   Board[2][0] = Board[5][0] = BBishop;
   Board[2][7] = Board[5][7] = WBishop;
   Board[3][7] = WQueen;
   Board[3][0] = BQueen;
   Board[4][7] = WKing;
   Board[4][0] = BKing;
}

void CheckColor(int i, int j)
{
  if(0 != i%2)
  {
          if(0 != j%2)
          {
                  Board[i][j] = WHITE;
          }
          else
          {
                  Board[i][j] = BLACK;
          }
  }
  else
  {
if(0 != j%2)
          {
                  Board[i][j] = BLACK;
          }
          else
          {
                  Board[i][j] = WHITE;
          }
  }
}

void callback(GtkWidget *widget,gpointer data)
{
    g_print("Hello again-%s was pressed\n",(gchar*) data);
}

void DrawBoard()
{
	int i, j;

    for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/Wsquare.jpg") ;
					break;
				case WKing:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/WKing.png") ;
					break;
				case BKing:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/BKing.png");
					break;
				case BPawn:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/BPawn.png");
					break;
				case WPawn:
					chess_icon = gtk_image_new_from_file("../src/chess_icon/WPawn.png");
					break;
        case WRook:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/WRook.png");
          break;
        case WKnight:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/WKnight.png");
          break;
        case WQueen:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/WQueen.png");
          break;
        case WBishop:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/WBishop.png");
          break;
        case BRook:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/BRook.png");
          break;
        case BKnight:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/BKnight.png");
          break;
        case BBishop:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/BBishop.png");
          break;
        case BQueen:
          chess_icon = gtk_image_new_from_file("../src/chess_icon/BQueen.png");
          break;
				default:
					break;

			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}
void GUIMove(int s_x, int s_y, int g_x, int g_y)
{

  BoardLocation[2][1] = Board[g_x][g_y];
  CheckColor(g_x, g_y);
  Board[s_x][s_y] = BoardLocation[2][1];
  DrawBoard();
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
  BoardLocation[0][0] = *g_x;
  BoardLocation[0][1] = *g_y;
}


void SelectCoordToGrid(int c_x, int c_y, int *s_x, int *s_y)
{
	*s_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*s_y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
  BoardLocation[1][0] = *s_x;
  BoardLocation[1][1] = *s_y;
}


//change the backgroud pic,don't change anything inside
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
	gtk_widget_set_app_paintable(widget, TRUE);		//allow to open a new image
	gtk_widget_realize(widget);


	gtk_widget_queue_draw(widget);

	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);
	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);

	GdkPixmap *pixmap = NULL;


	gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 10);
	gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);

	g_object_unref(src_pixbuf);
	g_object_unref(dst_pixbuf);
	g_object_unref(pixmap);
}

static gboolean
on_delete_event (GtkWidget *widget,
         GdkEvent  *event,
         gpointer   data)
{
  g_print ("delete event occurred\n");
  gtk_main_quit();
  return FALSE;
}

void hide_chat(GtkWidget *data)
{
	g_print("hide Chat box");
	gtk_widget_hide (data);
	//FriendName[0]  = '\0';
//	buffer = NULL;
}

void destroy(GtkWidget *widget,gpointer data)
{
    g_print("Exited\n");
    gtk_main_quit();
}

void show_board_window(GtkWidget *widget)
{
   gtk_widget_show_all(widget);
}

void show_register_window(GtkWidget *widget)
{
   gtk_widget_show_all(Register_window);
}

void show_login_window(GtkWidget *widget)
{
   gtk_widget_show_all(widget);
}

void hide (GtkWidget *widget)
{
    gtk_widget_hide (widget);
}

void hide_register (GtkWidget *widget)
{
	GtkWidget *Login_window_temp;
	gtk_widget_hide (widget);
	Login_window_temp = Create_login_window();
	show_login_window(Login_window_temp);
}

void reopen_register()
{
	gtk_widget_hide(Register_window);
	Register_window = Create_register_window();
	show_login_window(Register_window);
}

void select_click(GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{
      int coord_x, coord_y, grid_x, grid_y;
      GdkModifierType state ;
      printf("Which piece do you want to move?\n");

      gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ;

      SelectCoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

      printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

}

gint area_click (GtkWidget *widget,
                 GdkEvent  *event,
                 gpointer  data)
{

  //char words[MAX_MSGLEN] ;
  int coord_x_n, coord_y_n;
  int grid_s_x, grid_s_y;
  //struct BOARD *chess_board ;
  //struct SQUARE *chess_piece ;
  //struct SQUARE *piece_dest ;
  int Pre_x, Pre_y, Cu_x, Cu_y;
	//int test_x, test_y;

  GdkModifierType state ;
  gdk_window_get_pointer(widget->window, &coord_x_n, &coord_y_n, &state) ;

  CoordToGrid(coord_x_n, coord_y_n, &grid_s_x, &grid_s_y);

  printf("The new selct is coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x_n, coord_y_n, grid_s_x, grid_s_y);

  Pre_x = BoardLocation[0][0];
  Pre_y = BoardLocation[0][1];
  Cu_x = BoardLocation[1][0];
  Cu_y = BoardLocation[1][1];
  GUIMove(Pre_x, Pre_y, Cu_x, Cu_y);


	/*if (Coord_buffer[0] != NULL) {
		Pre_x = Coord_buffer[1];
		Pre_y = Coord_buffer[2];
		Cu_x = Coord_buffer[3];
		Cu_y = Coord_buffer[4];
		GUIMove(Pre_x, Pre_y, Cu_x, Cu_y);
	}*/
//testing for input moving board

	//Board[4][4] = Board[1][1];//this is for testing
  //MoveTheBKing(grid_x, grid_y);


  //gtk_container_remove(GTK_CONTAINER(fixed), board_fixed) ; //this function have no use
  table = gtk_table_new (0, 0, TRUE) ;
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
  DrawBoard();

  /*set fixed*/

  fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
  gtk_container_add(GTK_CONTAINER(board_fixed), fixed) ;

  gtk_widget_show_all(window) ;

  return FALSE ;
}
//This section is for string processing for changing all strings get and sent
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
char *substring(char *string, int position, int length)
{
   char *pointer;
   int c;

   pointer = malloc(length+1);

   if( pointer == NULL )
       exit(EXIT_FAILURE);

   for( c = 0 ; c < length ; c++ )
      *(pointer+c) = *((string+position-1)+c);

   *(pointer+c) = '\0';

   return pointer;
}

void insert_substring(gchar *a, gchar *b, gint position)
{
   gchar *f, *e;
   int length;

   length = strlen(a);

   f = substring(a, 0, position - 1 );
   e = substring(a, position, length-position+1);

   strcpy(a, "");
   strcat(a, f);
   free(f);
   strcat(a, b);
   strcat(a, e);
   free(e);
}

void add_command(gchar *string, gchar * command)
{
   int length;
   length = strlen(string);
   gchar temp_user[21];
   //gchar *temp_friend;
	 //gchar *temp_string = NULL;
	 int flag;
	 //MENTRY *User_Slot;
   if (strcmp(command, "M_S_G") == 0) {
		  printf("went into sending function");
		 	strcpy(out_buffer, "S_N_D");
		 	//strcat(temp_string, "S_N_D");
      //insert_substring(string, "\n", length+2);
			strcat(out_buffer, "\n");
			strcat(out_buffer, username);
			strcat(out_buffer, "\n");
			strcat(out_buffer, "R_C_V");
			strcat(out_buffer, "\n");
			strcat(out_buffer, FriendName);
			strcat(out_buffer, "\n");
			strcat(out_buffer, "M_S_G\n");
			strcat(out_buffer, string);
			strcat(out_buffer, "\n");
      g_print("%s This is the print out of add cmd",out_buffer);
			//strcpy(out_buffer, temp_string);
      }
   if (strcmp(command, "L_I") == 0) {
      g_print("%s",string);

			strcpy(temp_user, username);
      strcat(temp_user, "\n");
      g_print("%s",temp_user);

      strcat(password, "\n");
      g_print("%s",password);

      //there are maclloc involve here that might not freed properly
      string = concat(concat(string, temp_user), password);
      Talk2Server(string, message_receive);
			flag = Parsing(message_receive,strlen(message_receive));
			//User_Slot = clientglobal->userlist->first;
			//g_print("%s",User_Slot);
			if (flag == 1) {
				g_print("Login failed");
				hide(Login_window);
				Login_window = Create_login_window();
				show_login_window(Login_window);
			}
			else{
				//g_free(string);
				Friendlist = Create_Friendlist(clientglobal);
				show_login_window(Friendlist);
				hide(Login_window);
                                g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE,2000,(GSourceFunc)update_from_server,NULL,NULL);


			}
      }
    if (strcmp(command, "R_E_G") == 0)
      {
        insert_substring(string, "R_E_G\n", 1);
        g_print("%sThis is the print out of add cmd",string);
        Talk2Server(string, message_receive);
				Parsing(message_receive,strlen(message_receive));
      }
		if (strcmp(command, "C_S") == 0)
		{
printf("THe userserlkj;lkgj;slkj;lkjlkjlj;Username :%s\n",FriendName);
			strcpy(out_buffer, "C_S\n");
			strcat(out_buffer, username);
			strcat(out_buffer, "\n");
			strcat(out_buffer, FriendName);
			strcat(out_buffer, "\n");
			strcat(out_buffer, Chess_flag);
			g_print("%s This is the print out of add cmd",out_buffer);
			Talk2Server(out_buffer, message_receive);
printf("THe userserlkj;lkgj;slkj;lkjlkjlj;Username now :%s\n",FriendName);

		}
/*
		if (strcmp(command, "U_P_D") == 0)
		{
			strcpy(out_buffer, "U_P_D\n");
			strcat(out_buffer, username);
			strcat(out_buffer,"\n");
			g_print("%s This is the print out of add cmd",out_buffer);
			Talk2Server(out_buffer, message_receive);

		}*/


}
GtkWidget *Create_Friend_Request(gchar *UN){
  GtkWidget*window;
	GtkWidget* label1;
	GtkWidget* button;
	GtkWidget* box;
	GtkWidget* box1;
	GtkWidget* box2;
	gchar newtitle[40];

	strcpy(newtitle,"Sending to: ");
	strcat(newtitle,UN);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),newtitle);
	gtk_window_set_position(GTK_WINDOW(Login_window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(Login_window,100,50);

	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	box1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,10);
	box2 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,10);

	label1 = gtk_label_new("Do you want to send a friend request?");
	gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);

	button = gtk_button_new_with_label("Yes");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_send_friend),window);
	g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(hide_chat),window);
	gtk_box_pack_start(GTK_BOX(box2),button,TRUE,TRUE,10);
	gtk_widget_show(button);

	return window;
}

GtkWidget *Accpet_Friend_Request(gchar *UN){
        GtkWidget* window;
	GtkWidget* label1;
	GtkWidget* button;
	GtkWidget* box;
	GtkWidget* box1;
	GtkWidget* box2;
	gchar newtitle[40];

	strcpy(newtitle,"Accept from : ");
	strcat(newtitle,UN);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),newtitle);
	gtk_window_set_position(GTK_WINDOW(Login_window),GTK_WIN_POS_CENTER);
	gtk_widget_set_size_request(Login_window,100,50);

	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	box1 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,10);
	box2 = gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,10);

	label1 = gtk_label_new("Do you want accept this friend request?");
	gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);

	button = gtk_button_new_with_label("Yes");
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(on_accept_friend),window);
	g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(hide_chat),window);
	gtk_box_pack_start(GTK_BOX(box2),button,TRUE,TRUE,10);
	gtk_widget_show(button);

	return window;
}

GtkWidget *Create_Board()
{
  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
  gtk_window_set_title(GTK_WINDOW(window), "Deep Core Dumped") ;
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;

  /*Add bottoms on window*/
  button1 = gtk_button_new_with_label("Undo");
  g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(callback),"Undo pressed");

  button2 = gtk_button_new_with_label("Hint");
  g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(callback),"Hint pressed");


  button3 = gtk_button_new_with_label("Quit");
  g_signal_connect(G_OBJECT(button3),"clicked",G_CALLBACK(hide),window);
  //g_signal_connect_swapped(G_OBJECT(button3),"clicked",G_CALLBACK(gtk_widget_destroy),window);


  /*register event handlers*/
	g_signal_connect(window,"delete_event",G_CALLBACK(hide_chat),window);

  //gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ;
  gtk_widget_set_events(window,GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK) ;
  g_signal_connect(window, "button_press_event", G_CALLBACK(select_click), NULL) ;
  g_signal_connect(window, "button_release_event", G_CALLBACK(area_click), NULL) ;

  /*create a table and draw the board*/

  InitBoard();
  table = gtk_table_new (8, 8, TRUE) ;
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;

  DrawBoard();
  board_fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(board_fixed), table, 0, 0) ;
  gtk_container_add(GTK_CONTAINER(window), board_fixed) ;

  gtk_fixed_put(GTK_FIXED(board_fixed),button1,400,50);
  gtk_fixed_put(GTK_FIXED(board_fixed),button2,400,100);
  gtk_fixed_put(GTK_FIXED(board_fixed),button3,400,150);


  fixed = gtk_fixed_new() ;
  gtk_fixed_put(GTK_FIXED(board_fixed), fixed, 0, 0) ;
	return window;
}


void Login_on_button_clicked (GtkWidget* button,gpointer data)
{
	gchar reg_username[20];
	gchar reg_password[100];
	gchar reg_password_check[100];
	const gchar* Username;
	const gchar* Password;
    if ((int)data == 1){
        gtk_entry_set_text(GTK_ENTRY(entry1),"");
        gtk_entry_set_text(GTK_ENTRY(entry2),"");
    }
		if ((int)data == 2){
				//strcpy(Username, gtk_entry_get_text(GTK_ENTRY(entry1)));
				//strcpy(Password, gtk_entry_get_text(GTK_ENTRY(entry2)));
        Username = gtk_entry_get_text(GTK_ENTRY(entry1));
        Password = gtk_entry_get_text(GTK_ENTRY(entry2));
				strcpy(username, Username);
				strcpy(password, Password);
        add_command("L_I\n", "L_I");
   }
		if ((int)data == 3){
        //Change Editable status
        gtk_editable_set_editable(GTK_EDITABLE(entry1),GTK_TOGGLE_BUTTON(button)->active);
        gtk_editable_set_editable(GTK_EDITABLE(entry2),GTK_TOGGLE_BUTTON(button)->active);
    }
     if ((int)data == 4){
      g_print("entered data 4");
      show_board_window(window);
     }
     if ((int)data == 5){
      g_print("entered data 5");
			Register_window = Create_register_window();
      show_register_window(Register_window);
    }
     if ((int)data == 6) {
      g_print("Regiter process");
			strcpy(reg_username, gtk_entry_get_text(GTK_ENTRY(reg_entry1)));
			strcpy(reg_password, gtk_entry_get_text(GTK_ENTRY(reg_entry2)));
			strcpy(reg_password_check, gtk_entry_get_text(GTK_ENTRY(reg_entry3)));
			g_print("1 st: %s", reg_password);
			g_print("2 st: %s", reg_password_check);

      if (strcmp(reg_password, reg_password_check) != 0)
			{
        g_print("password doesn't match!!");
				reopen_register();
      }
      strcat(reg_username,"\n");
      strcat(reg_username, reg_password);
			strcat(reg_username, "\n");
      add_command(reg_username, "R_E_G");
			hide(Register_window);
			Login_window = Create_login_window();
			show_login_window(Login_window);

	//		Friendlist =Create_Friendlist(clientglobal);
	//		gtk_widget_show_all(Friendlist);
		}
		if ((int)data == 7){
		 g_print("entered play chess");
		 window = Create_Board();
		 show_board_window(window);
		 strcpy(Chess_flag, "w\n");
		 add_command("WHITE", "C_S");
	 	}
	 if ((int)data == 8){
		g_print("entered play chess");
		window = Create_Board();
		show_board_window(window);
		strcpy(Chess_flag, "b\n");
		add_command("BLACK", "C_S");
		}
		 if ((int)data == 9){
			g_print("entered play chess");
			window = Create_Board();
			show_board_window(window);
		}
}

GtkWidget *Create_login_window()
{
    //GtkWidget* window;
    GtkWidget* box;
    GtkWidget* box1;
    GtkWidget* box2;
    GtkWidget* box3;
    GtkWidget* label1;
    GtkWidget* label2;
    GtkWidget* button;
    GtkWidget* sep;
    GtkWidget* Login_window;
    //initialization
    //set window
    Login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(Login_window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(Login_window),"Welcome Comrade!!");
    gtk_window_set_position(GTK_WINDOW(Login_window),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(Login_window,480,270);

    //gtk_container_set_border_width(GTK_CONTAINER(Login_window),40);

    box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(Login_window),box);
    box1 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,10);
    box2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,10);
    sep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box),sep,FALSE,FALSE,10);
    box3 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);


    label1 = gtk_label_new("username：");
    entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),entry1,FALSE,FALSE,5);

    label2 = gtk_label_new("password：");
    entry2 = gtk_entry_new();
    //Let the text to be invisible
    gtk_entry_set_visibility(GTK_ENTRY(entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),entry2,FALSE,FALSE,5);

    button = gtk_check_button_new_with_label("Editable");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)3);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button),TRUE);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,10);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Clear");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)1);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,10);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Register");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)5);
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(hide),Login_window);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,10);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Log In");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)2);
    //g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(hide),Login_window);
    //g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),Login_window);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,5);
		chang_background(Login_window, 480,270, "../src/chess_icon/BackGroud_Login.jpg");
    gtk_widget_show(button);

   return Login_window;
}


GtkWidget *Create_register_window()
{
    //GtkWidget* window;
    GtkWidget* box;
    GtkWidget* box1;
    GtkWidget* box2;
    GtkWidget* box3;
    GtkWidget* box4;
    GtkWidget* label1;
    GtkWidget* label2;
    GtkWidget* label3;
    GtkWidget* button;
    GtkWidget* Window;
    //initialization
    //set window
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(Window),"destroy",G_CALLBACK(destroy),NULL);
    gtk_window_set_title(GTK_WINDOW(Window),"Welcome Comrade!!");
    gtk_window_set_position(GTK_WINDOW(Window),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(Window,480,270);

    box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(Window),box);
    box1 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box1,TRUE,TRUE,10);
    box2 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box2,TRUE,TRUE,10);
    box3 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box3,FALSE,FALSE,10);
    box4 = gtk_hbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(box),box4,FALSE,FALSE,10);


    label1 = gtk_label_new("username：");
    reg_entry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(box1),label1,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box1),reg_entry1,FALSE,FALSE,5);

    label2 = gtk_label_new("password：");
    reg_entry2 = gtk_entry_new();
    /*Let the text to be invisible*/
    gtk_entry_set_visibility(GTK_ENTRY(reg_entry2),FALSE);
    gtk_box_pack_start(GTK_BOX(box2),label2,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box2),reg_entry2,FALSE,FALSE,5);

    label3 = gtk_label_new("Retype Passcode");
    reg_entry3 = gtk_entry_new();
    /*Let the text to be invisible*/
    gtk_entry_set_visibility(GTK_ENTRY(reg_entry3),FALSE);
    gtk_box_pack_start(GTK_BOX(box3),label3,FALSE,FALSE,5);
    gtk_box_pack_start(GTK_BOX(box3),reg_entry3,FALSE,FALSE,5);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(hide_register),Window);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,10);
    gtk_widget_show(button);

    button = gtk_button_new_with_label("Register!");
    g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)6);
    g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(hide),Window);
    //g_signal_connect_swapped(G_OBJECT(button),"clicked",G_CALLBACK(gtk_widget_destroy),Login_window);
    gtk_box_pack_start(GTK_BOX(box3),button,TRUE,TRUE,5);
    gtk_widget_show(button);
		chang_background(Window, 480,270, "../src/chess_icon/BackGroud_Login.jpg");

   return Window;
}

void view_onRowActivated (GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata){
   GtkTreeModel *model;
   GtkTreeIter iter;
   model = gtk_tree_view_get_model(treeview);
   if (gtk_tree_model_get_iter(model, &iter, path)){
      gchar *name;
      gchar name1[20];
      name1[0] = '\0';
      gtk_tree_model_get(model, &iter, COLUMN, &name, -1);
printf("A row was double clicked: %s\n", name);
        if((name[0] == 'F') && (name[1] == '_')){
            GetUsername(FriendName, (name + 3));
	    Pop_ups = Accpet_Friend_Request(FriendName);
	    show_login_window(Pop_ups);
        } else {
        if((name[0] == 'U') && (name[1] == '_')){
printf("got ot here\n");
            GetUsername(FriendName, (name + 2));
            FENTRYC *entry1, *entry2;
            entry1 = clientglobal->friendlist->first;
            int occurrence = 0;
            while(entry1){
		   entry2 = entry1->next;
                   GetUsername(name1,entry1->username);
                            if(0 == strcmp(name1,FriendName)){
			        occurrence = 1;
                                break;
                            }
                            entry1 = entry2;
            }
                if(occurrence == 0){
                    Pop_ups = Create_Friend_Request(FriendName);
                    show_login_window(Pop_ups);
                }
        } else {
        if(0 == strcmp(name,"LOGOUT")){
            int check = -1;
            strcpy(out_buffer, "L_O");
	    strcat(out_buffer, "\n");
	    strcat(out_buffer, username);
	    strcat(out_buffer, "\n");
            Talk2Server(out_buffer, message_receive);
            check = Parsing(message_receive,strlen(message_receive));
            if(check == 0){
                destroy(Friendlist,NULL);
                return;
            }
        } else {
             GetUsername(FriendName,name);
             FENTRYC *entry1, *entry2;
             entry1 = clientglobal->friendlist->first;
             while(entry1){
		            entry2 = entry1->next;
                            GetUsername(name1,entry1->username);
                            if(0 == strcmp(name1,FriendName)){
			        entry1->Chat_window = Create_Chatbox(FriendName,entry1);
			        entry1->Chat_window = Create_Chatbox(FriendName,entry1);
			        gtk_widget_show_all(entry1->Chat_window);
                                message_into_window(entry1->history,entry1->buffer);
                                break;
                            }
                            entry1 = entry2;
                        }
        }}}
        g_free(name);
   }
}



//this function is to send one friend's message history into the GUI text window
//history: S_N_D\nUsername\nM_S_G\nHistory1\nS_N_D\nUsername\nM_S_G\nHistory1\nS_N_D\nE_N_D
void message_into_window(MSLIST *list,GtkTextBuffer *tempbuffer){
    assert(list);
    MENTRY *message1;
    MENTRY *message2;
    message1 = list->first;
    int count = 0;
    while (message1){
        message2 = message1->next;
        if((list->length - count) < 10){
            if(tempbuffer){
                gtk_text_buffer_get_end_iter(tempbuffer,&iter);
                gtk_text_buffer_insert(tempbuffer,&iter,message1->message,-1);
         	gtk_text_buffer_insert(tempbuffer,&iter,"\n",-1); //adding end of line char
                gtk_text_buffer_get_end_iter(tempbuffer,&iter);
            }
        }
        count++;
        message1 = message2;
   }
//   gtk_text_buffer_insert(tempbuffer,&iter,"\n",-1); //adding end of line char

   return;
}




static GtkTreeModel *create_and_fill_model(CLIENT *client)
{
   GtkTreeStore *treestore;
   GtkTreeIter toplevel, child;
	 FENTRYC *Friend_Slot;//Pointer to get Friend
	 FENTRYC *Friend_Slot_Next;//to get next friend
	 MENTRY *User_Slot;//Pointer to get user
	 MENTRY *User_Slot_Next;//pointer to get next user
         MENTRY *Request_Slot;
         MENTRY *Request_Slot_Next;

   treestore = gtk_tree_store_new(NUM_COLS, G_TYPE_STRING);


   gtk_tree_store_append(treestore, &toplevel, NULL);
   gtk_tree_store_set(treestore, &toplevel, COLUMN, "My Friend", -1);

	 Friend_Slot = client->friendlist->first;
	 while (Friend_Slot != NULL) {
         Friend_Slot_Next = Friend_Slot->next;
		 gtk_tree_store_append(treestore, &child, &toplevel);
		 gtk_tree_store_set(treestore, &child, COLUMN, Friend_Slot->username, -1);
		 g_print("%s", Friend_Slot->username);
		 Friend_Slot = Friend_Slot_Next;
	 }

   gtk_tree_store_append(treestore, &toplevel, NULL);
   gtk_tree_store_set(treestore, &toplevel, COLUMN, "Users", -1);
	 User_Slot = client->userlist->first;
	 while (User_Slot != NULL) {
             User_Slot_Next = User_Slot->next;
             char temp1[20];
             GetUsername(temp1,(User_Slot->message + 2));
             if(0 != strcmp(temp1,username)){

		 gtk_tree_store_append(treestore, &child, &toplevel);
		 gtk_tree_store_set(treestore, &child, COLUMN, User_Slot->message, -1);
             }
		 User_Slot = User_Slot_Next;

         }
   gtk_tree_store_append(treestore, &toplevel, NULL);
   gtk_tree_store_set(treestore, &toplevel, COLUMN, "Friend Requests", -1);
	 Request_Slot = client->friendrequest->first;
	 while (Request_Slot != NULL) {
                 Request_Slot_Next = Request_Slot->next;
		 gtk_tree_store_append(treestore, &child, &toplevel);
		 gtk_tree_store_set(treestore, &child, COLUMN, Request_Slot->message, -1);
		 Request_Slot = Request_Slot_Next;
	 }
         gtk_tree_store_append(treestore, &toplevel, NULL);
         gtk_tree_store_set(treestore, &toplevel, COLUMN, "LOGOUT", -1);

   //gtk_tree_store_append(treestore, &child, &toplevel);
   //gtk_tree_store_set(treestore, &child, COLUMN, "C", -1);
   return GTK_TREE_MODEL(treestore);
}


static GtkWidget *create_view_and_model(CLIENT *client)
{
   GtkTreeViewColumn *col;
   GtkCellRenderer *renderer;
   //GtkWidget *view;
//   GtkTreeModel *model;
   view = gtk_tree_view_new();

   col = gtk_tree_view_column_new();
   gtk_tree_view_column_set_title(col, "Friend List");
   gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

   renderer = gtk_cell_renderer_text_new();
   gtk_tree_view_column_pack_start(col, renderer, TRUE);
   gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);

   model1 = create_and_fill_model(client);
   gtk_tree_view_set_model(GTK_TREE_VIEW(view), model1);
   g_object_unref(model1);

   return view;
}

GtkWidget *Create_Friendlist(CLIENT *client){

   //GtkWidget *view;
   GtkWidget *Friendlist;
   GtkTreeSelection *selection;
   GtkWidget *vbox;
   GtkWidget *statusbar;

   Friendlist = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   g_signal_connect(Friendlist, "delete_event", G_CALLBACK(on_delete_event), NULL);
   gtk_window_set_position(GTK_WINDOW(Friendlist), GTK_WIN_POS_CENTER);
   gtk_window_set_title(GTK_WINDOW(Friendlist), "Tree View");
   gtk_widget_set_size_request(Friendlist, 200, 500);

   vbox = gtk_vbox_new(FALSE, 2);
   gtk_container_add(GTK_CONTAINER(Friendlist), vbox);

   view = create_view_and_model(client);
   selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
   gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);

   statusbar = gtk_statusbar_new();
   gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);

   g_signal_connect(view, "row-activated", (GCallback) view_onRowActivated, NULL);

   return Friendlist;
}

void on_receive (gchar *Receiver, gchar *Msg){
    GtkTextBuffer *tempbuffer;
    char name1[20];
    name1[0] = '\0';

    FENTRYC *entry1, *entry2;
        entry1 = clientglobal->friendlist->first;
        while(entry1){
            entry2 = entry1->next;
            GetUsername(name1,entry1->username);
            if(0 == strcmp(name1,Receiver)){
	        tempbuffer = entry1->buffer;
                break;
            }
            entry1 = entry2;
        }
    if(tempbuffer){
        gtk_text_buffer_get_end_iter(tempbuffer,&iter);
        gtk_text_buffer_insert(tempbuffer,&iter,Msg,-1); //display temp message
        gtk_text_buffer_get_end_iter(tempbuffer,&iter);
    }
}

void on_send(GtkButton *button, gpointer *data)
{
  const gchar *message;
  gchar Modify_Message[100];
  //this is the pointer to the correct buffer.
  GtkTextBuffer *tempbuffer;

  gchar Message_Server[100];
	gchar *FriendHeader;
 //get the username from the window header
 gchar UN[40];
 strcpy(UN,gtk_window_get_title(GTK_WINDOW(data)));
 strcpy(UN,(UN + 15));
    char name1[20];
    name1[0] = '\0';
    GtkWidget *text = NULL;
    GtkWidget *message_entry;
                         //find the buffer to the window that is current
                        FENTRYC *entry1, *entry2;
                        entry1 = clientglobal->friendlist->first;
                        while(entry1){
                            entry2 = entry1->next;
                            GetUsername(name1,entry1->username);
                            if(0 == strcmp(name1,UN)){
		                tempbuffer = entry1->buffer;
                                text = entry1->text;
                                message_entry = entry1->message_entry;
                                break;
                            }
                            entry1 = entry2;
                        }
        message = gtk_entry_get_text(GTK_ENTRY(message_entry));
	strcpy(Modify_Message, message);
	strcpy(Message_Server, message);
	FriendHeader = FriendName;
        tempbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
        gtk_text_buffer_get_end_iter(tempbuffer,&iter);
	gtk_text_buffer_insert(tempbuffer,&iter, username,-1); //display that user's name
	gtk_text_buffer_insert(tempbuffer,&iter, ": ",-1);
	gtk_text_buffer_insert(tempbuffer,&iter,Modify_Message,-1); //display user's message
	gtk_text_buffer_insert(tempbuffer,&iter,"\n",-1); //adding end of line cha
        AppendMes(entry1->history,message,username);
                        //Preparing the outgoing message
		 	strcpy(out_buffer, "S_N_D");
			strcat(out_buffer, "\n");
			strcat(out_buffer, username);
			strcat(out_buffer, "\n");
			strcat(out_buffer, "R_C_V");
			strcat(out_buffer, "\n");
			strcat(out_buffer, UN);
			strcat(out_buffer, "\n");
			strcat(out_buffer, "M_S_G\n");
			strcat(out_buffer,message);
			strcat(out_buffer, "\n");
  //Send the message and parse the incoming data
  Talk2Server(out_buffer, message_receive);
  Parsing(message_receive,strlen(message_receive));
  gtk_entry_set_text(GTK_ENTRY(message_entry), "");
}



void on_delete_friend(GtkButton *button,GtkWidget *data)
{
 //get the username from the window header
 gchar UN[40];
 strcpy(UN,gtk_window_get_title(GTK_WINDOW(data)));
 strcpy(UN,(UN + 15));
 strcpy(out_buffer, "D_F_N");
 strcat(out_buffer, "\n");
 strcat(out_buffer, username);
 strcat(out_buffer, "\n");
 strcat(out_buffer, UN);
 strcat(out_buffer, "\n");
  //Send the message and parse the incoming data
  Talk2Server(out_buffer, message_receive);
  Parsing(message_receive,strlen(message_receive));
  hide_chat(data);
}

void on_send_friend(GtkButton *button,GtkWidget *data)
{
 //get the username from the window header
 gchar UN[40];
 strcpy(UN,gtk_window_get_title(GTK_WINDOW(data)));
 strcpy(UN,(UN + 12));
 strcpy(out_buffer, "F_N_R");
 strcat(out_buffer, "\n");
 strcat(out_buffer, username);
 strcat(out_buffer, "\n");
 strcat(out_buffer, UN);
 strcat(out_buffer, "\n");
  //Send the message and parse the incoming data
  Talk2Server(out_buffer, message_receive);
  Parsing(message_receive,strlen(message_receive));
  hide_chat(data);

}

void on_accept_friend(GtkButton *button,GtkWidget *data){
	gchar UN[40];
	strcpy(UN,gtk_window_get_title(GTK_WINDOW(data)));
	strcpy(UN,(UN + 15));
                        char tempname[20];
                        MENTRY *entry1, *entry2;
                        entry1 = clientglobal->friendrequest->first;
                        while(entry1){
                            entry2 = entry1->next;
                            GetUsername(tempname,(entry1->message + 4));
printf("the username %s the username of the box %s\n",tempname,UN);
                            if(0 == strcmp(tempname,UN)){
		                DeleteMessageEntry(entry1);
                                break;
                            }
                            entry1 = entry2;
                        }
	strcpy(out_buffer, "F_N_A");
	strcat(out_buffer, "\n");
	strcat(out_buffer, username);
	strcat(out_buffer, "\n");
	strcat(out_buffer, UN);
	strcat(out_buffer, "\n");
	 //Send the message and parse the incoming data
	 Talk2Server(out_buffer, message_receive);
	 Parsing(message_receive,strlen(message_receive));
	 hide_chat(data);
}




GtkWidget *Create_Chatbox(gchar *UN,FENTRYC *frnd){
  GtkWidget *window;
  GtkWidget *vbox,*hbox,*button,*label,*view,*black_button,*white_button,*accpet;
  gchar newtitle[40];

  strcpy(newtitle,"Chatting with: ");
  strcat(newtitle,UN);

  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),newtitle);

  g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(hide_chat),window);

  gtk_container_set_border_width(GTK_CONTAINER(window),10); //30

  vbox=gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(window),vbox);

  hbox=gtk_hbox_new(FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,30);

  white_button=gtk_button_new_with_label("Chess Game as white");
  gtk_box_pack_start(GTK_BOX(hbox),white_button,FALSE,FALSE,10);
  g_signal_connect(G_OBJECT(white_button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)7);

  //The back button need to be fixed
  black_button=gtk_button_new_with_label("Chess Game as black");
  gtk_box_pack_start(GTK_BOX(hbox),black_button,FALSE,FALSE,10);
  g_signal_connect(G_OBJECT(black_button),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)8);

  accpet=gtk_button_new_with_label("Accept Game");
  gtk_box_pack_start(GTK_BOX(hbox),accpet,FALSE,FALSE,10);
  g_signal_connect(G_OBJECT(accpet),"clicked",G_CALLBACK(Login_on_button_clicked),(gpointer)9);

  white_button=gtk_button_new_with_label("Delete Friend");
  gtk_box_pack_start(GTK_BOX(hbox),white_button,FALSE,FALSE,10);
  g_signal_connect(G_OBJECT(white_button),"clicked",G_CALLBACK(on_delete_friend),window);

  view = gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(view),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  frnd->text = gtk_text_view_new();
  printf("TextView text created address is : %p\n",frnd->text);
  gtk_box_pack_start(GTK_BOX(vbox),view,TRUE,TRUE,40);
  gtk_container_add(GTK_CONTAINER(view),frnd->text);//scroll


  frnd->buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(frnd->text));
  hbox=gtk_hbox_new(FALSE,0);
  gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,20);
  label=gtk_label_new("enter message");
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,10);
  frnd->message_entry=gtk_entry_new();
  printf("message entry created address is : %p\n",frnd->message_entry);
  gtk_box_pack_start(GTK_BOX(hbox),frnd->message_entry,FALSE,FALSE,40);
  button=gtk_button_new_with_label("    send    ");
  gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,10);
  g_signal_connect(GTK_BUTTON(button),"clicked",G_CALLBACK(on_send),window);

	//gtk_widget_show_all(window);
  return window;
}



static gboolean update_from_server(void){
       //add_command(" ", "M_S_G");
        strcpy(out_buffer,"U_P_D\n");
        strcat(out_buffer,username);
        strcat(out_buffer,"\n");
 	Talk2Server(out_buffer, message_receive);
        Parsing(message_receive,strlen(message_receive));
        model1 = create_and_fill_model(clientglobal);
        gtk_tree_view_set_model(GTK_TREE_VIEW(view), model1);
	gtk_tree_view_expand_all(view);
        g_object_unref(model1);
	return TRUE;
}
void destroy_window(GtkWidget *widget)
{
    gtk_widget_destroy(widget);
}



//EOF
