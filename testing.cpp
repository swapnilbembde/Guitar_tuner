#include <gtk/gtk.h>
#include"p4.cpp"
#include"test2.cpp"
#include"nearest.cpp"

char buf[5];

void print(GtkWidget *widget, gpointer label)
{

    int a=mai();
    char note=nearest_note(a);
    int notefre=notefreq(note);
  sprintf(buf, "%d\n%c\n%d",a,note,notefre);
  nearest_note(a);


  gtk_label_set_text(GTK_LABEL(label), buf);
}
void show_add(GtkWidget *widget, gpointer window)
{
  //GtkWidget *dialog;
  //dialog = gtk_message_dialog_new(GTK_WINDOW(window),
          //  GTK_DIALOG_DESTROY_WITH_PARENT,
            //GTK_MESSAGE_add);
            //GTK_BUTTONS_OK,
            //"Browse", "title");

  //gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  //gtk_dialog_run(GTK_DIALOG(dialog));
  //gtk_widget_destroy(dialog);
  GtkWidget *filew;
  filew = gtk_file_selection_new ("File selection");
  g_signal_connect (filew, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    /* Connect the ok_button to file_ok_sel function */
    g_signal_connect (GTK_FILE_SELECTION (filew)->ok_button,
		      "clicked", G_CALLBACK (file_ok_sel), (gpointer) filew);

    /* Connect the cancel_button to destroy the widget */
    g_signal_connect_swapped (GTK_FILE_SELECTION (filew)->cancel_button,
	                      "clicked", G_CALLBACK (gtk_widget_destroy),
			      filew);

    /* Lets set the filename, as if this were a save dialog, and we are giving
     a default filename */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew),
				     "penguin.png");

    gtk_widget_show (filew);
}



void Real_time(GtkWidget *widget, gpointer window)
{
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_QUESTION,
            GTK_BUTTONS_YES_NO,
            "Start Input");
  gtk_window_set_title(GTK_WINDOW(dialog), "Input");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}


int main( int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *table;
   GtkWidget *label;
   GtkWidget *frame1;


  GtkWidget *add;
  GtkWidget *free;
  GtkWidget *fre;


  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
  gtk_window_set_title(GTK_WINDOW(window), "Guitar Tuner");

  table = gtk_table_new(2, 2, TRUE);
  gtk_table_set_row_spacings(GTK_TABLE(table), 2);
  gtk_table_set_col_spacings(GTK_TABLE(table), 2);

  add = gtk_button_new_with_label("Add File");

  fre = gtk_button_new_with_label("Real time tuner");
  frame1 = gtk_frame_new("Output Frequency");
  gtk_frame_set_shadow_type(GTK_FRAME(frame1), GTK_SHADOW_IN);
  free = gtk_button_new_with_label("Frequency");

  label = gtk_label_new("Frequency");





  gtk_table_attach(GTK_TABLE(table), add, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
  gtk_table_attach(GTK_TABLE(table), free, 2, 3, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
  gtk_table_attach(GTK_TABLE(table), fre, 0, 1, 2, 3, GTK_FILL, GTK_FILL, 3, 3);
  gtk_table_attach(GTK_TABLE(table), frame1 , 2, 3, 2, 5, GTK_FILL, GTK_FILL, 3, 3);



  gtk_container_add(GTK_CONTAINER(window), table);
  gtk_container_set_border_width(GTK_CONTAINER(window), 150);

 gtk_container_add (GTK_CONTAINER (frame1), label);

  g_signal_connect(G_OBJECT(add), "clicked",
        G_CALLBACK(show_add), (gpointer) window);

  g_signal_connect(free, "clicked",
      G_CALLBACK(print), label);

  g_signal_connect(G_OBJECT(fre), "clicked",
        G_CALLBACK(Real_time), (gpointer) window);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

