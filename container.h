#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "item.h"

using namespace std;
class trigger;
class container
{
public:
    //*********VARIBALES************
    string name;
    string status;
    string description;
    bool is_open;
    vector <string> accept;
    vector <trigger*> trig_list;
    vector <item*> items;
    //**********FUNCTIONS************
    container();
    container(string nm);
    virtual ~container();
    virtual void open();
    virtual void add_acceptable(string s);
    virtual void init_add(item *);
    virtual bool add(item *);
    virtual item * remove(string name);
    virtual item * get_item(string name);
    virtual int contains(string name);
    bool is_acceptable(string);
    virtual void update(string s);
    virtual void print();

};

#endif // CONTAINER_H
