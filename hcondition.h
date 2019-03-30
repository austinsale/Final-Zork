#ifndef HCONDITION_H
#define HCONDITION_H

#include "condition.h"
class hcondition : public condition
{
public:
    hcondition(bool h, string obj, string own);
    bool has;
    string object;
    string owner;
    virtual ~hcondition();
    virtual bool check();
    virtual void print();
};

#endif // HCONDITION_H
