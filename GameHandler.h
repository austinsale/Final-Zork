#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <string>
#include "room.h"
#include "inventory.h"
#include "parser.h"
using namespace std;
class GameHandler
{
public:
    GameHandler();
    virtual ~GameHandler( );
    void read_data();
    bool validate_data();
    bool internal_validate_data();
    bool execute_command();
    void mult_command_execute(vector <string> &c);
    bool itterate_trig_list(vector <trigger *> &tv);
    bool move(int dir);
    bool game_over;
    string * command;
    string command_data[3];
    parser * game_data;
    inventory * inv;
    room ** current_room;
    bool check_all();

private:
    string pattern_array[13];
    string internal_pattern[4];
};

#endif // INPUTHANDLER_H
