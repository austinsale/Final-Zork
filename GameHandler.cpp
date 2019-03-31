#include "GameHandler.h"
#include <iostream>
#include <regex>
using namespace std;

GameHandler::GameHandler(){
    game_over = false;
}

GameHandler::~GameHandler(){}

void GameHandler::read_data(){
    bool cont = true;
    while (cont){
        string temp;
        getline(cin,temp);
        *command = temp;
        cont = !validate_data();
        if(cont){
            cout << "Error" << endl;
        }
    }
}

bool GameHandler::split_data(){
    string input = *command;
    if(count(input.begin(), input.end(), ' ') > 3){
        return false;
    }
    int count = 0;
    int prev = 0;
    for(int i = 0; i <= input.length(); i++){
        if(input[i] == ' ' || i == input.length()){
            command_data[count++] = input.substr(prev,i-prev);
            prev = i+1;
        }
    }
    return true;
}

bool GameHandler::validate_data(){
    string input = *command;
    if(!split_data()){
        return false;
    }
    int num_words = count(input.begin(), input.end(), ' ');
    if(num_words == 0){
        if(command_data[0].compare("n") == 0 || command_data[0].compare("s") == 0 || command_data[0].compare("e") == 0
                || command_data[0].compare("w") == 0 || command_data[0].compare("i") == 0){
            return true;
        }
    }
    else if(num_words == 1){
        if(command_data[0].compare("take") == 0 || command_data[0].compare("open") == 0 || command_data[0].compare("read") == 0
                || command_data[0].compare("drop") == 0){
            return true;
        }
    }
    else if(num_words == 2){
        if(command_data[0].compare("turn") == 0 && command_data[1].compare("on") == 0){
            return true;
        }
    }else if(num_words == 3){
        if(command_data[0].compare("attack") == 0 && command_data[2].compare("with") == 0){
            return true;
        }else if(command_data[0].compare("put") == 0 && command_data[2].compare("in") == 0){
            return true;
        }
    }
    return false;
}

bool GameHandler::internal_validate_data(){//used for trigger command
    if(validate_data() == true){
        return true; //external command
    }else{
        string input = *command;
        int num_words = count(input.begin(), input.end(), ' ');
        if(num_words == 1){
            if(command_data[0].compare("Delete") == 0 ||
                    (command_data[0].compare("Game") == 0 && command_data[1].compare("Over") == 0)){
                return true;
            }
        }
        else if(num_words == 3){
            if(command_data[0].compare("Update") == 0 && command_data[2].compare("to") == 0){
                return true;
            }else if(command_data[0].compare("Add") == 0 && command_data[2].compare("to") == 0){
                     return true;
            }
        }
        return false;
    }
}

