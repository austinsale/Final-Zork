#include "room.h"
#include <algorithm>
#include <iostream>

using namespace std;
room::room()
{
    name = "generic room";
    description = "generic";
    status = "generic";
    type = "regular";
    for(int i = 0; i < 4; i++){
        border[i] = 0;
    }
}

room::room(string nm)
{
    name = nm;
    description = "generic";
    status = "generic";
    type = "regular";
    for(int i = 0; i < 4; i++){
        border[i] = 0;
    }
}

room::~room(){}

//can set both at same time but ehh
void room::set_dir(string dir, room * neighbor){
    if(dir.compare("north") == 0){
        border[0] = neighbor;
    }
    else if(dir.compare("east") == 0){
        border[1] = neighbor;
    }
    else if(dir.compare("south") == 0){
        border[2] = neighbor;
    }
    else if(dir.compare("west") == 0){
        border[3] = neighbor;
    }
}

//*****IN GAME FUNCTIONS**********
void room::add(container *c){
    container_vec.push_back(c);
}

void room::add(item *i){
    item_vec.push_back(i);
}

void room::add(creature *c){
    creature_vec.push_back(c);
}

    //****REMOVING ITEM******
//look through item list then container list for item
item * room::remove(string name){
    int res = find_itemvec(name);
    if(res != -1){
        return remove_from_list(res);
    }
    return find_containervec(name);
}

//remove item from a known location
item * room::remove_from_list(int loc){
    item * temp =  item_vec[static_cast<unsigned long long>(loc)];
    auto n = find(item_vec.begin(), item_vec.end(),temp);
    item_vec.erase(n);
    return temp;
}

//get index of item in itemvec
int room::find_itemvec(string name){
    int size = static_cast<int>(item_vec.size());
    for(int i = 0; i< size; i++){
        item * temp = item_vec[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            return i;
        }
    }
    return -1;
}

//get item from list of containers
item * room::find_containervec(string name){
    int size = static_cast<int>(container_vec.size());
    item * m = 0;
    for(int i = 0; i< size; i++){
       if(container_vec[static_cast<unsigned long long>(i)]->is_open){
            m = container_vec[static_cast<unsigned long long>(i)]->remove(name);
            if(m != 0){
                break;
            }
       }
    }
    return m;
}

container * room::remove_container(string name){
    int size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        container * temp = container_vec[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            auto n = find(container_vec.begin(), container_vec.end(),temp);
            container_vec.erase(n);
            return temp;
        }
    }
    return 0;
}

creature * room::remove_creature(string name){
    int size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        creature * temp = creature_vec[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            auto n = find(creature_vec.begin(), creature_vec.end(),temp);
            creature_vec.erase(n);
            return temp;
        }
    }
    return 0;
}

item * room::get_item(string name){
    int res = find_itemvec(name);
    if(res == -1){
        return 0;
    }
    return item_vec[static_cast<unsigned long long>(res)];
}

//GETTING CONTAINER
container * room::get_container(string name){
    int size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        container * temp = container_vec[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            return temp;
        }
    }
    return 0;
}

//GETTING CREATURE
creature * room::get_creature(string name){
    int size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        creature * temp = creature_vec[static_cast<unsigned long long>(i)];
        if(name.compare(temp->name)==0){
            return temp;
        }
    }
    return 0;
}

string room::get_object_status(string name){
    int res = find_itemvec(name);
    if(res != -1){
        return item_vec[static_cast<unsigned long long>(res)] -> status;
    }
    int size = static_cast<int>(container_vec.size());
    item * itm;
    for(int i = 0; i< size; i++){
        itm = container_vec[static_cast<unsigned long long>(i)]->get_item(name);
        if(itm != 0){
           return itm -> status;
        }
    }

    container * temp = get_container(name);
    if(temp == 0){
        return "";
    }
    return temp -> status;
}

void room::update(string s){
    status = s;
}

void room::print(){
    cout << "\name: " << name << endl;
    cout << "status: " << status << endl;
    cout << "description: " << description << endl;
    cout << "type: " << type << endl;
    int size = static_cast<int>(container_vec.size());
    if(size > 0){
        cout << "containers: ";
        for(int i = 0; i< size; i++){
            cout << container_vec[static_cast<unsigned long long>(i)]->name << ", ";
        }
        cout << endl;
    }

    size = static_cast<int>(item_vec.size());
    if(size > 0){
        cout << "items: ";
        for(int i = 0; i< size; i++){
            cout << item_vec[static_cast<unsigned long long>(i)] -> name << ", ";
        }
        cout << endl;
    }

    size = static_cast<int>(creature_vec.size());
    if(size > 0){
        cout << "creatures: ";
        for(int i = 0; i< size; i++){
            cout << creature_vec[static_cast<unsigned long long>(i)] -> name << ", ";
        }
        cout << endl;
    }

    string dir[4] = {"north", "east", "south", "west"};
    for(int i = 0; i < 4; i++){
        if(border[i] != 0){
            cout << dir[i] << ": " << border[i] -> name << endl;
        }
    }
}
