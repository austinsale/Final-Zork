#include "item.h"
#include <iostream>
using namespace std;

item::item(){
  name = "default";
  description = "default";
  writing = "default";
  status = "default";
  active_status = "default";
  status_phrase = "default";
  trig = nullptr;
  turn = nullptr;
}

item::item(string nm){
  name = nm;
  description = "default";
  writing = "default";
  status = "default";
  active_status = "default";
  status_phrase = "default";
  trig = nullptr;
  turn = nullptr;
}

item::~item(){}

void item::read(){
    if(writing.compare("default") != 0){
        cout << writing <<  endl;
    }else{
        cout << "Nothing written." << endl;
    }
}

void item::describe(){
    cout << description << endl;
}

void item::update(string s){
    status = s;
}

void item::print(){
    cout << "\nname: " << name << endl;
    cout << "status: " << status << endl;
    cout << "description: " << description << endl;
    cout << "writing: " << writing << endl;
}

