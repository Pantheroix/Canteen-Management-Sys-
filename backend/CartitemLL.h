#ifndef CARTITEMLL_H
#define CARTITEMLL_H
typedef struct CartItem
{
    const char *name;
    int price;
    int quantity;
    GtkWidget *label;
    struct CartItem *next;
} CartItem;

extern CartItem *head;

GtkWidget *push(const char *Itemname, int Itemprice, GtkWidget *Itemlabel)
{
    CartItem *newNode = (CartItem *)malloc(sizeof(CartItem));
    newNode->name = strdup(Itemname);
    newNode->price = Itemprice;
    newNode->quantity = 1;
    newNode->next = head;
    newNode->label = Itemlabel;
    head = newNode;

    return newNode->label;
}
void free_list()
{
    CartItem *current = head;
    CartItem *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    head = NULL;
    printf("list freed\n");
}

#endif