
#include <stdio.h>
#include "user.h"
#include "inventory.h"
#include "cart.h"
#include "billing.h"
#include "report.h"
#include "billing.h"
#include "sales_report_FO.h"
#include "inventory_FO.h"
#include "enum.h"

int start()
{
    Userlist userlist = {0};
    userlist.userCount = 0;
    Inventory inventory = {0};
    Cart cart = {0};
    Report report = {0};
    float totalsales = 0;
    int isRunning = 1;
    int choice = 0;
    int option = 0;
    int isOpened = 0;
    int ID = 0;
    float quantity = 0;
    int success = 0;
    User *currentUser = NULL;

    openUserFile();
    openInventoryFile();
    openSalesReportFile();

    loadUsersFromFile(&userlist);
    loadInventoryFromFile(&inventory);
    loadSalesReportFromFile(&report);

    if(userlist.userCount == 0)
    {
        addFirstAdminUser(&userlist);
    }

    printf("Welcome to the Grocery Management System!\n");
    int proceedToLogin = 1;
    while (currentUser == NULL)
    {

        printf("Press 1 to login. Any other number to Exit\n");
        if (scanf("%d", &proceedToLogin) != 1)
        {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        printf("\n\n");

        if(proceedToLogin != 1)
        {
            break;
        }

        currentUser = loginUser(&userlist);
        if (currentUser == NULL)
        {
            printf("Login failed. Please try again.\n");
        }
        else
        {
            printf("Login successful. Welcome, %s!\n", currentUser->username);
        }

        while (currentUser != NULL)
        {
            if (currentUser->role == ROLE_ADMIN)
            {
                printf("Admin Menu:\n");
                printf("1. Add User\n");
                printf("2. Delete User\n");
                printf("3. Manage Inventory\n");
                printf("4. View Reports\n");
                printf("5. Logout\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case  ADMIN_ADD_USER:

                    printf("Enter username: ");
                    char newUsername[MAX_USERNAME_LENGTH];
                    scanf("%s", newUsername);
                    printf("Enter password: ");
                    char newPassword[MAX_PASSWORD_LENGTH];
                    scanf("%s", newPassword);
                    printf("Enter role (1. Admin, 2. User): ");
                    int roleChoice;
                    scanf("%d", &roleChoice);

                    addUser(&userlist, newUsername, newPassword, (roleChoice == 1) ? ROLE_ADMIN : ROLE_USER);
                    break;

                case  ADMIN_DELETE_USER:

                    printf("Enter username to delete: ");
                    char deleteUsername[MAX_USERNAME_LENGTH];
                    scanf("%s", deleteUsername);
                    deleteUser(&userlist, deleteUsername);
                    break;

                case  ADMIN_INVENTORY_MANAGEMENT:

                    printf("Enter\n1.Add Item to Inventory\n2.Delete Item from Inventory\n3.Update Inventory Item Details\n4.Display Inventory summary\n5.Sort Inventory By Name\n6.Sort Inventory By Department\n7.Sort Inventory By Price\n8.Sort Inventory By ID\n9.Get list by ID\n10.Display Deleted Items\n");
                    scanf("%d", &option);

                    switch(option)
                    {

                    case Inventory_AddItem:
                        success = addItemToInventory(&inventory);
                        if(success)
                        {
                            printf("Items Added succesfully to the Inventory\n");
                        }
                        else
                        {
                            printf("Failed to add Item to the Inventory\n");
                        }
                        break;

                    case Inventory_DeleteItem:
                        printf("Enter ID to delete Item\n");
                        scanf("%d", &ID);
                        success = deleteItemFromInventory(&inventory, ID);
                        if(success)
                        {
                            printf("Item deleted succesfully from the Inventory\n");
                        }
                        else
                        {
                            printf("Failed to delete Item from the Inventory\n");
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
                            printf("Failed to update Item to the Inventory\n");
                        }
                        break;

                    case Inventory_DisplaySummary:
                        displayInventorySummary(&inventory);
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

                    case Inventory_SortByItemID:
                        success = sortInventorybyItemID(&inventory);
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

                    case Inventory_DisplayDeletedItems:
                        displayDeletedItems(&inventory);
                        break;

                    default:
                        printf("Enter valid option\n");
                    }
                    break;

                case  ADMIN_REPORTS:

                    printf("Enter\n1.Generate Sales Report\n2.Generate Inventory Report\n3.View Low Stock alerts\n");
                    scanf("%d", &option);

                    switch(option)
                    {
                    case Generate_SalesReport:
                        generateSalesReport(&cart, &inventory,&report,1);
                        cart.head = 0;
                        break;

                    case Generate_InventoryReport:
                        generateInventoryReport(&inventory);
                        break;

                    case ViewLOWStockAlerts:
                        viewLowStockAlerts(&inventory);
                        break;

                    default:
                        printf("Enter valid option\n");
                    }

                    break;

                case  ADMIN_LOGOUT:

                    closeUserFile();
                    currentUser->isLoggedIn = 0;
                    currentUser = NULL;
                    printf("Admin Logging out....\n\n\n");
                    isRunning = 0;
                    break;

                default:
                    printf("Invalid choice.\n");
                }
            }
            else if (currentUser->role == ROLE_USER)
            {
                printf("User Menu:\n");
                printf("1. View Inventory\n");
                printf("2. Manage Cart\n");
                printf("3. Billing\n");
                printf("4. Logout\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case  USER_VIEW_INVENTORY:

                    displayInventorySummary(&inventory);
                    break;

                case  USER_CART_MANAGEMENT:

                    printf("Enter\n1.Add Item to Cart\n2.Delete Item from Cart\n3.Update Cart item quantity\n4.Display Cart Summary\n");
                    scanf("%d", &option);

                    switch(option)
                    {

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
                            printf("Failed to add Item to the cart\n");
                        }
                        break;

                    case Cart_DeleteItem:
                        printf("Enter ID to remove item from cart\n");
                        scanf("%d", &ID);
                        success = removeItemFromCart(&inventory, &cart, ID);
                        if(success)
                        {
                            printf("Item deleted succesfully from the cart\n");
                        }
                        else
                        {
                            printf("Failed to delete Item from the cart\n");
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
                            printf("Failed to update Item to the cart\n");
                        }
                        break;

                    case Cart_DisplaySummary:
                        viewCartSummary(&cart);
                        break;

                    default:
                        printf("Enter valid option\n");
                    }
                    break;

                case  USER_BILLING:

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
                            generateSalesReport(&cart, &inventory,&report, 0);
                            cart.head = 0;
                            break;

                        default:
                            printf("Enter valid option\n");
                        }
                        break;
                    }
                    break;

                case USER_LOGOUT:

                    currentUser->isLoggedIn = 0;
                    currentUser = NULL;
                    printf("User Logging out....\n\n\n");
                    isRunning = 0;
                    break;

                default:
                    printf("Invalid choice.\n");
                }
            }
            else
            {
                printf("Invalid User Role.\n");
                currentUser = NULL;
                break;
            }
        }
    }
    saveUsersToFile(&userlist);
    closeSalesReportFile();
    closeInventoryFile();

    return 0;
}
