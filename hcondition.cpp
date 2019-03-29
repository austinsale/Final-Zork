#include "hcondition.h"
#include <iostream>
hcondition::hcondition(bool h, string obj, string own) : condition (){
    has = h;
    object = obj;
    owner = own;
}
hcondition::~hcondition(){}

bool hcondition::check(){
    if(owner.compare("inventory") != 0){
        container * c = (*active_room)->get_container(owner);
        if(c == nullptr){
            return false;
        }else{
            return (c->contains(object) != -1) == has;
        }
    }
    return (inv->contains(object) != -1) == has;
}

void hcondition::print(){
    cout << owner << " does ";
    if(!has){
        cout << "not ";
    }
    cout << "have " << object << endl;
}
