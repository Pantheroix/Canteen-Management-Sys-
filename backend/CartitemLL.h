#ifndef CARTITEMLL_H
#define CARTITEMLL_H
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

typedef struct CartItem
{
    char *name;
    int price;
    int quantity;
    GtkWidget *label;
    struct CartItem *next;
} CartItem;

extern CartItem *head;

/* push item to cart */
static inline GtkWidget *push(const char *Itemname, int Itemprice, GtkWidget *Itemlabel)
{
    CartItem *n = malloc(sizeof(CartItem));
    n->name = strdup(Itemname);
    n->price = Itemprice;
    n->quantity = 1;
    n->label = Itemlabel;
    n->next = head;
    head = n;
    return Itemlabel;
}

/* clone cart for order queue */
static inline CartItem *clone_cart()
{
    CartItem *newHead = NULL, *tail = NULL;
    for (CartItem *t = head; t; t = t->next)
    {
        CartItem *n = malloc(sizeof(CartItem));
        n->name = strdup(t->name);
        n->price = t->price;
        n->quantity = t->quantity;
        n->label = NULL;
        n->next = NULL;
        if (!newHead)
            newHead = tail = n;
        else
        {
            tail->next = n;
            tail = n;
        }
    }
    return newHead;
}

/* free UI cart */
static inline void free_list()
{
    CartItem *t = head;
    while (t)
    {
        CartItem *n = t->next;
        free(t->name);
        free(t);
        t = n;
    }
    head = NULL;
}

#endif
