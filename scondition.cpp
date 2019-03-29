#include "scondition.h"
#include <iostream>
scondition::scondition(string obj, string s) : condition ()
{
    object = obj;
    status = s;
}

bool scondition::check(){
    //get object from active room and compare to status
    if((*active_room)->get_object_status(object).compare(status) == 0){
        return true;
    }

    //get object from inventory and compare status
    item * temp = inv->get_item(object);
    if(temp != 0){
        return (temp->status.compare(status) == 0);
    }

    return false;
}

void scondition::print(){
    cout << object << " of status: " << status << endl;
}
