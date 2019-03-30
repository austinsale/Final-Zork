#include "creature.h"
#include <iostream>
#include <algorithm>
using namespace std;

creature::creature()
{
    name = "creature";
    status = "alive";
    description = "default";
    atck = 0;
}

creature::creature(string nm)
{
    name = nm;
    status = "alive";
    description = "default";
    atck = 0;
}

creature::~creature(){}

bool creature::attack(item*weapon){//if true check atck
    if(is_weakness(weapon->name)){
           cout << "You assult the " << name << " with " << weapon->name << endl;
           return true;
    }
    return false;
}

void creature::add_vulnerability(string thing){
    vulnerability.push_back(thing);
}

bool creature::is_weakness(string nm){
    return find(vulnerability.begin(), vulnerability.end(), nm) != vulnerability.end();
}

void creature::print(){
    cout << "\nname: " << name << endl;
    cout << "status: " << status << endl;
    cout << "description: " << description << endl;
    cout << "vulnerablilities: ";
    int size = static_cast<int>(vulnerability.size());
    for(int i = 0; i< size; i++){
        cout << vulnerability[static_cast<unsigned long long>(i)];
    }
    cout << endl;
}
