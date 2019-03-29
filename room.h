#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "vector"
#include "creature.h"
#include "item.h"
#include "container.h"
class trigger;
class room
{
public:
    room();
    room(string nm);
    virtual ~room();

    //*****VARIABLES*******
    string name;
    string description;
    string status;
    string type;
    room * border[4]; //n-e-s-w 0-1-2-3
    vector <container*> container_vec;
    vector <item*> item_vec;
    vector <creature*> creature_vec;
    trigger * trig;//replace later
    vector <trigger*> trig_list;

    //*****FUNCTIONS*******
    void set_dir(string, room *);

    void add(container*);
    void add(item *);
    void add(creature *);

    item * remove(string name); //main callable
    item * remove_from_list(int loc);
    int find_itemvec(string name);
    item * find_containervec(string name);

    container * remove_container(string name);
    creature * remove_creature(string name);
    item * get_item(string name);
    container * get_container(string name);
    creature * get_creature(string name);
    string get_object_status(string name);

    void update(string s);
    void print();

};

#endif // ROOM_H
