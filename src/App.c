/*
To compile (GTK 4):
gcc App.c -o app $(pkg-config --cflags --libs gtk4)
step2:
./main
done
Tested with MSYS2 (ucrt64)
*/

#include <gtk/gtk.h>
int total;
typedef struct
{
    const char *name;
    int price;
} Item;

static void print(GtkWidget *btn, gpointer user_data)
{
    g_print("Hello world");
};
static void Total(GtkWidget *btn, gpointer user_data)
{
    Item *item = (Item *)user_data;
    total += item->price;

    g_print("%d\n", total);
};

static GtkWidget *Items(Item *item)
{
    // Main vertical box for the item
    GtkWidget *itembox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8); // 8 px spacing
    gtk_widget_set_size_request(itembox, 300, 400);

    // Item name label
    GtkWidget *iName = gtk_label_new(item->name);
    gtk_widget_set_halign(iName, GTK_ALIGN_CENTER);

    // Price label
    char priceText[20];
    sprintf(priceText, "₹%d", item->price);
    GtkWidget *iPrice = gtk_label_new(priceText);
    gtk_widget_set_halign(iPrice, GTK_ALIGN_CENTER);

    // Add-to-cart button
    GtkWidget *Adcbtn = gtk_button_new_with_label("ADD TO CART");
    gtk_widget_set_halign(Adcbtn, GTK_ALIGN_CENTER);

    // btn signal
    g_signal_connect(Adcbtn, "clicked", G_CALLBACK(Total), item);

    // Pack into box
    gtk_box_append(GTK_BOX(itembox), iName);
    gtk_box_append(GTK_BOX(itembox), iPrice);
    gtk_box_append(GTK_BOX(itembox), Adcbtn);

    // css
    gtk_widget_add_css_class(itembox, "itembox");
    gtk_widget_add_css_class(iName, "item-name");
    gtk_widget_add_css_class(iPrice, "item-price");
    gtk_widget_add_css_class(Adcbtn, "add-btn");

    return itembox;
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;    // Main vertical box
    GtkWidget *navbar; // Top navbar
    GtkWidget *Menu_box;
    GtkWidget *label;
    GtkWidget *scroll;
    GtkWidget *btn;
    GtkWidget *btn1;
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

    // Create a Scrollable window
    scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_hexpand(scroll, FALSE);
    gtk_box_append(GTK_BOX(box), scroll);

    // create a menu box
    Menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(Menu_box, -1, 800);
    gtk_widget_set_halign(Menu_box, GTK_ALIGN_FILL);
    gtk_widget_set_valign(Menu_box, GTK_ALIGN_END);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), Menu_box);
    // gtk_box_append(GTK_BOX(box), Menu_box);

    // create a grid box
    GtkWidget *grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(Menu_box), grid);

    // Adding items to the menu box

    static Item i1 = {"burgur", 50};
    static Item i2 = {"pizza", 50};
    static Item i3 = {"Misti Doi", 40};
    static Item i4 = {"Rosgulla", 40};
    static Item i5 = {"Butter Chicken", 40};

    GtkWidget *iBurgur = Items(&i1);
    GtkWidget *pizza = Items(&i2);
    GtkWidget *Misti = Items(&i3);
    GtkWidget *Rosgulla = Items(&i4);
    GtkWidget *Butterc = Items(&i5);

    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    gtk_grid_attach(GTK_GRID(grid), iBurgur, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), pizza, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), Misti, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), Rosgulla, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), Butterc, 4, 0, 1, 1);

    // Create navbar label
    label = gtk_label_new("Food Camp Menu");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(navbar), label);

    // Create navbar button
    btn = gtk_button_new_with_label("ORDERS");
    btn1 = gtk_button_new_with_label("HISTORY");

    // Wrap button in a horizontal box for right alignment
    btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(btn_box, GTK_ALIGN_START);
    // gtk_widget_set_margin_end(GTK_WIDGET(btn), 5);
    gtk_box_append(GTK_BOX(btn_box), btn);
    gtk_box_append(GTK_BOX(btn_box), btn1);
    gtk_box_append(GTK_BOX(navbar), btn_box);

    g_signal_connect(btn, "clicked", G_CALLBACK(print), NULL);

    // Apply CSS classes
    gtk_widget_add_css_class(box, "box");
    gtk_widget_add_css_class(navbar, "navbar");
    gtk_widget_add_css_class(label, "navbar-label");
    gtk_widget_add_css_class(btn, "Obtn");
    gtk_widget_add_css_class(btn1, "Hbtn");
    gtk_widget_add_css_class(Menu_box, "Menu_box");

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
                                      "}"
                                      ".Hbtn {"
                                      "  background-color: green;"
                                      "  color: black;"
                                      "  min-width: 100px;"
                                      "  min-height: 40px;"
                                      "  margin-top: 10px;"
                                      "  margin-right: 20px;"
                                      "}"
                                      ".Menu_box {"
                                      "  border: 5px solid red;"
                                      "  border-radius: 8px;"
                                      "}"
                                      ".add-btn { background-color: green; color: black; border-radius: 5px; padding: 6px 12px; }"
                                      ".itembox { border: 3px solid purple; border-radius: 12px; margin: 10px; padding: 10px; background-color: #fafafa; }"
                                      ".item-name { font-weight: bold; font-size: 16px; }"
                                      ".item-price { color: #333; margin-bottom: 6px; }");

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
