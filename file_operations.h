#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
#include"inventory.h"

void saveInventoryToFile(const Inventory *inventory, const char *filename);
void loadInventoryFromFile(Inventory *inventory, const char *filename);
void clearInventory(Inventory *inventory);
#endif // FILE_OPERATIONS_H
