#include "ccondition.h"
#include <iostream>

ccondition::ccondition(string ac) : condition (){active_command = ac;}
ccondition::~ccondition(){ }

bool ccondition::check(){
    return (*command).compare(active_command) == 0;
}

void ccondition::print(){
    cout << "command: " << active_command << endl;
}
