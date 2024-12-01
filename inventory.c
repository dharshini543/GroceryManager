#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "enum.h"

int addItemToInventory(Inventory *inventory)
{
    int choice = 1;
    InventoryItem *temp = inventory->head;

    while(choice)
    {
        InventoryItem *newitem = (InventoryItem*)malloc(sizeof(InventoryItem));
        if (newitem == 0)
        {
            printf("Memory allocation failed.\n");
            return Failure;
        }
        newitem->itemID = inventory->itemCount+1;
        printf("Item name:");
        scanf(" %[^\n]", newitem->name);
        printf("Item Brand:");
        scanf(" %[^\n]",newitem->brand);
        printf("Item price:");
        scanf("%f",&newitem->price);
        printf("Item Quantity:");
        scanf("%f", &newitem->quantity);
        printf("Item Department:");
        scanf(" %[^\n]",newitem->department);
        printf("Item ExpiryDate:");
        scanf("%s",newitem->expiryDate);
        newitem->next = 0;

        if(inventory->head == 0)
        {
            inventory->head = newitem;
            temp = newitem;
        }
        else
        {
            while(temp->next != 0)
            {
                temp = temp->next;
            }
            temp->next = newitem;
            temp = newitem;
        }
        inventory->itemCount++;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", newitem->itemID, newitem->name, newitem->brand, newitem->price, newitem->quantity, newitem->department, newitem->expiryDate);
        printf("Item Added\n");
        printf("Want to continue...press 1\n");
        scanf("%d",&choice);
    }
    return Success;
}

int deleteItemFromInventory(Inventory *inventory, int itemID)
{

    InventoryItem *current = inventory->head;
    InventoryItem *prev = NULL;

    if (current == NULL)
    {
        printf("Inventory is Empty\n");
        return Failure;
    }
    if(inventory->head->itemID == itemID)
    {
        InventoryItem *temp = inventory->head->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", inventory->head->itemID, inventory->head->name, inventory->head->brand, inventory->head->price, inventory->head->quantity, inventory->head->department, inventory->head->expiryDate);

        free(inventory->head);
        inventory->head = temp;
        return Success;
    }
    else
    {
        while(current->itemID != itemID)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", current->itemID, current->name, current->brand, current->price, current->quantity, current->department, current->expiryDate);
        free(current);
        return Success;
    }

}

int updateItemDetails(Inventory *inventory, int itemID)
{
    InventoryItem *temp = inventory->head;
    if(temp == 0)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }
    while(temp != 0 && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if(temp == 0)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }

    printf("Enter new details for the item\n");
    printf("Item name:");
    scanf(" %[^\n]",temp->name);
    printf("Item Brand:");
    scanf(" %[^\n]",temp->brand);
    printf("Item price:");
    scanf("%f",&temp->price);
    printf("Item Quantity:");
    scanf("%f",&temp->quantity);
    printf("Item Department:");
    scanf(" %[^\n]",temp->department);
    printf("Item ExpiryDate:");
    scanf("%s",temp->expiryDate);

    return Success;
}

void viewInventorySummary(const Inventory *inventory)
{
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        InventoryItem* temp = inventory->head;
        printf("Inventory Summary:\n");
        printf("ID\t\tName\t\t\tBrand\t\t\tPrice\t\t\tQuantity\t\t\tDepartment\t\tExpiry Date\n");
        while(temp != 0)
        {
            printf("%d\t\t%s\t\t\t%s\t\t\t%.2f\t\t\t%.2f\t\t\t%s\t\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);
            temp = temp->next;
        }
    }
}

int sortInventorybyName(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->name, j->name) > 0)
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int sortInventorybyDepartment(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->department, j->department) > 0)
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int sortInventorybyPrice(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return Failure;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if ((i->price > j->price))
            {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    return Success;
}

int getInventoryItemByID(Inventory*inventory,int itemID)
{
    InventoryItem *temp = inventory->head;
    if(temp == 0)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }
    while(temp != 0 && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if(temp == 0)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }
    printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);

    return Success;
}
