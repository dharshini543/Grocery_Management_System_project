#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"
#include "enum.h"
#include "inventory_FO.h"

int addItemToInventory(Inventory *inventory)
{
    int choice = 1;
    InventoryItem *temp = inventory->head;

    while(choice)
    {
        InventoryItem *newitem = (InventoryItem*)malloc(sizeof(InventoryItem));
        if (!newitem)
        {
            printf("Memory allocation failed.\n");
            return Failure;
        }
        newitem->itemID = inventory->itemCount+1;
        printf("Item name:");
        scanf(" %[^\n]", newitem->name);
        printf("Item Brand:");
        scanf(" %[^\n]",newitem->brand);
        printf("Item Department:");
        scanf(" %[^\n]",newitem->department);
        printf("Item ExpiryDate:");
        scanf("%s",newitem->expiryDate);
        printf("Item price:");
        scanf("%f",&newitem->price);
        printf("Item Quantity:");
        scanf("%f", &newitem->quantity);

        newitem->next = 0;

        if(inventory->head == 0 || strcmp(newitem->name,inventory->head->name) < 0)
        {
            newitem->next = inventory->head;
            inventory->head = newitem;
        }
        else
        {
            InventoryItem *temp = inventory->head;

            while(temp->next != 0 && strcmp(temp->next->name ,newitem->name) < 0)
            {
                temp = temp->next;
            }
            newitem->next = temp->next;
            temp->next = newitem;
        }
        inventory->itemCount++;
        printf("Item Added\n");
        addInventoryItem(inventory, *newitem);

        printf("Want to continue...press 1\n");
        scanf("%d",&choice);

    }

    return Success;
}


int deleteItemFromInventory(Inventory *inventory, int itemID)
{

    InventoryItem *current = inventory->head;
    InventoryItem *prev = NULL;

    if (!current)
    {
        printf("Inventory is Empty\n");
        return Failure;
    }
    if(inventory->head->itemID == itemID)
    {
        InventoryItem *temp = inventory->head->next;
        printf("%d\t%s\t\t%s\t\t%.2f\t\t%f\t\t%s\t\t%s\n", inventory->head->itemID, inventory->head->name, inventory->head->brand, inventory->head->price, inventory->head->quantity, inventory->head->department, inventory->head->expiryDate);
        free(inventory->head);
        inventory->head = temp;
        deleteInventoryItem(inventory, itemID);

        return Success;
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
        inventory->itemCount--;
        deleteInventoryItem(inventory, itemID);
        return Success;
    }
}

int updateItemDetails(Inventory *inventory, int itemID)
{
    int field;
    char newName[50];
    char newBrand[50];
    char newDepartment[30];
    char newExpiryDate[30];
    float newPrice;
    float newQuantity;

    InventoryItem *temp = inventory->head;
    if (!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }

    while (temp != NULL && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Item not found with the given item Id.\n");
        return Failure ;
    }

    printf("Enter new details for the item\n");
    printf("Enter\n1.Update Name\n2.Update Brand\n3.Update Department\n4.Update Expiry Date\n5.Update Price\n6.Update Quantity\n\n");
    scanf("%d", &field);

    switch (field)
    {
    case Name:
        printf("Item name: ");
        scanf(" %[^\n]", newName);
        strcpy(temp->name,newName);
        updateInventoryItemField(inventory, itemID, Name, newName, temp);
        break;
    case Brand:
        printf("Item Brand: ");
        scanf(" %[^\n]", newBrand);
        strcpy(temp->brand,newBrand);
        updateInventoryItemField(inventory, itemID, Brand, newBrand, temp); // Pass newBrand
        break;
    case Department:
        printf("Item Department: ");
        scanf(" %[^\n]", newDepartment);
        strcpy(temp->department,newDepartment);
        updateInventoryItemField(inventory, itemID, Department, newDepartment, temp); // Pass newDepartment
        break;
    case ExpiryDate:
        printf("Item Expiry Date: ");
        scanf(" %[^\n]", newExpiryDate);
        strcpy(temp->expiryDate,newExpiryDate);
        updateInventoryItemField(inventory, itemID, ExpiryDate, newExpiryDate, temp); // Pass newExpiryDate
        break;
    case Price:
        printf("Item Price: ");
        scanf("%f", &newPrice);
        temp->price = newPrice;
        updateInventoryItemField(inventory, itemID, Price, &newPrice, temp); // Pass address of newPrice
        break;
    case Quantity:
        printf("Item Quantity: ");
        scanf("%f", &newQuantity);
        temp->quantity = newQuantity;
        updateInventoryItemField(inventory, itemID, Quantity, &newQuantity, temp); // Pass address of newQuantity
        break;

    default:
        printf("Enter a valid option\n");
        return Failure;
    }

    return Success;
}

void displayInventorySummary(const Inventory *inventory)
{
    if(inventory->head == 0)
    {
        printf("Inventory is empty\n");
    }
    else
    {
        InventoryItem* temp = inventory->head;
        printf("Inventory Summary:\n");
        printf("ID   Name\tBrand\t\tPrice\tQuantity\tDepartment\tExpiryDate\n");
        while(temp != 0)
        {
            if(temp->itemID > 0 )
            {
                printf("%d   %s\t%s\t\t%.2f\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);

            }
            temp = temp->next;
        }
    }
}

void displayDeletedItems(Inventory *inventory)
{
    int deletedItemCount = 0;
    InventoryItem *temp = inventory->head;

    printf("Displaying deleted items:\n");
    printf("ItemNo\tName\t\tBrand\t\tDepartment\t\tExpiryDate\n");
    while (temp != NULL)
    {
        if (temp->itemID < 0)  // Check if the item is marked as deleted
        {
            printf("%d\t%s\t\t%s\t\t%s\t\t%s\n",++deletedItemCount, temp->name,temp->brand,temp->department,temp->expiryDate);
        }
        temp = temp->next;
    }

    if (deletedItemCount == 0)
    {
        printf("No deleted items to display.\n");
    }
    else
    {
        printf("Total deleted items: %d\n", deletedItemCount);
    }
}


int getInventoryItemByID(Inventory*inventory,int itemID)
{
    InventoryItem *temp = inventory->head;
    if(!temp)
    {
        printf("No Item in inventory. Please add.\n");
        return Failure;
    }
    while(temp != 0 && temp->itemID != itemID)
    {
        temp = temp->next;
    }
    if(temp == 0)
    {
        printf("Item not found with the given item Id.\n");
        return Failure;
    }
    printf("%d\t%s\t\t%s\t\t%.2f\t\t%.2f\t\t%s\t\t%s\n", temp->itemID, temp->name, temp->brand, temp->price, temp->quantity, temp->department, temp->expiryDate);

    return Success;
}
