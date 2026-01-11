#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H
#include "../backend/OrderHistory.h"
#include <gtk/gtk.h>

static GtkWidget *history_container;

/* Reload served orders */
static void refresh_history(GtkWidget *btn, gpointer data)
{
    GtkWidget *child = gtk_widget_get_first_child(history_container);
    while (child)
    {
        GtkWidget *next = gtk_widget_get_next_sibling(child);
        gtk_box_remove(GTK_BOX(history_container), child);
        child = next;
    }

    if (!H_front)
    {
        GtkWidget *l = gtk_label_new("No Served Orders Yet");
        gtk_widget_set_halign(l, GTK_ALIGN_START);
        gtk_box_append(GTK_BOX(history_container), l);
        return;
    }

    for (struct HistoryNode *h = H_front; h; h = h->next)
    {
        GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
        gtk_widget_add_css_class(card, "history-card");
        gtk_widget_set_halign(card, GTK_ALIGN_START);

        char buf[64];
        sprintf(buf, "Order #%d", h->orderId);
        GtkWidget *id = gtk_label_new(buf);
        gtk_widget_set_halign(id, GTK_ALIGN_START);
        gtk_widget_add_css_class(id, "history-id");
        gtk_box_append(GTK_BOX(card), id);

        for (CartItem *i = h->items; i; i = i->next)
        {
            char line[128];
            sprintf(line, "• %s × %d", i->name, i->quantity);
            GtkWidget *item = gtk_label_new(line);
            gtk_widget_set_halign(item, GTK_ALIGN_START);
            gtk_box_append(GTK_BOX(card), item);
        }

        char tot[64];
        sprintf(tot, "Total ₹%.2f", h->totalAmount);
        GtkWidget *total = gtk_label_new(tot);
        gtk_widget_set_halign(total, GTK_ALIGN_START);
        gtk_box_append(GTK_BOX(card), total);

        gtk_box_append(GTK_BOX(history_container), card);
    }
}

GtkWidget *history_page()
{
    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    /* Header */
    GtkWidget *header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *title = gtk_label_new("Order History");
    gtk_widget_add_css_class(title, "page-title");
    gtk_widget_set_hexpand(title, TRUE);
    gtk_widget_set_halign(title, GTK_ALIGN_START);

    GtkWidget *refresh_btn = gtk_button_new_with_label("Refresh");
    gtk_widget_add_css_class(refresh_btn, "refresh-btn");
    g_signal_connect(refresh_btn, "clicked", G_CALLBACK(refresh_history), NULL);

    gtk_box_append(GTK_BOX(header), title);
    gtk_box_append(GTK_BOX(header), refresh_btn);
    gtk_box_append(GTK_BOX(root), header);

    /* Scroll area */
    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_box_append(GTK_BOX(root), scroll);

    history_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_halign(history_container, GTK_ALIGN_START);
    gtk_widget_set_hexpand(history_container, TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), history_container);

    refresh_history(NULL, NULL);
    return root;
}
#endif
