#include <iostream>
#include <GameHandler.h>
#include <inventory.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include <parser.h>
#include <fstream>
using namespace std;

void test_parser(){
    string txt = "C://Users/Austin/Desktop/QTProjects/ECE 30862/Zork/samples/sample.txt.xml";
    parser p = parser(txt);
    p.make_game();
    p.print_game();

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
}

void test_file(){
    string filename = "C:\\Users\\Austin\\Desktop\\QTProjects\\ECE 30862\\Zork\\samples/sample.txt.xml";
    string filename2 = "sample.txt.xml";
    ifstream t(filename2);
}

int main()
{
    test_parser();
    cout << "Game Over" << endl;
    return 0;
}


//make vector of triggers
//create make file and test on school machine
/*
 * Game flow:
 * 1. Make game
 * 2. Make inventory
 * 3. assign active room, assign inventory
 * 4. Read in command (verify correct format)
 * 5. pass in commands and check command triggers
 * 6. execute triggers and go to step 4
 * 7. execute input comannd (verifying content of command)
 * 8. check/execute non-command tiggers
 */
