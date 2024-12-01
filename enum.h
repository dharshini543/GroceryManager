#ifndef ENUM_H
#define ENUM_H

typedef enum
{
    INVENTORY_MANAGEMENT = 1,
    CART_MANAGEMENT,
    BILLING,
    REPORT,
    EXIT
}MainMenuOptions;

typedef enum
{
    Inventory_AddItem = 1,
    Inventory_DeleteItem,
    Inventory_UpdateItem,
    Inventory_DisplaySummary,
    Inventory_SortByName,
    Inventory_SortByDepartment,
    Inventory_SortByPrice,
    Inventory_GetItemByID,
    Inventory_SaveToFile
} InventoryMenuOptions;

typedef enum
{
    Cart_AddItem = 1,
    Cart_DeleteItem,
    Cart_UpdateQuantity,
    Cart_DisplaySummary
} CartMenuOptions;

typedef enum
{
    Calculate_FinalBill = 1,
    Billing_GenerateReceipt
} BillingMenuOptions;

typedef enum
{
    Generate_SalesReport = 1,
    Generate_InventoryReport,
    ViewLOWStockAlerts,
    SaveToFile
} ReportMenuOptions;

enum
{
    Failure = 0,
    Success
};


#endif // ENUM_H
