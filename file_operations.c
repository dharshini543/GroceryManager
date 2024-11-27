#include"file_operations.h"
#include<stdio.h>
#include"inventory.h"
#include<stdlib.h>

void saveInventoryToFile(const Inventory *inventory, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error: Unable to open file for saving.\n");
        return;
    }

    InventoryItem *current = inventory->head;

    while (current != NULL)
    {
        fwrite(current, sizeof(InventoryItem) - sizeof(InventoryItem*), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Inventory saved to file successfully.\n");
}

void loadInventoryFromFile(Inventory *inventory, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error: Unable to open file for loading.\n");
        return;
    }

    InventoryItem *prev = NULL;
    inventory->head = NULL;
    inventory->itemCount = 0;

    while (1) {
        InventoryItem *newitem = (InventoryItem *)malloc(sizeof(InventoryItem));
        if (newitem == NULL)
        {
            printf("Memory allocation failed.\n");
            break;
        }
        if (fread(newitem, sizeof(InventoryItem) - sizeof(InventoryItem*), 1, file) != 1)
        {
            free(newitem);
            break;
        }
        newitem->next = NULL;

        if (inventory->head == NULL)
        {
            inventory->head = newitem;
        }
        else
        {
            prev->next = newitem;
        }

        prev = newitem;
        inventory->itemCount++;
    }

    fclose(file);
    printf("Inventory loaded from file successfully.\n");
}

void clearInventory(Inventory *inventory)
{
    InventoryItem *current = inventory->head;
    while (current != NULL)
    {
        InventoryItem *temp = current;
        current = current->next;
        free(temp);
    }
    inventory->head = NULL;
    inventory->itemCount = 0;
}

