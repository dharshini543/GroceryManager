#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include"enum.h"

int saveInventoryToFile(const Inventory *inventory, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Could not open file %s for writing.\n", filename);
        return Failure;
    }

    InventoryItem *temp = inventory->head;
    while (temp != NULL)
    {
        fprintf(file, "%d|%s|%s|%.2f|%.2f|%s|%s\n",
                temp->itemID, temp->name, temp->brand, temp->price,
                temp->quantity, temp->department, temp->expiryDate);
        temp = temp->next;
    }

    fclose(file);
    printf("Inventory successfully saved to %s.\n", filename);
    return Success;
}

int loadInventoryFromFile(Inventory *inventory, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s for reading.\n", filename);
        return Failure;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        InventoryItem *newitem = (InventoryItem *)malloc(sizeof(InventoryItem));
        if (newitem == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return Failure;
        }

        sscanf(line, "%d|%[^|]|%[^|]|%f|%f|%[^|]|%s",
               &newitem->itemID, newitem->name, newitem->brand,
               &newitem->price, &newitem->quantity,
               newitem->department, newitem->expiryDate);

        newitem->next = NULL;

        if (inventory->head == NULL)
        {
            inventory->head = newitem;
        }
        else
        {
            InventoryItem *temp = inventory->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newitem;
        }

        inventory->itemCount++;
    }

    fclose(file);
    printf("Inventory successfully loaded from %s.\n", filename);
    return Success;
}

int saveReportToFile(const Report *report, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Could not open file %s for writing.\n", filename);
        return Failure;
    }

    ReportItem *temp = report->head;
    while (temp != NULL)
    {
        fprintf(file, "%d|%.2f\n", temp->itemID, temp->quantity);
        temp = temp->next;
    }

    fclose(file);
    printf("Report successfully saved to %s.\n", filename);
    return Success;
}

int loadReportFromFile(Report *report, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s for reading.\n", filename);
        return Failure;
    }

    char line[128];
    while (fgets(line, sizeof(line), file))
    {
        ReportItem *newitem = (ReportItem *)malloc(sizeof(ReportItem));
        if (newitem == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return Failure;
        }

        sscanf(line, "%d|%f", &newitem->itemID, &newitem->quantity);

        newitem->next = NULL;

        if (report->head == NULL)
        {
            report->head = newitem;
        }
        else
        {
            ReportItem *temp = report->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newitem;
        }
    }

    fclose(file);
    printf("Report successfully loaded from %s.\n", filename);
    return Success;
}



