#ifndef ENUM_H
#define ENUM_H

enum MainMenuOptions
{
    INVENTORY_MANAGEMENT = 1,
    CART_MANAGEMENT,
    BILLING,
    REPORT,
    SAVE_TO_FILE,
    LOGOUT

};


enum InventoryMenuOptions
{
    Inventory_AddItem = 1,
    Inventory_DeleteItem,
    Inventory_UpdateItem,
    Inventory_DisplaySummary,
    Inventory_SortByName,
    Inventory_SortByDepartment,
    Inventory_SortByPrice,
    Inventory_SortByItemID,
    Inventory_GetItemByID,
    Inventory_DisplayDeletedItems
} ;

enum mergeSort
{
    Sort_By_Name = 1,
    Sort_By_Department,
    Sort_By_ItemID,
    Sort_By_Price

};
enum field
{
    Name = 1,
    Brand,
    Department,
    ExpiryDate,
    Price,
    Quantity

};

enum CartMenuOptions
{
    Cart_AddItem = 1,
    Cart_DeleteItem,
    Cart_UpdateQuantity,
    Cart_DisplaySummary
};

enum BillingMenuOptions
{
    Calculate_FinalBill = 1,
    Billing_GenerateReceipt
};

enum ReportMenuOptions
{
    Generate_SalesReport = 1,
    Generate_InventoryReport,
    ViewLOWStockAlerts,
    Report_SaveToFile
};

enum returnValue
{
    Failure = 0,
    Success
};


#endif // ENUM_H
