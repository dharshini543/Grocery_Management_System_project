#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "enum.h"

#define MAX_NAME_LENGTH 50
#define MAX_BRAND_LENGTH 50
#define MAX_DEPARTMENT_LENGTH 30
#define MAX_EXPIRY_LENGTH 30
#define RECORD_SIZE (10 + MAX_NAME_LENGTH + MAX_BRAND_LENGTH + MAX_DEPARTMENT_LENGTH + MAX_EXPIRY_LENGTH + 10 + 10)


FILE *inventoryFile = NULL;

int openFilesForReadingWriting()
{
    inventoryFile = fopen("GroceryInventoryFile.txt", "r+");
    if (!inventoryFile)
    {
        inventoryFile = fopen("GroceryInventoryFile.txt", "w+");
        if (!inventoryFile)
        {
            return 0;
        }
    }
    return 1;
}


void closeFile()
{
    if (inventoryFile != NULL)
    {
        fflush(inventoryFile);
        fclose(inventoryFile);
    }
}

void padOrTrimString(char *dest, const char *src, size_t length)
{
    strncpy(dest, src, length);

    size_t srcLen = strlen(src);
    if (srcLen < length)
    {
        memset(dest +srcLen, ' ', length - srcLen);
    }

    dest[srcLen] = '\0';
}

void serializeRecord(const InventoryItem *item, char *buffer) {
    char temp[RECORD_SIZE + 1];

    snprintf(temp, RECORD_SIZE + 1,
             "%-10d%-50s%-50s%-30s%-30s%-10.2f%-10.2f\n",
             item->itemID,
             item->name,
             item->brand,
             item->department,
             item->expiryDate,
             item->price,
             item->quantity);

    strncpy(buffer, temp, RECORD_SIZE);
    buffer[RECORD_SIZE] = '\0';
}


void deserializeRecord(const char *buffer, InventoryItem *item)
{
    sscanf(buffer,
           "%10d%50s%50s%30s%30s%10f%10f",
           &item->itemID,
           item->name,
           item->brand,
           item->department,
           item->expiryDate,
           &item->price,
           &item->quantity);
}

void loadInventoryFromFile(Inventory *inventory)
{
    char buffer[RECORD_SIZE + 1];
    fseek(inventoryFile, 0, SEEK_SET);
    inventory->head = NULL;
    inventory->itemCount = 0;

    int deletedItemCount = 0;

    while (fgets(buffer, RECORD_SIZE + 1, inventoryFile) != NULL)
    {
        if (strlen(buffer) < RECORD_SIZE)
        {
            continue;
        }

        InventoryItem *newItem = (InventoryItem *)malloc(sizeof(InventoryItem));
        if (newItem == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        deserializeRecord(buffer, newItem);

        if (newItem->itemID < 0)
        {
            deletedItemCount++;
        }

        newItem->next = NULL;

        if (inventory->head == NULL)
        {
            inventory->head = newItem;
        }
        else
        {
            InventoryItem *temp = inventory->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newItem;
        }

        inventory->itemCount++;
    }

    if (inventory->itemCount > 0)
    {
        printf("Inventory loaded successfully. %d items loaded.\n", inventory->itemCount);
    }
    else
    {
        printf("No valid items found in inventory file.\n");
    }

    if (deletedItemCount == 0)
    {
        printf("No deleted items.\n");
    }
}



void saveInventoryToFile(Inventory *inventory)
{
    fseek(inventoryFile, 0, SEEK_SET);

    InventoryItem *temp = inventory->head;
    char buffer[RECORD_SIZE + 1];
    while (temp != NULL)
    {
        serializeRecord(temp, buffer);
        fprintf(inventoryFile, "%s", buffer);
        temp = temp->next;
    }
    fflush(inventoryFile);
    printf("Inventory saved successfully.\n");
}


void addInventoryItem(Inventory *inventory, InventoryItem newItem)
{
    fseek(inventoryFile, 0, SEEK_END);

    char buffer[RECORD_SIZE + 1];
    serializeRecord(&newItem, buffer);
    fprintf(inventoryFile, "%s\n", buffer);

    fflush(inventoryFile);
    printf("Item added successfully.\n");
}


void updateInventoryItemField(Inventory *inventory, int itemID, int field, void *newValue, InventoryItem *item)
{
    fseek(inventoryFile, 0, SEEK_SET);
    char buffer[RECORD_SIZE + 1];

    InventoryItem temp;

    while (fgets(buffer, RECORD_SIZE + 1, inventoryFile) != NULL)
    {
        deserializeRecord(buffer, &temp);
        if (temp.itemID == itemID)
        {
            switch (field)
            {
            case Name:
                padOrTrimString(temp.name, (char *)newValue, MAX_NAME_LENGTH);
                break;
            case Brand:
                padOrTrimString(temp.brand, (char *)newValue, MAX_BRAND_LENGTH);
                break;
            case Department:
                padOrTrimString(temp.department, (char *)newValue, MAX_DEPARTMENT_LENGTH);
                break;
            case ExpiryDate:
                padOrTrimString(temp.expiryDate, (char *)newValue, MAX_EXPIRY_LENGTH);
                break;
            case Price:
                temp.price = *(float *)newValue;
                break;
            case Quantity:
                temp.quantity = *(float *)newValue;
                break;


            default:
                printf("Invalid field.\n");
                return;
            }

            fseek(inventoryFile, -RECORD_SIZE, SEEK_CUR);
            serializeRecord(item, buffer);
            fprintf(inventoryFile, "%s", buffer);
            fflush(inventoryFile);
            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Item with ID %d not found.\n", itemID);
}

void deleteInventoryItem(Inventory *inventory, int itemID)
{
    fseek(inventoryFile, 0, SEEK_SET);
    char buffer[RECORD_SIZE + 1];
    InventoryItem temp;

    while (fgets(buffer, RECORD_SIZE + 1, inventoryFile) != NULL)
    {
        deserializeRecord(buffer, &temp);
        if (temp.itemID == itemID)
        {
            temp.itemID = -1;
            fseek(inventoryFile, -RECORD_SIZE, SEEK_CUR);
            serializeRecord(&temp, buffer);
            fprintf(inventoryFile, "%s", buffer);
            fflush(inventoryFile);
            printf("Record marked as deleted.\n");
            return;
        }
    }
    printf("Item with ID %d not found.\n", itemID);
}
