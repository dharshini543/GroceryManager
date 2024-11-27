#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"inventory.h"

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
            return 0;
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
    return 1;
}

int deleteItemFromInventory(Inventory *inventory, int itemID)
{

    InventoryItem *current = inventory->head;
    InventoryItem *prev = NULL;

    if (current == NULL)
    {
        printf("Inventory is Empty\n");
        return 0;
    }
    if(inventory->head->itemID == itemID)
    {
        InventoryItem *temp = inventory->head;
        temp = inventory->head->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", inventory->head->itemID, inventory->head->name, inventory->head->brand, inventory->head->price, inventory->head->quantity, inventory->head->department, inventory->head->expiryDate);

        free(inventory->head);
        inventory->head = temp;
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
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", current->itemID, current->name, current->brand, current->price, current->quantity, current->department, current->expiryDate);
        free(current);
        return 1;
    }

}

int updateItemDetails(Inventory *inventory, int itemID)
{
    InventoryItem*temp = inventory->head;
    if(temp == 0)
    {
        printf("No Item in inventory. Please add.\n");
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

    return 1;
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
void sortInventorybyName(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return;
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
    printf("Inventory sorted by item name.\n");
}

void sortInventorybyDepartment(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->department, j->department) > 0) {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    printf("Inventory sorted by item Department.\n");
}

void sortInventorybyPrice(Inventory *inventory)
{
    if (inventory->head == NULL || inventory->head->next == NULL)
    {
        return;
    }

    InventoryItem *i, *j;
    for (i = inventory->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if ((i->price > j->price)) {
                InventoryItem temp = *i;
                *i = *j;
                *j = temp;

                InventoryItem *tempNext = i->next;
                i->next = j->next;
                j->next = tempNext;
            }
        }
    }
    printf("Inventory sorted by item Price.\n");
}

InventoryItem* getInventoryItemByID(Inventory*inventory,int itemID)
{
    InventoryItem *temp1 = inventory->head;
    while(temp1 != NULL && temp1->itemID != itemID)
    {
        temp1 = temp1->next;
    }

    printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", temp1->itemID, temp1->name, temp1->brand, temp1->price, temp1->quantity, temp1->department, temp1->expiryDate);
    return temp1;
}