bool GameHandler::execute_command(){
    if(!internal_validate_data()){
        return false;
    }
    if(command_data[0].compare("n") == 0){
        if(!move(0)){
            cout << "Can't go that way." << endl;
        }
        return true;
    }
    else if(command_data[0].compare("e") == 0){
        if(!move(1)){
            cout << "Can't go that way." << endl;
        }
        return true;
    }
    else if(command_data[0].compare("s") == 0){
        if(!move(2)){
            cout << "Can't go that way." << endl;
        }
        return true;
    }
    else if(command_data[0].compare("w") == 0){
        if(!move(3)){
            cout << "Can't go that way." << endl;
        }
        return true;
    }
    else if(command_data[0].compare("i") == 0){
        inv->open();
        return true;
    }
    else if(command_data[0].compare("take") == 0){
        item * temp = (*current_room)->remove(command_data[1]);
        if(!temp)
            return false;
        inv->add(temp);
        return true;
    }
    else if(command_data[0].compare("open") == 0){
        if(command_data[1].compare("exit")==0){
            if((*current_room)->type.compare("exit") == 0){
                *command = "Game Over";
                execute_command();
                return true;
            }
            return false;
        }
        container * temp = (*current_room)->get_container(command_data[1]);
        if(!temp)
            return false;
        temp->open();
        return true;
    }
    else if(command_data[0].compare("read") == 0){
        item * temp = inv->get_item(command_data[1]);
        if(!temp)
            return false;
        temp->read();
        return true;
    }
    else if(command_data[0].compare("drop") == 0){
        item * temp = game_data->get_item(command_data[1]);
        if(!temp){
            return false;
        }
        temp = inv->remove(command_data[1]);
        if(!temp){
            cout << "Error! " << command_data[1] << " is not in inventory" << endl;
            return true;
        }
        cout << temp->name << " dropped." << endl;
        (*current_room)->add(temp);
        return true;
    }
    else if(command_data[0].compare("put") == 0){
        item * i_temp = game_data->get_item(command_data[1]);
        if(!i_temp){
            return false;
        }
        i_temp = inv->get_item(command_data[1]);
        if(!i_temp){
            cout << command_data[1] << " not in inventory." << endl;
            return true;
        }
        container * c_temp = (*current_room)->get_container(command_data[3]);
        if(!c_temp)
            return false;
        if(c_temp->add(i_temp)){
           inv->remove(command_data[1]);
        }
        return true;
    }
    else if(command_data[0].compare("turn") == 0){
        item * temp = inv->get_item(command_data[2]);
        if(!temp){
            return false;
        }

        if(temp->turn){//itterate through actions
            vector <string> cmds = temp->turn->execute();
            mult_command_execute(cmds);
            return true;
        }
        return false;
    }
    else if(command_data[0].compare("attack") == 0){
        creature * c_temp = (*current_room)-> get_creature(command_data[1]);
        if(!c_temp){
            return false;
        }
        item * i_temp = inv->get_item(command_data[3]);
        if(!i_temp){
            return false;
        }
        if(c_temp->attack(i_temp)){
            if(c_temp->atck && c_temp->atck->check_all()){
                vector <string> cmd = c_temp->atck->execute();
                mult_command_execute(cmd);
            }
            return true;
        }
        return false;
    }
    else if(command_data[0].compare("Add") == 0){
        item * item_add = game_data->get_item(command_data[1]);
        container * container_add = game_data->get_container(command_data[1]);
        creature * creature_add = game_data->get_creature(command_data[1]);

        if(item_add == 0 && container_add == 0 && creature_add == 0)
            return false;

        container * c_dest = game_data->get_container(command_data[3]);
        room * r_dest = game_data->get_room(command_data[3]);
        if(!c_dest && !r_dest)
            return false;
        //add object to dest
        if(c_dest){
            if(item_add){
                c_dest->init_add(item_add);
            }else{
                return false;
            }
        }else{
            if(item_add){
                r_dest->add(item_add);
            }else if(container_add){
                r_dest->add(container_add);
            }else{
                r_dest->add(creature_add);
            }
        }
        return true;
    }
    else if(command_data[0].compare("Delete") == 0){
        return game_data->delete_object(command_data[1]);
    }
    else if(command_data[0].compare("Update") == 0){
        item * u_item = game_data->get_item(command_data[1]);
        container * u_container = game_data->get_container(command_data[1]);
        room * u_room = game_data->get_room(command_data[1]);
        creature * u_creature = game_data->get_creature(command_data[1]);
        if(!u_item && !u_room && !u_container && !u_creature){
            return false;
        }
        if(u_item){
            u_item->status = command_data[3];
        }else if(u_container){
            u_container->status = command_data[3];
        }else if(u_room){
            u_room->status = command_data[3];
        }else{
            u_creature->status = command_data[3];
        }
        return true;
    }
    else if(command_data[0].compare("Game") == 0){
        game_over = true;
        return true;
    }
    else{
        return false;
    }
}

bool GameHandler::move(int dir){
    if((*current_room)->border[dir] == 0){
        return false;
    }
    else{
        *current_room = (*current_room)->border[dir];
        cout << (*current_room)->description << endl;
        return true;
    }
}

bool GameHandler::check_all(){
    vector <string> cmds;
    bool triggered = false;
    triggered |= itterate_trig_list((*current_room)->trig_list);

    vector <container*> container_vec = (*current_room)->container_vec;
    vector <creature*> creature_vec = (*current_room)->creature_vec;
    vector <item*> item_vec = (*current_room)->item_vec;
    int size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        container * temp = container_vec[static_cast<unsigned long long>(i)];
        triggered |= itterate_trig_list(temp->trig_list);
    }

    size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        creature * temp = creature_vec[static_cast<unsigned long long>(i)];
        triggered |= itterate_trig_list(temp->trig_list);
    }

    size = static_cast<int>(item_vec.size());
    for(int i = 0; i< size; i++){
        item * temp = item_vec[static_cast<unsigned long long>(i)];
        triggered |= itterate_trig_list(temp->trig_list);
    }
    return triggered;
}

void GameHandler::mult_command_execute(vector <string> &c){
    string prev_command = *command;
    int size = static_cast<int>(c.size());
    for(int i = 0; i< size; i++){
        *command = c[static_cast<unsigned long long>(i)];
        if(!execute_command()){
            cout << "Error" << endl;
        }
    }
    *command = prev_command;
}

bool GameHandler::itterate_trig_list(vector <trigger *> &tv){
    vector <string> cmds;
    bool triggered = false;
    int size = static_cast<int>(tv.size());
    for(int i = 0; i< size; i++){
        if(tv[static_cast<unsigned long long>(i)]->check_all()){
            triggered = true;
            cmds = tv[static_cast<unsigned long long>(i)]->execute();
            mult_command_execute(cmds);
        }
    }
    return triggered;
}
