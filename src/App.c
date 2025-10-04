/*
To compile (GTK 4):
gcc App.c -o app $(pkg-config --cflags --libs gtk4)
step2:
./main
done
Tested with MSYS2 (ucrt64)
*/

#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;    // Main vertical box
    GtkWidget *navbar; // Top navbar
    GtkWidget *label;
    GtkWidget *btn;
    GtkWidget *btn_box; // Box to align button to the right

    // Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Canteen Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);

    // Create the main vertical container
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // Create the navbar (vertical box)
    navbar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(navbar, -1, 150); // Height only
    gtk_widget_set_halign(navbar, GTK_ALIGN_FILL);
    gtk_widget_set_valign(navbar, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(box), navbar);

    // Create label
    label = gtk_label_new("Food Camp Menu");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(navbar), label);

    // Create button
    btn = gtk_button_new_with_label("ORDERS");

    // Wrap button in a horizontal box for right alignment
    btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(btn_box, GTK_ALIGN_END);
    gtk_box_append(GTK_BOX(btn_box), btn);
    gtk_box_append(GTK_BOX(navbar), btn_box);

    // Apply CSS classes
    gtk_widget_add_css_class(box, "box");
    gtk_widget_add_css_class(navbar, "navbar");
    gtk_widget_add_css_class(label, "navbar-label");
    gtk_widget_add_css_class(btn, "Obtn");

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
                                      ".box {"
                                      "  border: 5px solid black;"
                                      "  border-radius: 8px;"
                                      "}"
                                      ".navbar {"
                                      "  border: 2px solid white;"
                                      "  border-radius: 8px;"
                                      "  background-color: #333333;"
                                      "  margin-top: 5px;"
                                      "  padding: 10px;"
                                      "}"
                                      ".navbar-label {"
                                      "  font-style: italic;"
                                      "  font-size: 32px;"
                                      "  color: red;"
                                      "}"
                                      ".Obtn {"
                                      "  background-color: green;"
                                      "  color: black;"
                                      "  min-width: 100px;"
                                      "  min-height: 40px;"
                                      "  margin-top: 10px;"
                                      "  margin-right: 20px;"
                                      "}");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
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
