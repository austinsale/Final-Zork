#include "parser.h"

parser::parser(ifstream &t)
{
    rapidxml::xml_document<> d;
    doc = &d;
    stringstream buffer;
    buffer << t.rdbuf();
    string txt = buffer.str();
    char * cstr = new char[txt.size() + 1];  // Create char buffer to store string copy
    strcpy(cstr, txt.c_str());
    doc->parse<0>(cstr);
    delete[] cstr;
}

parser::~parser(){}

//********ADD FUNCTIONS*******************
void parser::add_item(item *i){
    item_vec.push_back(i);
}

void parser::add_container(container *c){
    container_vec.push_back(c);
}

void parser::add_creature(creature *c){
    creature_vec.push_back(c);
}

void parser::add_room(room *r){
    room_vec.push_back(r);
}

//********GET FUNCTIONS*******************
item * parser::get_item(string name){
    int size = static_cast<int>(item_vec.size());
    for(int i = 0; i< size; i++){
        item * m = item_vec[static_cast<unsigned long long>(i)];
        if(m->name.compare(name) == 0){
            return m;
        }
    }
    return 0;
}

container * parser::get_container(string name){
    int size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        container * m = container_vec[static_cast<unsigned long long>(i)];
        if(m->name.compare(name) == 0){
            return m;
        }
    }
    return 0;
}

creature * parser::get_creature(string name){
    int size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        creature * m = creature_vec[static_cast<unsigned long long>(i)];
        if(m->name.compare(name) == 0){
            return m;
        }
    }
    return 0;
}

room * parser::get_room(string name){
    int size = static_cast<int>(room_vec.size());
    for(int i = 0; i< size; i++){
        room * m = room_vec[static_cast<unsigned long long>(i)];
        if(m->name.compare(name) == 0){
            return m;
        }
    }
    return 0;
}
//****************************************

//*******make functions*******************
room * parser::make_room(rapidxml::xml_node<> * r_node){
    string nm = r_node -> first_node("name") -> value();
    room * r = get_room(nm);
    if(r != 0){
        return r;
    }
    r = new room(nm);
    add_room(r);
    for(rapidxml::xml_node<> * i_node = r_node -> first_node();
            i_node; i_node = i_node->next_sibling()){
        string attr =  i_node -> name();
        if(attr.compare("description") == 0){
            r->description = i_node -> value();
        }
        else if(attr.compare("trigger") == 0){
            trigger * t = make_trigger(i_node);
            r->trig_list.push_back(t);
        }
        else if(attr.compare("border") == 0){
            string dir = i_node -> first_node("direction") -> value();
            string room_nm = i_node -> first_node("name") -> value();
            r -> set_dir(dir,make_room(get_xml_node("room", room_nm)));
        }
        else if(attr.compare("container") == 0){
            r -> add(make_container(get_xml_node(attr,  i_node -> value())));
        }
        else if(attr.compare("creature") == 0){
            r -> add(make_creature(get_xml_node("creature",  i_node -> value())));
        }
        else if(attr.compare("item") == 0){
            r -> add(make_item(get_xml_node("item",  i_node -> value())));
        }
        else if(attr.compare("type") == 0){
            r->type = i_node->value();
        }else if(attr.compare("name") != 0){
            cout << "missed: " << attr << endl;
        }
    }
    return r;
}

creature * parser::make_creature(rapidxml::xml_node<> * c_node){
    creature * c = get_creature(c_node -> first_node() -> value());
    if(c != 0){
        return c;
    }
    c = new creature(c_node -> first_node() -> value());
    add_creature(c);
    for(rapidxml::xml_node<> * i_node = c_node -> first_node();
            i_node; i_node = i_node->next_sibling()){
        string attr =  i_node -> name();
        if(attr.compare("trigger") == 0){
            trigger * t = make_trigger(i_node);
            c->trig_list.push_back(t);
        }else if(attr.compare("vulnerability") == 0){
            c->add_vulnerability(i_node->value());
        }else if(attr.compare("attack") == 0){
            c->atck = make_trigger(i_node);
        }

    }
    return c;
}

