#include<stdio.h>
#include<stdlib.h>
#include"inventory.h"
#include"cart.h"
#include"report.h"

void add_sales_report_item(Cart *cart, Inventory *inventory, Report *report)
{
    CartItem *current = cart->head;
    ReportItem *temp = report->head;
    int count = 0;
    while(current != 0)
    {
        InventoryItem *temp1 = inventory->head;
        while(temp1 != NULL && temp1->itemID != current->itemID)
        {
            temp1 = temp1->next;
        }
        InventoryItem *Item = temp1;
        if(Item != NULL )
        {
            int check = is_ItemId_Already_present_in_Sales_Report(report, Item->itemID);
            if(check == 0)
            {
                ReportItem *newitem = (ReportItem*)malloc(sizeof(ReportItem));
                if (newitem == 0)
                {
                    printf("Memory allocation failed.\n");
                    return;
                }
                newitem->itemID = Item->itemID;
                newitem->quantity = current->quantity;
                newitem->next = 0;
                if(report->head == 0)
                {
                    report->head = newitem;
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
            }
            else
            {
                temp->quantity = temp->quantity + current->quantity;
            }
            current = current->next;
        }
    }
}

int is_ItemId_Already_present_in_Sales_Report(Report *report, int ItemID)
{
    int ID = ItemID;
    int isPresent = 0;
    ReportItem * temp = report->head;
    while(temp != 0)
    {
        if(temp->itemID == ID)
        {
            isPresent = 1;
        }
        else
        {
            isPresent = 0;
        }
        temp = temp->next;
    }
    return isPresent;
}

void generateSalesReport(Cart *cart, Inventory *inventory, float totalsales, Report *report)
{
    ReportItem *temp = report->head;
    CartItem *current = cart->head;
    int count = 0;
    float FinalAmount = 0;

    printf("-----------------------Sales Report---------------------------\n");
    printf("Item_No\tItemID\tName\t\tPrice\t\tQuantity\tAmount\n");
    while(temp != 0)
    {
        InventoryItem *temp1 = inventory->head;
        while(temp1 != NULL && temp1->itemID != temp->itemID)
        {
            temp1 = temp1->next;
        }
        InventoryItem *Item = temp1;
        if(Item != NULL)
        {
            printf("%d\t%d\t%s\t\t%.2f\t\t%.2f\t\t%.2f\n",++count, Item->itemID, Item->name, Item->price, temp->quantity, Item->price * temp->quantity);
        }
        temp = temp->next;
    }
    printf("---------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTotal Sales = %.2f\n",totalsales);
}

void generateInventoryReport(const Inventory *inventory)
{

    InventoryItem*temp = inventory->head;
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        printf("-----------------Inventory Report--------------------\n");
        printf("ID\tName\t\tBrand\t\tPrice\t\tQuantity\tDepartment\t\tExpiry Date\n");
        while(temp != 0)
        {
            printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);
            temp = temp->next;
        }
    }
}

void viewLowStockAlerts(const Inventory *inventory)
{
    InventoryItem*current = inventory->head;
    int isFirstLowStock = 1;
    while(current != 0)
    {
        if(current->quantity < 5)
        {
            if(isFirstLowStock)
            {
                printf("----------------Low stock Alert!----------------\n");
                printf("ItemID\t\tName\t\tQuantity\n");
                isFirstLowStock = 0;
            }
            printf("%d\t\t%s\t\t%.2f\n", current->itemID, current->name, current->quantity);
        }
        current = current->next;
    }
}

