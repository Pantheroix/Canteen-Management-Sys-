#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

GtkWidget *history_page()
{
    GtkWidget *box;
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *label = gtk_label_new("History page");
    gtk_box_append(GTK_BOX(box), label);

    return box;
}

#endif