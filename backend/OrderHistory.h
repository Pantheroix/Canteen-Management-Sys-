#ifndef ORDERHISTORY_H
#define ORDERHISTORY_H
#include "../backend/CartitemLL.h"
#include "../backend/OrderType.h"
#include <stdlib.h>

struct HistoryNode
{
    int orderId;
    int totalItems;
    float totalAmount;
    CartItem *items;
    struct HistoryNode *next;
};

static struct HistoryNode *H_front = NULL, *H_rear = NULL;

static void add_to_history(struct Order *ord)
{
    struct HistoryNode *n = malloc(sizeof(struct HistoryNode));
    n->orderId = ord->orderId;
    n->totalItems = ord->totalItems;
    n->totalAmount = ord->totalAmount;
    n->items = ord->items; // take ownership
    n->next = NULL;

    if (!H_rear)
        H_front = H_rear = n;
    else
    {
        H_rear->next = n;
        H_rear = n;
    }
}
#endif
