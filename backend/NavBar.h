#ifndef NAVBAR_H
#define NAVBAR_H

static void show_order(GtkWidget *btn, gpointer user_data)
{
    GtkWidget *stack = GTK_WIDGET(user_data);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "order");
};
static void show_menu(GtkWidget *btn, gpointer user_data)
{
    GtkWidget *stack = GTK_WIDGET(user_data);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "menu");
};
static void show_history(GtkWidget *btn, gpointer user_data)
{
    GtkWidget *stack = GTK_WIDGET(user_data);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "history");
}

GtkWidget *show_navbar(GtkWidget *stack, GtkWidget *Menu_page, GtkWidget *Order_page, GtkWidget *History_page)
{
    GtkWidget *navbar; // Top navbar
    GtkWidget *Order_btn;
    GtkWidget *History_btn;
    GtkWidget *Menu_btn;
    GtkWidget *btn_box; // Box to align button to the right
    GtkWidget *label;

    // stacking

    gtk_stack_add_named(GTK_STACK(stack), Menu_page, "menu");
    gtk_stack_add_named(GTK_STACK(stack), Order_page, "order");
    gtk_stack_add_named(GTK_STACK(stack), History_page, "history");

    /*Navbar*/
    navbar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_size_request(navbar, -1, 150); // Height only
    gtk_widget_set_halign(navbar, GTK_ALIGN_FILL);
    gtk_widget_set_valign(navbar, GTK_ALIGN_START);
    // Create navbar label
    label = gtk_label_new("Food Camp Menu");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(navbar), label);
    // Create navbar buttons
    Order_btn = gtk_button_new_with_label("ORDERS");
    History_btn = gtk_button_new_with_label("HISTORY");
    Menu_btn = gtk_button_new_with_label("MENU");
    // Wrap buttons in a horizontal box for alignment
    btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(btn_box, GTK_ALIGN_START);
    gtk_widget_set_margin_end(GTK_WIDGET(Order_btn), 5);
    gtk_box_append(GTK_BOX(btn_box), Menu_btn);
    gtk_box_append(GTK_BOX(btn_box), Order_btn);
    gtk_box_append(GTK_BOX(btn_box), History_btn);
    gtk_box_append(GTK_BOX(navbar), btn_box);

    g_signal_connect(Order_btn, "clicked", G_CALLBACK(show_order), stack);
    g_signal_connect(History_btn, "clicked", G_CALLBACK(show_history), stack);
    g_signal_connect(Menu_btn, "clicked", G_CALLBACK(show_menu), stack);

    gtk_widget_add_css_class(navbar, "navbar");
    gtk_widget_add_css_class(label, "navbar-label");
    gtk_widget_add_css_class(Order_btn, "Obtn");
    gtk_widget_add_css_class(History_btn, "Hbtn");
    gtk_widget_add_css_class(Menu_btn, "Mbtn");

    return navbar;
}

#endif