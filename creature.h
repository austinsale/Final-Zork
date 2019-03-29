#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <vector>
#include <item.h>
#include <container.h>
using namespace std;
class trigger;
class creature
{
public:
    creature();
    creature(string nm);
    virtual ~creature();

    //*******Variables***********
    string name;
    string status;
    string description;
    vector <string> vulnerability;
    trigger * trig;
    vector <trigger*> trig_list;
    trigger * atck;
    //******FUNCTIONS***********
    virtual bool attack(item*); //UPDATE its stupid rn
    virtual void add_vulnerability(string);
    virtual bool is_weakness(string nm);
    virtual void print();
};

#endif // CREATURE_H
