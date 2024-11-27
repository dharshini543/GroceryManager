#ifndef REPORT_H
#define REPORT_H

#include "inventory.h"
#include"cart.h"

typedef struct ReportItem
{
    int itemID;
    float quantity;
    struct ReportItem *next;
}ReportItem;

typedef struct Report
{
    ReportItem *head;
}Report;


void add_sales_report_item(Cart *cart, Inventory *inventory, Report * report);
void generateSalesReport(Cart *cart, Inventory *inventory, float totalsales, Report *report);
void generateInventoryReport(const Inventory *inventory);
void viewLowStockAlerts(const Inventory *inventory);
int is_ItemId_Already_present_in_Sales_Report(Report *report, int ItemID);

#endif // REPORT_H


