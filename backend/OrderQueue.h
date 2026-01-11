#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H
#include "../backend/OrderType.h"
#include "../backend/OrderHistory.h"
#include "../backend/CartitemLL.h"
#include <stdio.h>
#include <stdlib.h>

struct OrderNode
{
    struct Order data;
    struct OrderNode *next;
};

static struct OrderNode *O_front = NULL, *O_rear = NULL;
static int ORDER_SEQ = 1000;

static void calculateTotals(struct Order *ord)
{
    ord->totalItems = 0;
    ord->totalAmount = 0;
    for (CartItem *t = ord->items; t; t = t->next)
    {
        ord->totalItems += t->quantity;
        ord->totalAmount += t->quantity * t->price;
    }
}

static void enqueue(CartItem *orderCart)
{
    if (!orderCart)
        return;

    struct OrderNode *n = malloc(sizeof(struct OrderNode));
    n->data.orderId = ORDER_SEQ++;
    n->data.items = orderCart;
    calculateTotals(&n->data);
    n->next = NULL;

    if (!O_rear)
        O_front = O_rear = n;
    else
    {
        O_rear->next = n;
        O_rear = n;
    }
}

static void free_item_list(CartItem *h)
{
    while (h)
    {
        CartItem *n = h->next;
        free(h->name);
        free(h);
        h = n;
    }
}

static void dequeue()
{
    if (!O_front)
        return;

    struct OrderNode *t = O_front;
    O_front = O_front->next;
    if (!O_front)
        O_rear = NULL;

    add_to_history(&t->data); // move to history
    free(t);                  // DO NOT free items anymore
}

#endif
