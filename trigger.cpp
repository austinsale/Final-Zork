#include "trigger.h"

trigger::trigger(bool p)
{
    permanet = p;
    active = true;
}

trigger::~trigger(){
    int size = static_cast<int>(conditions.size());
    for(int i = 0; i< size; i++){
        delete conditions[static_cast<unsigned long long>(i)];
    }
};

bool trigger::check_all(){
    if(!active){
        return false;
    }
    int size = static_cast<int>(conditions.size());
    for(int i = 0; i< size; i++){
        condition * c =conditions[static_cast<unsigned long long>(i)];
        if(!(c->check())){
            return false;
        }
    }
    return true;
}

void trigger::add_print(string s){
    prints.push_back(s);
}

void trigger::add_command(string s){
    commands.push_back(s);
}

void trigger::add_condition(condition *c){
    conditions.push_back(c);
}

vector <string> trigger::execute(){
    if(!permanet){
        active = false;
    }
    int size = static_cast<int>(prints.size());
    for(int i = 0; i< size; i++){
        cout << prints[static_cast<unsigned long long>(i)] << endl;
    }
    return commands;
}

void trigger::print(){
    cout << "trigger info: ";
    if(permanet){
        cout << "permanet, ";
    }else{
        cout << "single, ";
    }
    if(active){
        cout << "active";
    }
    cout << endl;

    cout << "conditions: " << endl;
    int size = static_cast<int>(conditions.size());
    for(int i = 0; i< size; i++){
        conditions[static_cast<unsigned long long>(i)]->print();
    }
    cout << "prints: " << endl;
    size = static_cast<int>(prints.size());
    for(int i = 0; i< size; i++){
        cout << prints[static_cast<unsigned long long>(i)] << endl;
    }
    cout << "commands: " << endl;
    size = static_cast<int>(commands.size());
    for(int i = 0; i< size; i++){
        cout << commands[static_cast<unsigned long long>(i)] << endl;
    }
}
