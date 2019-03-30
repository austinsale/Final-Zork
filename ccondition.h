#ifndef CCONDITION_H
#define CCONDITION_H

#include "condition.h"
#include <iostream>
class ccondition : public condition
{
public:
    ccondition(string ac);
    string active_command;
    virtual ~ccondition();
    virtual bool check();
    virtual void print();
};

#endif // CCONDITION_H
