#include<stdio.h>
#include<stdlib.h>
#include"inventory.h"
#include"cart.h"
#include"billing.h"
#include"report.h"
#include "inventory_FO.h"
#include "enum.h"

int calculateFinalBill(Cart *cart, Inventory *inventory, float * totalsales)
{
    CartItem *current = cart->head;
    float total = cart->totalAmount;
    float discountRate = 0;
    float DiscountAmount = 0;

    if(current == 0)
    {
        printf("Cart is Empty\n");
        return 0;
    }
    else
    {
        printf("Enter Discount in percentage\n");
        scanf("%f", &discountRate);

        DiscountAmount = applyDiscount(&total, discountRate);

        printf("Total Bill after Discount : %.2f\n", total);

        *totalsales = *totalsales + total;

        return DiscountAmount;
    }
}


int applyDiscount(float *total, float discountRate)
{
    float DiscountAmount = 0;

    DiscountAmount = *total * (discountRate/100);
    *total = *total - DiscountAmount;

    return DiscountAmount;
}


void generateReceipt(Cart *cart, Inventory *inventory, float DiscountAmount, Report *report)
{
    CartItem *current = cart->head;
    int count = 0;
    float FinalAmount = 0;

    if (current == NULL)
    {
        printf("Cart is empty\n");
    }
    else
    {
        printf("-------------------------Receipt---------------------------\n");
        printf("Item_No\tName\t\tPrice\t\tQuantity\tAmount\n");

        while (current != NULL)
        {
            InventoryItem *temp = inventory->head;
            while (temp != NULL && temp->itemID != current->itemID)
            {
                temp = temp->next;
            }

            if (temp != NULL)
            {
                float itemAmount = temp->price * current->quantity;
                printf("%d\t%s\t\t%.2f\t\t%.2f\t\t%.2f\n", ++count, temp->name, temp->price, current->quantity, itemAmount);

                FinalAmount += itemAmount;

                updateInventoryQuantity(temp, current);
                updateInventoryItemField(inventory, temp->itemID, Quantity, &temp->quantity, temp);
            }
            else
            {
                printf("Item with ID %d not found in inventory.\n", current->itemID);
            }
            current = current->next;
        }
        addSalesReportItem(cart, inventory, report);

        printf("-----------------------------------------------------------\n");
        printf("  \t\t\t\t\tTotal amount :%.2f\n", FinalAmount);
        printf("  \t\t\t\t\tDiscount :%.2f\n", DiscountAmount);
        printf("   \t\t\t\t\tPayableAmount :%.2f\n", FinalAmount - DiscountAmount);
        printf("-----------------------------------------------------------\n");

        cart->totalAmount = 0;
        cart->head = NULL;
    }
}


void updateInventoryQuantity(InventoryItem *temp, CartItem *current)
{
    temp->quantity = temp->quantity - current->quantity;
}
