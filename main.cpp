#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "GameHandler.h"
#include "inventory.h"
#include "parser.h"

using namespace std;

int main(int argc, char*argv[])
{
    if(argc != 2){
        cout << "Incorect parameter!" << endl;
        return -1;
    }
    string * val = new string(argv[1]);
    ifstream t(*val);
    delete val;
    if(!t.is_open()){
        cout << "Could not open xml file" << endl;
        return -1;
    }
    parser p = parser(t);
    t.close();
    p.make_game();

    room * active_room = p.get_room("Entrance");
    GameHandler gh = GameHandler();
    inventory * inv = new inventory();
    string * dummy = new string();

    gh.current_room = &active_room;
    gh.inv = inv;
    gh.command = dummy;
    gh.game_data = &p;
    condition::active_room = &active_room;
    condition::inv = inv;
    condition::command = dummy;

    cout << active_room->description << endl;
    while(!gh.game_over){
        gh.read_data();
        if(!gh.check_all())
            if(!gh.execute_command()){
                cout << "Error" << endl;
            }
        if(!gh.game_over){
            *(gh.command)="";
            gh.check_all();
        }
    }
    delete inv;
    delete dummy;
    p.delete_game();
    cout << "Game Over" << endl;
    return 0;
}


