#ifndef ORDERTYPE_H
#define ORDERTYPE_H

struct Order
{
    int orderId;
    int totalItems;
    float totalAmount;
    CartItem *items;
};

#endif