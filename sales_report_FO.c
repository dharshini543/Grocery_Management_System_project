#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"

#define MAX_NAME_LENGTH 50
#define RECORD_SIZE (10 + MAX_NAME_LENGTH + 10 + 10 + 10)

FILE *salesReportFile = NULL;

void openSalesReportFile()
{
    salesReportFile = fopen("SalesReportFile.txt", "r+");
    if (!salesReportFile)
    {
        salesReportFile = fopen("SalesReportFile.txt", "w+");
        if (!salesReportFile)
        {
            return;
        }
    }
    return;
}

void closeSalesReportFile()
{
    if (salesReportFile != NULL) {
        fflush(salesReportFile);
        fclose(salesReportFile);
    }
}

void serializeSalesRecord(const ReportItem *reportItem, const char *name, float price, char *buffer)
{
    float amount = price * reportItem->quantity;

    snprintf(buffer, RECORD_SIZE + 1,
             "%-10d%-50s%-10.2f%-10.2f%-10.2f\n",
             reportItem->itemID, name, price, reportItem->quantity, amount);
}

void deserializeSalesRecord(const char *buffer, int *itemID, char *name, float *price, float *quantity)
{
    float totalValue = 0;

    int itemsParsed = sscanf(buffer, "%d %49s %f %f %f", itemID, name, price, quantity, &totalValue);
}

void loadSalesReportFromFile(Report *report)
{
    if (!salesReportFile)
    {
        printf("Sales report file is not open.\n");
        return;
    }

    fseek(salesReportFile, 0, SEEK_SET);
    char buffer[RECORD_SIZE + 1];
    report->head = NULL;

    while (fgets(buffer, RECORD_SIZE + 1, salesReportFile) != NULL)
    {
        int itemID = 0;
        char name[MAX_NAME_LENGTH + 1] = {0};
        float price = 0, quantity = 0;

        deserializeSalesRecord(buffer, &itemID, name, &price, &quantity);

        ReportItem *newItem = (ReportItem *)malloc(sizeof(ReportItem));
        if (!newItem)
        {
            printf("Memory allocation failed while loading sales report.\n");
            exit(1);
        }

        newItem->itemID = itemID;
        newItem->quantity = quantity;
        newItem->next = NULL;

        if (report->head == NULL)
        {
            report->head = newItem;
        }
        else
        {
            ReportItem *temp = report->head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newItem;
        }
    }

    printf("Sales report loaded successfully from file.\n");
}


void updateSalesReportInFile(Report *report, int itemID, float quantity, const char *name, float price)
{
    fseek(salesReportFile, 0, SEEK_SET);
    char buffer[RECORD_SIZE + 1];
    long currentPos = 0;
    int recordFound = 0;

    while (fgets(buffer, RECORD_SIZE + 1, salesReportFile) != NULL)
    {
        int existingItemID = 0;
        float existingQuantity = 0, existingPrice = 0;
        char existingName[MAX_NAME_LENGTH + 1];

        deserializeSalesRecord(buffer, &existingItemID, existingName, &existingPrice, &existingQuantity);

        if (existingItemID == itemID)
        {
            fseek(salesReportFile, currentPos, SEEK_SET);

            ReportItem updatedItem = { itemID, quantity, NULL };
            memset(buffer, 0, sizeof(buffer));
            serializeSalesRecord(&updatedItem, name, price, buffer);
            fprintf(salesReportFile, "%-10d%-50s%-10.2f%-10.2f%-10.2f\n", updatedItem.itemID,
                    name, price, updatedItem.quantity, updatedItem.quantity * price);
            fflush(salesReportFile);

            recordFound = 1;
            break;
        }

        currentPos = ftell(salesReportFile);
    }

    if (!recordFound)
    {
        fseek(salesReportFile, 0, SEEK_END);
        ReportItem newItem = { itemID, quantity, NULL };
        memset(buffer, 0, sizeof(buffer));
        serializeSalesRecord(&newItem, name, price, buffer);

        fprintf(salesReportFile, "%-10d%-50s%-10.2f%-10.2f%-10.2f\n", newItem.itemID, name, price, newItem.quantity, newItem.quantity * price);
        fflush(salesReportFile);

        //printf("New sales record added for Item ID %d.\n", itemID);
    }
}



