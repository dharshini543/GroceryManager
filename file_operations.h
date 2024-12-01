#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "inventory.h"
#include"report.h"

int saveInventoryToFile(const Inventory *inventory, const char *filename);
int loadInventoryFromFile(Inventory *inventory, const char *filename);
int saveReportToFile(const Report *report, const char *filename);
int loadReportFromFile(Report *report, const char *filename);

#endif // FILE_OPERATIONS_H

