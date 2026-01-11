#ifndef MENUPAGE_H
#define MENUPAGE_H
#include "../backend/CartitemLL.h"
#include "../backend/OrderQueue.h"
int total = 0;
GtkWidget *cart_item_box;
GtkWidget *totallabel;

CartItem *head = NULL;

typedef struct
{
    const char *name;
    int price;
} Item;

static void update_total()
{
    char buf[50];
    sprintf(buf, "Total: ₹%d", total);
    gtk_label_set_text(GTK_LABEL(totallabel), buf);
}

static void Total(GtkWidget *btn, gpointer user_data)
{
    Item *item = (Item *)user_data;

    int found = 0;
    CartItem *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, item->name) == 0)
        {
            temp->quantity++;
            char text[100];
            sprintf(text, "%s × %d (₹%d)", temp->name, temp->quantity, temp->price * temp->quantity);
            gtk_label_set_text(GTK_LABEL(temp->label), text);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found)
    {
        char text[100];
        sprintf(text, "%s × %d (₹%d)", item->name, 1, item->price);
        GtkWidget *label = gtk_label_new(text);
        GtkWidget *newlabel = push(item->name, item->price, label);
        gtk_box_append(GTK_BOX(cart_item_box), newlabel);
    }
    total += item->price;
    update_total();
};
static void fcheckout(GtkWidget *btn, gpointer user_data)
{
    if (!head)
        return;

    // Create independent order copy
    CartItem *orderCopy = clone_cart();

    // Push order into queue
    enqueue(orderCopy);

    // Clear UI cart safely
    free_list();
    total = 0;
    update_total();

    // Clear cart panel widgets
    GtkWidget *box = GTK_WIDGET(user_data);
    GtkWidget *child = gtk_widget_get_first_child(box);
    while (child)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(box), child);
        child = next;
    }
}

static void clear_list(GtkWidget *btn, gpointer user_data)
{
    total = 0;
    GtkWidget *box = GTK_WIDGET(user_data);
    GtkWidget *child = gtk_widget_get_first_child(box);

    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(box), child);
        child = next;
    }
    update_total();

    free_list();
}
static GtkWidget *Items(Item *item)
{
    // Main vertical box for the item
    GtkWidget *itembox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8); // 8 px spacing
    gtk_widget_set_size_request(itembox, 300, 400);

    // Item name label
    // Price label
    char priceText[20];
    sprintf(priceText, "%s:  ₹%d", item->name, item->price);
    GtkWidget *iNamep = gtk_label_new(priceText);
    gtk_widget_set_halign(iNamep, GTK_ALIGN_CENTER);

    // Add-to-cart button
    GtkWidget *Adcbtn = gtk_button_new_with_label("ADD TO CART");
    gtk_widget_set_halign(Adcbtn, GTK_ALIGN_CENTER);

    // btn signal
    g_signal_connect(Adcbtn, "clicked", G_CALLBACK(Total), item);

    // Pack into box
    gtk_box_append(GTK_BOX(itembox), iNamep);
    gtk_box_append(GTK_BOX(itembox), Adcbtn);

    // css
    gtk_widget_add_css_class(itembox, "itembox");
    gtk_widget_add_css_class(iNamep, "item-name");
    gtk_widget_add_css_class(Adcbtn, "add-btn");

    return itembox;
}

GtkWidget *menu_page()
{
    GtkWidget *box; // Main vertical box
    GtkWidget *Menu_box;
    GtkWidget *scroll;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Create a Scrollable window
    scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_hexpand(scroll, TRUE);

    // create a menu box (this will be the scrolled child)
    Menu_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(Menu_box, -1, 800);
    gtk_widget_set_halign(Menu_box, GTK_ALIGN_FILL);
    gtk_widget_set_valign(Menu_box, GTK_ALIGN_START);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), Menu_box);

    /* create a priceBar */
    GtkWidget *priceBar;
    priceBar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(priceBar, 320, 800);
    gtk_widget_set_halign(priceBar, GTK_ALIGN_END);
    gtk_widget_set_valign(priceBar, GTK_ALIGN_START);
    gtk_widget_add_css_class(priceBar, "priceBar");

    // Now create a horizontal content box to hold scroll
    GtkWidget *content_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_hexpand(content_hbox, TRUE);
    gtk_widget_set_vexpand(content_hbox, TRUE);
    gtk_box_append(GTK_BOX(content_hbox), scroll);
    gtk_box_append(GTK_BOX(content_hbox), priceBar);
    gtk_box_append(GTK_BOX(box), content_hbox);

    /*crating labels for price bar*/
    GtkWidget *price_label = gtk_label_new("YOUR BILL:");
    totallabel = gtk_label_new("Total:");
    cart_item_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *checkout = gtk_button_new_with_label("CHECKOUT");
    GtkWidget *clear = gtk_button_new_with_label("Clear");
    gtk_widget_set_halign(price_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(price_label, GTK_ALIGN_START);
    gtk_widget_set_halign(totallabel, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(totallabel, GTK_ALIGN_END);
    gtk_box_append(GTK_BOX(priceBar), checkout);
    gtk_box_append(GTK_BOX(priceBar), clear);
    gtk_box_append(GTK_BOX(priceBar), price_label);
    gtk_box_append(GTK_BOX(priceBar), totallabel);
    gtk_box_append(GTK_BOX(priceBar), cart_item_box);

    /*checkout btn signal*/
    g_signal_connect(checkout, "clicked", G_CALLBACK(fcheckout), cart_item_box);
    g_signal_connect(clear, "clicked", G_CALLBACK(clear_list), cart_item_box);

    // create a grid box inside Menu_box
    GtkWidget *grid = gtk_grid_new();
    gtk_box_append(GTK_BOX(Menu_box), grid);

    // Add menu items
    static Item items[] = {
        {"Burger", 50}, {"Pizza", 60}, {"Misti Doi", 40}, {"Rosgulla", 30}, {"Butter Chicken", 120}, {"Chiken Roll", 90}, {"Fried Rice", 70}, {"Noodles", 60}, {"Pasta", 80}, {"Coke", 20}, {"Pepsi", 20}, {"Sprite", 20}, {"Fanta", 20}};

    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);
    int col = 0, row = 0;
    for (int i = 0; i < sizeof(items) / sizeof(Item); i++)
    {
        GtkWidget *itemBox = Items(&items[i]);
        gtk_grid_attach(GTK_GRID(grid), itemBox, col, row, 1, 1);
        col++;
        if (col > 4)
        {
            col = 0;
            row++;
        }
    }

    // Apply CSS classes
    gtk_widget_add_css_class(box, "box");
    gtk_widget_add_css_class(Menu_box, "Menu_box");
    gtk_widget_add_css_class(price_label, "price_label");
    gtk_widget_add_css_class(totallabel, "total_label");
    gtk_widget_add_css_class(checkout, "checkout");
    gtk_widget_add_css_class(clear, "clear");

    return box;
}

#endif