container * parser::make_container(rapidxml::xml_node<> * c_node){
    string nm = c_node -> first_node("name") -> value();
    container * c = get_container(nm);
    if(c != 0){
        return c;
    }
    c = new container(nm);
    add_container(c);
    for(rapidxml::xml_node<> * t_node = c_node -> first_node();
            t_node; t_node = t_node->next_sibling()){
        string attr =  t_node -> name();
        if(attr.compare("description") == 0){
            c -> description = attr;
        }else if(attr.compare("accept") == 0){
            c->add_acceptable(t_node->value());
        }else if(attr.compare("status") == 0){
            c -> status = t_node -> value();
        }else if(attr.compare("item") == 0){
            c->init_add(make_item(get_xml_node(attr, t_node->value())));
        }else if(attr.compare("trigger") == 0){
            trigger * t = make_trigger(t_node);
            c->trig_list.push_back(t);
        }else if(attr.compare("name") != 0){
            cout << "missed: attribute" << attr << endl;
        }
    }
    return c;
}

item * parser::make_item(rapidxml::xml_node<> * i_node){
    string nm = i_node -> first_node("name") -> value();
    item * i = get_item(nm);
    if(i != 0){
        return i;
    }
    i = new item(nm);
    add_item(i);
    for(rapidxml::xml_node<> * t_node = i_node -> first_node();
            t_node; t_node = t_node->next_sibling()){
        string attr =  t_node -> name();
        if(attr.compare("description") == 0){
            i -> description = t_node -> value();
        }else if(attr.compare("writing") == 0){
            i -> writing = t_node -> value();
        }else if(attr.compare("status") == 0){
            i -> status = t_node -> value();
        }else if(attr.compare("turnon") == 0){
            trigger * t = make_trigger(t_node);
            t->add_condition(new ccondition("turn on " + i-> name));
            t->prints.insert(t->prints.begin(), "You activate the " + nm + ".");
            i->turn = t;
        }else if(attr.compare("trigger") == 0){
            trigger *t = make_trigger(t_node);
            i->trig_list.push_back(t);
        }else if(attr.compare("name") != 0){
            cout << "missed attribute: " << attr << endl;
        }
    }
    return i;
}

trigger * parser::make_trigger(rapidxml::xml_node<> *t_node){
    //check trigger type
    rapidxml::xml_node<> * type= t_node ->first_node("type");
    bool perm = false;
    if(type != 0){
        string t = type->value();
        perm = t.compare("permanent") == 0;
    }
    trigger * t = new trigger(perm);

    //itterate through conditions, prints, commands
    for(rapidxml::xml_node<> * i_node = t_node -> first_node();
            i_node; i_node = i_node->next_sibling()){
        string attr = i_node -> name();
        if(attr.compare("command") == 0){
            t->add_condition(new ccondition(i_node->value()));
        }else if(attr.compare("condition") == 0){
            t->add_condition(make_condition(i_node));
        }else if(attr.compare("print") == 0){
            t->add_print(i_node -> value());
        }else if(attr.compare("action") == 0){
            t->add_command(i_node -> value());
        }
    }
    trigger_vec.push_back(t);
    return t;
}

condition * parser::make_condition(rapidxml::xml_node<> *i_node){
    string obj = i_node -> first_node("object")->value();
    if(i_node -> first_node("has") != 0){
        string owner =  i_node -> first_node("owner")->value();
        string has_val = i_node -> first_node("has")->value();
        bool has = has_val.compare("yes") == 0;
        return new hcondition(has, obj, owner);
    }else{
        string status = i_node -> first_node("status")->value();
        return new scondition(obj, status);
    }
}

rapidxml::xml_node<> * parser::get_xml_node(string type, string name){
    rapidxml::xml_node<> * map = doc->first_node();
    for(rapidxml::xml_node<> * obj = map->first_node(); obj;obj=obj->next_sibling()){
        string t = obj->name();
        if(t.compare(type) == 0){
            string n = obj->first_node("name")->value();
            if(n.compare(name) == 0){
                return obj;
            }
        }
    }
    return 0;
}
//****************************************

