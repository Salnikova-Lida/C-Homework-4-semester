#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "group.h"
#include "user.h"

std::list<Group*> group_list;
std::list<User*> user_list;

void createUser(const std::string& name, int id){
    user_list.push_back(new User(name, id));
    std::cout << "User " << name << " was created\n" << std::endl;
}

std::list<User*>::iterator userPointerInList(int id){
    return std::find_if(user_list.begin(), user_list.end(), [&id](User* u){ return u->_id == id; });
}

void findUser(int id){
    auto target = userPointerInList(id);
    if (target != user_list.end()){
        std::cout << **target << std::endl;
        return;
    }
    std::cout << "User with id " << id << " does not exist\n" << std::endl;
}

void printUserList(){
    for (auto user : user_list){
        std::cout << *user;
    }
    std::cout << std::endl;
}

void deleteUser(int id){
    auto target = userPointerInList(id);
    if (target != user_list.end()){
        user_list.erase(target);
        delete *target;
        return;
    }
    std::cout << "User with id " << id << " does not exist\n" << std::endl;
}

void newGroup(const std::string& name, int id){
    group_list.push_back(new Group(name, id));
    std::cout << "Group " << name << " was created\n" << std::endl;
}

std::list<Group*>::iterator groupPointer(int id){
    return std::find_if(group_list.begin(), group_list.end(), [&id](Group* g){ return g->_id == id; });
}

void findGroup(int id){
    auto target = groupPointer(id);
    if (target != group_list.end()){
        std::cout << **target << std::endl;
        return;
    }
    std::cout << "Group with id " << id << " does not exist\n" << std::endl;
}
void printGroupList(){
    for (auto group : group_list){
        std::cout << *group;
    }
    std::cout << std::endl;
}

void deleteGroup(int id){
    auto target = groupPointer(id);
    if (target != group_list.end()){
        group_list.erase(target);
        return;
    }
    delete *target;
    std::cout << "Group with id " << id << " does not exist\n" << std::endl;
}

void addUserToGroup(int group_id, int user_id){
    auto g = groupPointer(group_id);
    auto u = userPointerInList(user_id);
    if ((g != group_list.end()) && (u != user_list.end())){
        (*g)->addUser(*u);
        std::cout << "User " << user_id <<" is linked to group" << group_id << "\n" << std::endl;
        return;
    } else if (g == group_list.end()){
        std::cout << "Group with id " << group_id << " does not exist\n" << std::endl;
        return;
    }
    std::cout << "User with id " << user_id << " does not exist\n" << std::endl;
}

int process(const std::vector<std::string>& args){
    if (args.size() == 0){
        std::cout << "\nYou can use following commands: \nnewU {user_name, user_id}     create a new user\n" << 
        "delU {user_id}                delete a user\nprintU                        see the list of users\nfindU {user_id}               know more about a user\n" <<
        "newG {group_name, group_id}   create a group\ndelG {group_id}               delete a group\nprintG                        see the list of groups\n" << 
        "findG {group_id}              know more about a group\nconnect {group_id, user_id}   link a user to a group\n" << std::endl;
        return 0;
    }
    if (args[0] == "newU"){
        if (args.size() != 3){
            std::cout << "Invalid format for the command, two arguments must be name and user_id\n" << std::endl;
            return 0;
        }
        createUser(args[1], std::stoi(args[2]));
    } else if (args[0] == "delU"){
        if (args.size() != 2){
            std::cout << "Invalid format for the command, the only argument must be user_id\n" << std::endl;
            return 0;
        }
        deleteUser(std::stoi(args[1]));
    } else if (args[0] == "printU"){
        if (args.size() != 1){
            std::cout << "Invalid format for the command, no arguments needed\n" << std::endl;
            return 0;
        }
        printUserList();
    } else if (args[0] == "findU"){
        if (args.size() != 2){
            std::cout << "Invalid format for the command, the only argument must be user_id\n" << std::endl;
            return 0;
        }
        findUser(std::stoi(args[1]));
    } else if (args[0] == "newG"){
        if (args.size() != 3){
            std::cout << "Invalid format for the command, two arguments must be group_name and group_id\n" << std::endl;
            return 0;
        }
        newGroup(args[1], std::stoi(args[2]));
    } else if (args[0] == "delG"){
        if (args.size() != 2){
            std::cout << "Invalid format for the command, the only argument must be group_id\n" << std::endl;
            return 0;
        }
        deleteGroup(std::stoi(args[1]));
    } else if (args[0] == "printG"){
        if (args.size() != 1){
            std::cout << "Invalid format for the command, no arguments needed\n" << std::endl;
            return 0;
        }
        printGroupList();
    } else if (args[0] == "findG"){
        if (args.size() != 2){
            std::cout << "Invalid format for the command, the only argument must be group_id\n" << std::endl;
            return 0;
        }
        findGroup(std::stoi(args[1]));
    } else if (args[0] == "connect"){
        if (args.size() != 3){
            std::cout << "Invalid format for the command, two arguments must be group_id and user_id\n" << std::endl;
            return 0;
        }
        addUserToGroup(std::stoi(args[1]), std::stoi(args[2]));
    } else if (args[0] != "q"){
        std::cout << "Invalid command, press enter to see 'help'\n" << std::endl;
        return 0;
    }
    return 1;
}

std::vector<std::string> parse(const std::string& line){
    std::vector<std::string> args;
    std::istringstream iss(line);
    std::string arg;
    while (iss >> arg){
        args.push_back(arg);
    }
    return args;
}

int main(){
    std::string input;
    while (std::getline(std::cin, input)){
        input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch){ return !std::isspace(ch); }));
        input.erase(find_if(input.rbegin(), input.rend(), [](int ch){ return !std::isspace(ch); }).base(), input.end());
        std::vector<std::string> args = parse(input);
        int res = process(args);
        if (res){
            break;
        }
    }
    return 0;
}