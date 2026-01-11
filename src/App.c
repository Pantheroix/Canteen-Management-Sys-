/*
To compile (GTK 4):
gcc App.c -o app $(pkg-config --cflags --libs gtk4)
step2:
./app
done
Tested with MSYS2 (ucrt64)
*/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "../backend/Menupage.h"
#include "../backend/css.h"
#include "../backend/NavBar.h"
#include "../backend/OrderPage.h"
#include "../backend/HistoryPage.h"

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    // Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Canteen Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 700);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    /*stack*/
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);
    GtkWidget *Order_page = order_page();
    GtkWidget *History_page = history_page();
    GtkWidget *Menu_page = menu_page();

    GtkWidget *navbar = show_navbar(stack, Menu_page, Order_page, History_page);

    /*Add Navbar to the main box*/
    gtk_box_append(GTK_BOX(main_box), navbar);
    /*Add Stack to the main box*/
    gtk_box_append(GTK_BOX(main_box), stack);

    // Create the main vertical container
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    // Load CSS
    GtkCssProvider *provider = load_css();
    g_object_unref(provider);

    // Show the window
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.CanteenApp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
