#include "inventory.h"
#include <iostream>
using namespace std;

inventory::inventory() : container ()
{
    name = "Inventory";
}

void inventory::open(){
    if(items.empty()){
        cout << "Inventory: empty" << endl;
        return;
    }
    string message = "Inventory: ";
    int size = static_cast<int>(items.size());
    for(int i = 0; i< size; i++){
        if(i > 0){
            message += ", ";
        }
        message += items[static_cast<unsigned long long>(i)]->name;
    }
    cout << message << endl;
}

item * inventory::get_item(string name){
    int size = static_cast<int>(items.size());
    for(int i = 0; i< size; i++){
        item * temp = items[static_cast<unsigned long long>(i)];
        if(temp->name.compare(name) == 0){
            return temp;
        }
    }
    return nullptr;
}
