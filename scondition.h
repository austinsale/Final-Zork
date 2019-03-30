#ifndef SCONDITION_H
#define SCONDITION_H

#include "condition.h"
#include <string>
class scondition : public condition
{
public:
    scondition(string obj, string s);
    string status;
    string object;
    virtual bool check();
    virtual void print();
};

#endif // SCONDITION_H
