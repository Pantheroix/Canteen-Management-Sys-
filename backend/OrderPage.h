#ifndef ORDERPAGE_H
#define ORDERPAGE_H
#include "../backend/OrderQueue.h"
#include <gtk/gtk.h>

static GtkWidget *orders_container;

// Function to refresh the list of orders
static void refresh_orders(GtkWidget *btn, gpointer user_data)
{
    // Clear existing children from the container
    GtkWidget *child = gtk_widget_get_first_child(orders_container);
    while (child != NULL)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(orders_container), child);
        child = next;
    }

    // Check if queue is empty
    struct OrderNode *temp = O_front;
    if (temp == NULL)
    {
        GtkWidget *label = gtk_label_new("No Pending Orders");
        gtk_widget_add_css_class(label, "no-orders-label");
        gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
        gtk_box_append(GTK_BOX(orders_container), label);
        return;
    }

    // Iterate through the queue and create a card for each order
    while (temp != NULL)
    {
        // Create Order Card Box
        GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_add_css_class(card, "order-card");

        // Order ID Label
        char id_buf[30];
        sprintf(id_buf, "Order ID: %d", temp->data.orderId);
        GtkWidget *id_label = gtk_label_new(id_buf);
        gtk_widget_add_css_class(id_label, "order-id");
        gtk_widget_set_halign(id_label, GTK_ALIGN_START);
        gtk_box_append(GTK_BOX(card), id_label);

        // Items List
        CartItem *item = temp->data.items;
        while (item)
        {
            char item_buf[100];
            sprintf(item_buf, "• %s x %d", item->name, item->quantity);
            GtkWidget *item_label = gtk_label_new(item_buf);
            gtk_widget_set_halign(item_label, GTK_ALIGN_START);
            gtk_box_append(GTK_BOX(card), item_label);
            item = item->next;
        }

        // Total Amount Label
        char total_buf[50];
        sprintf(total_buf, "Total: ₹%.2f", temp->data.totalAmount);
        GtkWidget *total_label = gtk_label_new(total_buf);
        gtk_widget_add_css_class(total_label, "order-total");
        gtk_widget_set_halign(total_label, GTK_ALIGN_END);
        gtk_box_append(GTK_BOX(card), total_label);

        // Add card to the main container
        gtk_box_append(GTK_BOX(orders_container), card);

        temp = temp->next;
    }
}

// Callback to serve the next order (dequeue)
static void serve_next_order(GtkWidget *btn, gpointer user_data)
{
    if (O_front != NULL)
    {
        dequeue();                  // Removes the head of the queue
        refresh_orders(NULL, NULL); // Refresh the UI
    }
}

GtkWidget *order_page()
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 10);
    gtk_widget_set_margin_bottom(box, 10);
    gtk_widget_set_margin_start(box, 10);
    gtk_widget_set_margin_end(box, 10);

    // Header Section
    GtkWidget *header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *title = gtk_label_new("Kitchen Queue");
    gtk_widget_add_css_class(title, "page-title");
    gtk_widget_set_hexpand(title, TRUE);
    gtk_widget_set_halign(title, GTK_ALIGN_START);

    GtkWidget *refresh_btn = gtk_button_new_with_label("Refresh");
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(refresh_orders), NULL);

    GtkWidget *serve_btn = gtk_button_new_with_label("Serve Next");
    gtk_widget_add_css_class(serve_btn, "serve-btn");
    g_signal_connect(serve_btn, "clicked", G_CALLBACK(serve_next_order), NULL);

    gtk_box_append(GTK_BOX(header), title);
    gtk_box_append(GTK_BOX(header), refresh_btn);
    gtk_box_append(GTK_BOX(header), serve_btn);
    gtk_box_append(GTK_BOX(box), header);

    // Scrollable Area for Orders
    GtkWidget *scrolled = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_widget_set_hexpand(scrolled, TRUE);
    gtk_box_append(GTK_BOX(box), scrolled);

    // Container for the list of orders
    orders_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), orders_container);

    // Initial Load
    refresh_orders(NULL, NULL);

    return box;
}

#endif