void parser::make_game(){
    rapidxml::xml_node<> * map = doc->first_node();
    for(rapidxml::xml_node<> * obj = map->first_node(); obj;obj=obj->next_sibling()){
        string nm =  obj->name();
        if(nm.compare("room") ==0){
            make_room(obj);
        }else if (nm.compare("creature") == 0) {
            make_creature(obj);
        }else if (nm.compare("container")== 0){
            make_container(obj);
        }else if (nm.compare("item") == 0){
            make_item(obj);
        }
    }
    doc->clear();
}

void parser::delete_game(){
    int size = static_cast<int>(room_vec.size());
    for(int i = 0; i< size; i++){
        delete room_vec[static_cast<unsigned long long>(i)];
    }

    size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        delete creature_vec[static_cast<unsigned long long>(i)];
    }

    size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        delete container_vec[static_cast<unsigned long long>(i)];
    }

    size = static_cast<int>(item_vec.size());
    for(int i = 0; i< size; i++){
        delete item_vec[static_cast<unsigned long long>(i)];
    }

    size = static_cast<int>(trigger_vec.size());
    for(int i = 0; i< size; i++){
        delete trigger_vec[static_cast<unsigned long long>(i)];
    }
}

void parser::print_game(){
    cout << "***********ROOMS***********";
    int size = static_cast<int>(room_vec.size());
    for(int i = 0; i< size; i++){
        room_vec[static_cast<unsigned long long>(i)]->print();
    }
    cout << endl << "***********CREATURES***********";
    size = static_cast<int>(creature_vec.size());
    for(int i = 0; i< size; i++){
        creature_vec[static_cast<unsigned long long>(i)]->print();
    }
    cout << endl << "***********CONTAINERS*********** ";
    size = static_cast<int>(container_vec.size());
    for(int i = 0; i< size; i++){
        container_vec[static_cast<unsigned long long>(i)]->print();
    }
    cout << endl << "***********ITEMS***********";
    size = static_cast<int>(item_vec.size());
    for(int i = 0; i< size; i++){
        item_vec[static_cast<unsigned long long>(i)]->print();
    }
    cout << endl << "***************************" << endl;
}

bool parser::delete_object(string name){
    room * del_room = get_room(name);
    if(del_room != 0){
        int size = static_cast<int>(room_vec.size());
        for(int i = 0; i< size; i++){
            room * temp = room_vec[static_cast<unsigned long long>(i)];
            for(int k = 0; k < 4; k ++){
                if(temp->border[k] == del_room){
                   temp->border[k] = 0;
                }
            }
        }
        auto n = find(room_vec.begin(), room_vec.end(), del_room);
        room_vec.erase(n);
        delete del_room;
        return true;
    }

    creature * del_creature = get_creature(name);
    if(del_creature != 0){
        int size = static_cast<int>(room_vec.size());
        for(int i = 0; i< size; i++){
            room * temp = room_vec[static_cast<unsigned long long>(i)];
            temp->remove_creature(del_creature->name);
        }
        //auto n = find(creature_vec.begin(), creature_vec.end(),del_creature); //dont think this is right
        //creature_vec.erase(n);
        return true;
    }

    container * del_cont = get_container(name);
    if(del_cont != 0){
        //remove from all rooms
        int size = static_cast<int>(room_vec.size());
        for(int i = 0; i< size; i++){
            room * temp = room_vec[static_cast<unsigned long long>(i)];
            temp->remove_container(del_cont->name);
        }
        //delete from parser list
        //auto n = find(container_vec.begin(), container_vec.end(),del_cont);
        //container_vec.erase(n);
        return true;
    }

    item * del_item = get_item(name);
    if(del_item != 0){
        int size = static_cast<int>(room_vec.size());
        for(int i = 0; i< size; i++){
            room * temp = room_vec[static_cast<unsigned long long>(i)];
            temp -> remove(del_item->name);
        }
        //auto n = find(item_vec.begin(), item_vec.end(),del_item);
        //item_vec.erase(n);
        return true;
    }

    return false;
}
