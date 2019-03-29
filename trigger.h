#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>
#include <iostream>
#include <condition.h>
using namespace std;
class trigger
{
public:
    trigger(bool p);
    virtual ~trigger();
    bool permanet;
    bool active;
    vector <string> commands;
    vector <string> prints;
    vector <condition*> conditions;
    virtual bool check_all();
    virtual vector <string> execute();
    virtual void add_command(string s);
    virtual void add_print(string s);
    virtual void add_condition(condition * c);
    virtual void print();
};

#endif // TRIGGER_H
