#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct InventoryItem
{
    int itemID;
    char name[50];
    char brand[50];
    char department[30];
    char expiryDate[30];
    float price;
    float quantity;
    struct InventoryItem *next;
} InventoryItem;

typedef struct Inventory
{
    InventoryItem *head;
    int itemCount;
} Inventory;

int addItemToInventory(Inventory *inventory);
int deleteItemFromInventory(Inventory *inventory, int itemID);
int updateItemDetails(Inventory *inventory, int itemID);
void displayInventorySummary(const Inventory *inventory);
int sortInventorybyName(Inventory *inventory);
int sortInventorybyDepartment(Inventory *inventory);
int sortInventorybyPrice(Inventory *inventory);
int sortInventorybyItemID(Inventory *inventory);
int getInventoryItemByID(Inventory*inventory, int itemID);
void displayDeletedItems(Inventory*inventory);

#endif // INVENTORY_H


