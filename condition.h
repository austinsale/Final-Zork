#ifndef CONDITION_H
#define CONDITION_H

#include "room.h"
#include "container.h"
#include "inventory.h"
#include <string>
class condition
{
public:
    condition();
    virtual ~condition();
    static string * command;
    static room ** active_room;
    static inventory * inv;
    virtual bool check();
    virtual void print();
};

#endif // CONDITION_H
