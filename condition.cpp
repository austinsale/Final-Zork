#include "condition.h"
#include "iostream"

string * condition::command = nullptr;
room ** condition::active_room = nullptr;
inventory * condition::inv = nullptr;

condition::condition(){ }
condition::~condition(){}
bool condition::check(){return false;}
void condition::print(){cout << "base condition" << endl;}
