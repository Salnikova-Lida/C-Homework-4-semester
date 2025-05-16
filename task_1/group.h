#ifndef __GROUP__
#define __GROUP__

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

struct User;
struct Group{
    Group(std::string name, int id) : _name{name}, _id{id}{}

    void addUser(User* u);
    std::list<User*>::iterator userPointerInGroup(int id);
    void findUser(int id) const;
    void deleteUser(int id);

    std::string _name;
    int _id;
    std::list<User*> _members{};
};

std::ostream& operator<<(std::ostream& os, const Group& g);

#endif