#include <stdio.h>
#include "user.h"
#include "inventory.h"
#include "cart.h"
#include "billing.h"
#include "report.h"
#include"file_operations.h"
#include "enum.h"

int start()
{
    int choice = 0, option = 0;
    User user = {0};
    Inventory inventory = {0};
    Cart cart = {0};
    Report report = {0};
    float totalsales = 0;
    int isTrue = 1;

    loadInventoryFromFile(&inventory, "inventory.txt");
    loadReportFromFile(&report, "sales_report.txt");

    initializeUser(&user,"Dharshini","1234");
    printf("Enter 1.Login Credentials\n");
    while(!user.isLoggedIn)
    {
        displayLoginScreen(&user);
    }

    while(isTrue)
    {
        printf("Enter\n1.Inventory Management\n2.Cart Management\n3.Billing\n4.Report\n5.Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case INVENTORY_MANAGEMENT:
            printf("Enter\n1.Add Item to Inventory\n2.Delete Item from Inventory\n3.Update Inventory Item Details\n4.Display Inventory summary\n5.Sort Inventory By Name\n6.Sort Inventory By Department\n7.Sort Inventory By Price\n8.Get list by ID\n9.Save to file\n");
            scanf("%d", &option);

            switch(option)
            {
                int ID = 0;
                int success = 0;

            case Inventory_AddItem:
                success = addItemToInventory(&inventory);
                if(success)
                {
                    printf("Items Added succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to add Item to the Inventory");
                }
                break;

            case Inventory_DeleteItem:
                printf("Enter ID to delete Item\n");
                scanf("%d", &ID);
                success = deleteItemFromInventory(&inventory, ID);
                if(success)
                {
                    printf("Item deleted succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to delete Item to the Inventory");
                }
                break;

            case Inventory_UpdateItem:
                printf("Enter ID to update Item details\n");
                scanf("%d", &ID);
                success = updateItemDetails(&inventory, ID);
                if(success)
                {
                    printf("Item updated succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to update Item to the Inventory");
                }
                break;

            case Inventory_DisplaySummary:
                viewInventorySummary(&inventory);
                break;

            case Inventory_SortByName:
                success = sortInventorybyName(&inventory);
                if(success)
                {
                    printf("Inventory sorted by item name.\n");
                }
                else
                {
                    printf("Failed to sort Inventory by name\n");
                }
                break;

            case Inventory_SortByDepartment:
                success = sortInventorybyDepartment(&inventory);
                if(success)
                {
                    printf("Inventory sorted by item Department.\n");
                }
                else
                {
                    printf("Failed to sort Inventory by Department\n");
                }
                break;

            case Inventory_SortByPrice:
                success = sortInventorybyPrice(&inventory);
                if(success)
                {
                    printf("Inventory sorted by item Price.\n");
                }
                else
                {
                    printf("Failed to sort inventory by Price.\n");
                }
                break;

            case Inventory_GetItemByID:

                printf("Enter ID of an item\n");
                scanf("%d", &ID);
                success = getInventoryItemByID(&inventory, ID);
                if(success)
                {
                    printf("Got item Successfully\n");
                }
                else
                {
                    printf("Failed to get item\n");
                }
                break;

            case Inventory_SaveToFile:
                saveInventoryToFile(&inventory, "inventory.txt");
                break;


            default:
                printf("Enter valid option\n");
            }
            break;

        case  CART_MANAGEMENT:
            printf("Enter\n1.Add Item to Cart\n2.Delete Item from Cart\n3.Update Cart item quantity\n4.Display Cart Summary\n");
            scanf("%d", &option);


            switch(option)
            {
                int ID;
                float quantity = 0;
                int success = 0;

            case Cart_AddItem:
                printf("Enter ID of Inventory Item to add\n");
                scanf("%d", &ID);
                printf("Enter Quantity\n");
                scanf("%f", &quantity);
                success = addItemToCart(&cart, &inventory, ID, quantity);
                if(success)
                {
                    printf("Item Added succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to add Item to the cart");
                }
                break;

            case Cart_DeleteItem:
                printf("Enter ID to remove item from cart\n");
                scanf("%d", &ID);
                success = removeItemFromCart(&inventory, &cart, ID);
                if(success)
                {
                    printf("Item deleted succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to delete Item to the cart");
                }
                break;

            case Cart_UpdateQuantity:
                printf("Enter ID to update quantity\n");
                scanf("%d", &ID);
                printf("Enter Quantity\n");
                scanf("%f", &quantity);
                success = updateCartItemQuantity(&inventory, &cart, ID, quantity);
                if(success)
                {
                    printf("Item updated succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to update Item to the cart");
                }
                break;

            case Cart_DisplaySummary:
                viewCartSummary(&cart);
                break;

            default:
                printf("Enter valid option\n");
            }
            break;

        case BILLING:
            if(cart.head == 0)
            {
                printf("No Items in cart,Please add...\n");
            }
            else
            {
            printf("Enter\n1.Calculate Final Bill\n2.Generate Receipt\n");
            scanf("%d", &option);

            switch(option)
            {
                float DiscountAmount = 0;

            case Calculate_FinalBill:
                DiscountAmount = calculateFinalBill(&cart, &inventory, &totalsales);
                break;

            case Billing_GenerateReceipt:
                generateReceipt(&cart, &inventory,DiscountAmount,&report);
                break;

            default:
                printf("Enter valid option\n");
            }
            break;
            }
            break;

        case REPORT:
            printf("Enter\n1.Generate Sales Report\n2.Generate Inventory Report\n3.View Low Stock alerts\n4.Save Report to file\n");
            scanf("%d", &option);

            switch(option)
            {
            case Generate_SalesReport:
                generateSalesReport(&cart, &inventory, totalsales,&report);
                cart.head = 0;
                break;

            case Generate_InventoryReport:
                generateInventoryReport(&inventory);
                break;

            case ViewLOWStockAlerts:
                viewLowStockAlerts(&inventory);
                break;

            case SaveToFile:
                saveReportToFile(&report, "sales_report.txt");
                break;

            default:
                printf("Enter valid option\n");
            }
            break;

        case EXIT:
            saveInventoryToFile(&inventory, "inventory.txt");
            saveReportToFile(&report, "sales_report.txt");
            printf("Exiting program...\n");
            isTrue = 0;
            break;

        default:
            printf("Enter valid choice\n");
        }
    }
    return 0;
}
