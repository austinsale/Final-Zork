#include "condition.h"
#include <iostream>

string * condition::command = 0;
room ** condition::active_room = 0;
inventory * condition::inv = 0;

condition::condition(){ }
condition::~condition(){}
bool condition::check(){return false;}
void condition::print(){cout << "base condition" << endl;}
