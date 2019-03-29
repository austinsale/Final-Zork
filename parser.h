#ifndef PARSER_H
#define PARSER_H

#include<fstream>
#include <rapidxml.hpp>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <item.h>
#include <container.h>
#include <creature.h>
#include <room.h>
#include <iostream>
#include <trigger.h>

using namespace std;

class parser
{
public:
    parser(string filename);
    virtual ~parser();

    // *****VARIABLES********
    rapidxml::xml_document<> * doc;
    vector <item*> item_vec;
    vector <container*> container_vec;
    vector <creature *> creature_vec;
    vector <room *> room_vec;
    // *****FUNCTIONS********
    void add_item(item * i);
    void add_container(container * c);
    void add_creature(creature * c);
    void add_room(room * r);

    item * get_item(string name);
    container * get_container(string name);
    creature * get_creature(string name);
    room * get_room(string name);

    item * make_item(rapidxml::xml_node<> * i_node);
    container * make_container(rapidxml::xml_node<> * c_node);
    room * make_room(rapidxml::xml_node<> * r_node);
    creature * make_creature(rapidxml::xml_node<> * c_node);
    trigger * make_trigger(rapidxml::xml_node<> * t_node);
    condition * make_condition(rapidxml::xml_node<> * i_node);
    rapidxml::xml_node<> * get_xml_node(string type, string name);

    void make_game();
    void print_game();

    bool delete_object(string name);
};


#endif // PARSER_H
