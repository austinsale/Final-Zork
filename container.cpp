#include "container.h"

using namespace std;
//nothing written not moveable
container::~container(){}

container::container(){
    name = "default";
    status = "unlocked";
    description = "default";
    is_open = false;
}

container::container(string nm){
    name = nm;
    status = "unlocked";
    description = "default";
    is_open = false;
}

void container::open(){
    is_open = true;
    if(items.empty()){
        cout << name << " is empty" << endl;
    }else{
        string output = name + " contains";
        int size = static_cast<int>(items.size());
        for(int i = 0; i< size; i++){
            output += " " + items[static_cast<unsigned long long>(i)]->name;
        }
        output += ".";
        cout << output << endl;
    }
}

void container::add_acceptable(string s){
    accept.push_back(s);
}

void container::init_add(item* i){
    items.push_back(i);
}

bool container::add(item * new_one){
    //check if already in there
    if(contains(new_one -> name) != -1){
        return false;
    }

    //check if it is acceptable
    if(accept.empty() | is_acceptable(new_one->name)){
        if(accept.empty() && !is_open){
            cout << "Error " << name << " is not opened." << endl;
            return false;
        }
        cout << "Item " << new_one -> name << " added to " << name << "." << endl;
        items.push_back(new_one);
        return true;
    }
    else {
        cout << "Error" << endl;
        return false;
    }
}

bool container::is_acceptable(string nm){
    return find(accept.begin(), accept.end(), nm) != accept.end();
}

item * container::remove(string obj){
    int index = contains(obj);
    if(index != -1){
        item * temp =  items[static_cast<unsigned long long>(index)];
        auto n = find(items.begin(), items.end(),temp);
        items.erase(n);
        return temp;
    }
    return 0;
}

item * container::get_item(string name){
    int index = contains(name);
    if(index != -1){
        item * temp =  items[static_cast<unsigned long long>(index)];
        return temp;
    }
    return 0;
}

int container::contains(string name){
    int size = static_cast<int>(items.size());
    for(int i = 0; i< size; i++){
        item * temp = items[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            return i;
        }
    }
    return -1;
}

void container::print(){
    cout << "\nname: " << name << endl;
    cout << "status: " << status << endl;
    cout << "description: " << description << endl;
    cout << "contains: ";
    int size = static_cast<int>(items.size());
    for(int i = 0; i< size; i++){
        cout << items[static_cast<unsigned long long>(i)]->name;
    }
    cout << endl << "accepts: ";
    size = static_cast<int>(accept.size());
    for(int i = 0; i< size; i++){
        cout << accept[static_cast<unsigned long long>(i)];
    }
    cout << endl;
}

void container::update(string s){
    status = s;
}
