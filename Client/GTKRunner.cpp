#include "GTKRunner.h"
#include <iostream>
#include <gtk/gtk.h>

GtkEntry * entry1;
GtkListStore* liststore;



void destroy( GtkWidget *widget, gpointer   data )
{
    gtk_main_quit ();
}


void login_clicked(GtkWidget* widget, gpointer data){
    //const gchar* aa = gtk_entry_get_text( GTK_ENTRY (entry1) );
    std::cout << "Login " << "  \n" ;
    //GtkTreeIter   iter;

    //gtk_list_store_append(liststore, &iter);

    /* Fill fields with some data */
    //gtk_list_store_set (liststore, &iter, 0, 'J', -1);


}



GTKRunner::GTKRunner() {

}

GTKRunner::~GTKRunner() {

}

void GTKRunner::Run(int* argc, char***argv){
    GtkWidget *gtkwindow;

    //auto window = gtk_application_window_new (app);
    //gtk_window_set_title (GTK_WINDOW (window), "Window");
    //gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
    //gtk_widget_show_all (window);


    GtkBuilder      *builder;
    //GtkWidget       *loginWindow;
    //GtkWidget       *lobbiesWindow;
    //GtkWidget       *loginButton;

    gtk_init (argc, argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "../Client/Launcher.glade", NULL);
    gtkwindow = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    //  loginWindow = GTK_WIDGET (gtk_builder_get_object (builder, "loginWindow"));
    //lobbiesWindow = GTK_WIDGET (gtk_builder_get_object (builder, "lobbiesWindow"));
    //loginButton = GTK_WIDGET (gtk_builder_get_object (builder, "login_button"));
    //entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
    //liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
    //g_signal_connect (loginButton, "clicked", G_CALLBACK(login_clicked), NULL);
    //  g_signal_connect (loginWindow, "destroy", G_CALLBACK (destroy), NULL);
    g_signal_connect (gtkwindow, "destroy", G_CALLBACK (destroy), NULL);
    // gtk_builder_connect_signals (builder, NULL);


    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (gtkwindow);
    // gtk_widget_show (loginWindow);
    gtk_main ();
}
