#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"cart.h"

int addItemToCart(Cart *cart, Inventory *inventory, int itemID, float quantity)
{
    InventoryItem*temp =inventory->head;
    CartItem*temp1 = cart->head;
    if(temp == 0)
    {
        printf("Inventory is Empty\n");
        return 0;
    }
    while(temp != NULL && temp->itemID != itemID )
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("Item not found in Inventory\n");
        return 0;
    }
    if(temp->quantity < quantity)
    {
        printf("Not enough stock available\n");
        return 0;
    }
    CartItem *newitem = (CartItem*)malloc(sizeof(CartItem));
    if (newitem == 0)
    {
        printf("Memory allocation failed.\n");
        return 0;
    }
    newitem->itemID = itemID;
    newitem->quantity = quantity;
    newitem->next = 0;
    if(cart->head == 0)
    {
        cart->head = newitem;
        temp1 = newitem;
    }
    else
    {
        while(temp1->next != 0)
        {
            temp1 = temp1->next;
        }
        temp1->next = newitem;
        temp1 = newitem;
    }
    printf("ItemID:%d,Quantity:%.2f\n",newitem->itemID,newitem->quantity);
    cart->totalAmount = cart->totalAmount +(temp->price * quantity);
    return 1;

}
int removeItemFromCart(Inventory *inventory,Cart *cart, int itemID)
{
    CartItem *current = cart->head;
    CartItem *prev = NULL;
    InventoryItem*temp1 = inventory->head;

    if (current == NULL)
    {
        printf("Cart is Empty\n");
        return 0;
    }
    if(cart->head->itemID == itemID)
    {
        CartItem *temp = cart->head;
        temp = cart->head->next;
        printf("%d\t%.2f\n", cart->head->itemID,cart->head->quantity);

        while(temp1->itemID != itemID)
        {
            temp1 = temp1->next;
        }
        cart->totalAmount = cart->totalAmount -(temp1->price * cart->head->quantity);
        printf("Payable Amount =Rs:%.2f\n",cart->totalAmount);
        free(cart->head);
        cart->head = temp;
        return 1;
    }
    else
    {
        while(current->itemID != itemID)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        printf("%d\t%.2f\n", current->itemID,current->quantity);

        while(temp1->itemID != itemID)
        {
            temp1 = temp1->next;
        }
        cart->totalAmount = cart->totalAmount -(temp1->price * current->quantity);
        printf("Payable Amount =Rs:%.2f\n",cart->totalAmount);
        free(current);
        return 1;
    }
}

int updateCartItemQuantity(Inventory*inventory, Cart *cart, int itemID, int quantity)
{
    CartItem* temp = cart->head;
    InventoryItem* temp1 = inventory->head;
    if(temp == 0)
    {
        printf("No Item in Cart. Please add.\n");
        return 0;
    }
    while(temp != 0 && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if(temp == 0)
    {
        printf("Item not found with the given item Id.\n");
        return 0;
    }
    temp->quantity =quantity;
    cart->totalAmount = cart->totalAmount + ( temp1->price * quantity );

    return 1;
}

void viewCartSummary(Cart *cart)
{
    CartItem*temp =cart->head;
    printf("ItemID\tQuantity\n");
    while(temp != 0)
    {
        printf("%d\t%.2f\n", temp->itemID, temp->quantity);
        temp = temp->next;
    }
    printf("Total Amount =Rs:%.2f\n", cart->totalAmount);

}

