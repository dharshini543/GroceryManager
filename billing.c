#include<stdio.h>
#include<stdlib.h>
#include"inventory.h"
#include"cart.h"
#include"billing.h"
#include"report.h"

int calculateFinalBill(Cart *cart, Inventory *inventory, float * totalsales)
{
    float total = cart->totalAmount;
    float discountRate;
    float DiscountAmount;

    printf("Enter Discount in percentage\n");
    scanf("%f", &discountRate);
    DiscountAmount = applyDiscount(&total, discountRate);
    printf("Total Bill after Discount : %.2f\n", total);
    *totalsales = *totalsales + total;
    return DiscountAmount;
}

int applyDiscount(float *total, float discountRate)
{
    float DiscountAmount;
    DiscountAmount = *total * (discountRate/100);
    *total = *total - DiscountAmount;
    return DiscountAmount;
}

void generateReceipt(Cart *cart, Inventory *inventory,float DiscountAmount,Report *report)
{
    CartItem *current = cart->head;
    int count = 0;
    float FinalAmount = 0;
    printf("-------------------------Receipt---------------------------\n");
    printf("Item_No\tName\t\tPrice\t\tQuantity\tAmount\n");
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
            printf("%d\t%s\t\t%.2f\t\t%.2f\t\t%.2f\n",++count, Item->name, Item->price, current->quantity, Item->price*current->quantity);
            FinalAmount = FinalAmount + Item->price * current->quantity;
            add_sales_report_item(cart, inventory, report);
            updateInventoryQuantity(temp1, current);
        }
        current = current->next;

    }
    printf("-----------------------------------------------------------\n");
    printf("  \t\t\t\t\tTotal amount :%.2f\n", FinalAmount);
    printf("  \t\t\t\t\tDiscount :%.2f\n", DiscountAmount);
    printf("   \t\t\t\t\tPayableAmount :%.2f\n", FinalAmount - DiscountAmount);
    free(current);
    cart->totalAmount = 0;

}

void updateInventoryQuantity(InventoryItem *temp1,CartItem *current)
{
    temp1->quantity = temp1->quantity - current->quantity;
}
