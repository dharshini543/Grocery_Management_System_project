#ifndef SALES_REPORT_FO_H
#define SALES_REPORT_FO_H

#include "report.h"
int openSalesReportFile();
void closeSalesReportFile();
void serializeSalesReportRecord(const ReportItem *item, char *buffer);
void deserializeSalesReportRecord(const char *buffer, ReportItem *item);
//void updateSalesReportInFile(Report *report, int itemID, float additionalQuantity);
void updateSalesReportInFile(Report *report, int itemID, float additionalQuantity, const char *name, float price);
void loadSalesReportFromFile(Report *report);
//void printReport(Report *report);
void generateAndUpdateSalesReport(Cart *cart, Inventory *inventory, Report *report);
InventoryItem *getInventoryItemByIDinFile(Inventory *inventory,int itemID);
void saveSalesReportToFile(const Report *report,Inventory *inventory);
//void updateSalesReportInFile(Report *report);
InventoryItem* findInventoryItem(Inventory *inventory, int itemID);
#endif // SALES_REPORT_FO_H
