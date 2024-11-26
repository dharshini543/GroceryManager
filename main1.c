#include <stdio.h>
#include "user.h"
#include "inventory.h"
#include "cart.h"
#include "billing.h"
#include "report.h"
#include"file_operations.h"

int start()
{
    int choice, option;
    User user;
    Inventory inventory = {0};
    Cart cart = {0};
    Report report = {0};
    CartItem Item;
    loadInventoryFromFile( &inventory, "inventory.data");
    float totalsales;


    //initializeUser(&user,"Dharshini","7259475953");
    // printf("Enter 1.Enter User Credentials\n");
    // while(!user.isLoggedIn)
    // {
    //     displayLoginScreen(&user);
    // }

    while(1)
    {
        printf("Enter\n1.Inventory Management\n2.Cart Management\n3.Billing\n4.Report\n5.Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:printf("Inventory Management:\n");
            printf("Enter\n1.Add Item to Inventory\n2.Delete Item from Inventory\n3.Update Inventory Item Details\n4.Display Inventory summary\n5.Sort Inventory\n6.Get list by ID\n");
            scanf("%d", &option);

            switch(option)
            {
                int ID;
                int ItemID;
                int num;
                int added;
                int deleted;
                int updated;
            case 1:added = addItemToInventory(&inventory);
                if(added)
                {
                    printf("Items Added succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to add Item to the Inventory");
                }
                break;
            case 2:
                printf("Enter ID to delete Item\n");
                scanf("%d", &ID);
                deleted = deleteItemFromInventory(&inventory, ID);
                if(deleted)
                {
                    printf("Item deleted succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to delete Item to the Inventory");
                }
                break;
            case 3:
                printf("Enter ID to update Item details\n");
                scanf("%d", &ItemID);
                updated = updateItemDetails(&inventory, ItemID);
                if(updated)
                {
                    printf("Item updated succesfully to the Inventory\n");
                }
                else
                {
                    printf("Failed to update Item to the Inventory");
                }

                break;
            case 4:viewInventorySummary(&inventory);
                break;
            case 5:sortInventory(&inventory);
                break;
            case 6:
                saveInventoryToFile(&inventory, "inventory.data");
                printf("Enter ID of an item\n");
                scanf("%d", &num);
                getInventoryItemByID(&inventory, num);
                break;
            default:
                printf("Enter valid option\n");
            }
            break;

        case 2:printf("Cart Management:\n");
            printf("Enter\n1.Add Item to Cart\n2.Delete Item from Cart\n3.Update Cart item quantity\n4.Display Cart Summary\n");
            scanf("%d", &option);


            switch(option)
            {
                int ID1;
                int ID2;
                int ID3;
                float quantity1;
                float quantity2;
                int added;
                int deleted;
                int updated;
            case 1:
                printf("Enter ID of Inventory Item to add\n");
                scanf("%d", &ID1);
                printf("Enter Quantity\n");
                scanf("%f", &quantity1);
                added = addItemToCart(&cart, &inventory, ID1, quantity1);
                if(added)
                {
                    printf("Item Added succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to add Item to the cart");
                }
                break;
            case 2:
                printf("Enter ID to remove item from cart\n");
                scanf("%d", &ID2);
                deleted = removeItemFromCart(&inventory, &cart, ID2);
                if(deleted)
                {
                    printf("Item deleted succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to delete Item to the cart");
                }
                break;
            case 3:printf("Enter ID to update quantity\n");
                scanf("%d", &ID3);
                printf("Enter Quantity\n");
                scanf("%f", &quantity2);
                updated = updateCartItemQuantity(&inventory, &cart, ID3, quantity2);
                if(updated)
                {
                    printf("Item updated succesfully to the cart\n");
                }
                else
                {
                    printf("Failed to update Item to the cart");
                }
                break;
            case 4:viewCartSummary(&cart);
                break;
            default:
                printf("Enter valid option\n");
            }
            break;

            case 3:printf("Billing:\n");
            printf("Enter\n1.Calculate Final Bill\n2.Generate Receipt\n");
            scanf("%d", &option);

            switch(option)
            {
                float DiscountAmount = 0;
            case 1:DiscountAmount = calculateFinalBill(&cart, &inventory, &totalsales);
                break;
            case 2:generateReceipt(&cart, &inventory,DiscountAmount,&report);
            default:
                printf("Enter valid option\n");
            }
            break;

        case 4:printf("Report:\n");
            printf("Enter\n1.Generate Sales Report\n2.Generate Inventory Report\n3.View Low Stock alerts\n");
            scanf("%d", &option);

            switch(option)
            {
            case 1:generateSalesReport(&cart, &inventory, totalsales,&report);
                cart.head = 0;
                break;
            case 2:generateInventoryReport(&inventory);
                break;
            case 3:viewLowStockAlerts(&inventory);
                break;
            default:
                printf("Enter valid option\n");
            }
            break;
        case 5:saveInventoryToFile(&inventory, "inventory.data");
            clearInventory(&inventory);
            printf("Exiting program...\n");
            return 0;
        default:
            printf("Enter valid choice\n");
        }
    }
    return 0;
}
