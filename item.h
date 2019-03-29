#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <vector>
using namespace std;
class trigger;
class item
{
public:
    //*********VARIABLES*****************
    string name;        //name of object
    string status;      //whether off or on
    string description;  //description of object
    string writing;     //whats written on ojbect
    vector <trigger*> trig_list;
    trigger * turn;
    string active_status;   //what it changes to
    string status_phrase;   //what it says when item is activated
    //**********FUCNTIONS****************
    virtual ~item();
    item(string nm);
    item(); //make new item
    virtual void describe();    //visual appreance
    virtual void read();        //if writing read it
    virtual void update(string s);
    virtual void print();
    //add owner?
};

#endif // ITEM_H
