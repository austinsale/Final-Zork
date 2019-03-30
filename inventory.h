#ifndef INVENTORY_H
#define INVENTORY_H

#include "container.h"

class inventory : public container
{
public:
    inventory();
    void open();
    item * get_item(string name);
};

#endif // INVENTORY_H
