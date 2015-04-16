#include <gtk/gtk.h>

/* Get the selected filename and print it to the console */
static void file_ok_sel( GtkWidget        *w,
                         GtkFileSelection *fs )
{
    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));
}
/*void set_up_filters(GtkFileChooser *filew)
{
    GtkFileFilter *gtk_file_filter_new;

    filter=gtk_file_filter_new();
    gtk_file_filter_set_name(filter,"Text Files");
    gtk_file_filter_add_pattern(filter,"*");
    gtk_file_chooser_add_filter(filew,filter)
}*/
int main( int   argc,
          char *argv[] )
{
    GtkWidget *filew;
    GtkWidget *filter;


    gtk_init (&argc, &argv);

    /* Create a new file selection widget */
    filew = gtk_file_selection_new ("guitar tuner");
     GtkFileFilter *gtk_file_filter_new;

    filter= gtk_file_filter_new();
    gtk_file_filter_set_name(filter,"Text Files");
    gtk_file_filter_add_pattern(filter,"*");
    gtk_file_chooser_add_filter(filew,filter)

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
				     "Fast_&_Furious_7_Soundtrack_Get_Low.mp3");

    gtk_widget_show (filew);
    gtk_main ();
    return 0;
}
