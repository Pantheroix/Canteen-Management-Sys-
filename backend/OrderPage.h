#ifndef ORDERPAGE_H
#define ORDERPAGE_H

GtkWidget *order_page()
{
    GtkWidget *box;
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *label = gtk_label_new("Order page");
    gtk_box_append(GTK_BOX(box), label);
    return box;
}

#endif