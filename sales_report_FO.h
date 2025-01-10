#ifndef SALES_REPORT_FO_H
#define SALES_REPORT_FO_H

#include "report.h"

void openSalesReportFile();
void closeSalesReportFile();
void serializeSalesRecord(const ReportItem *reportItem, const char *name, float price, char *buffer);
void deserializeSalesRecord(const char *buffer, int *itemID, char *name, float *price, float *quantity);
void loadSalesReportFromFile(Report *report);
void updateSalesReportInFile(Report *report, int itemID, float quantity, const char *name, float price);

#endif // SALES_REPORT_FO_H
