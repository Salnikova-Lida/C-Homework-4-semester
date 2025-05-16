#include "group.h"
#include "user.h"

void Group::addUser(User* u) {
    u->_group = this;
    _members.push_back(u);
}

std::list<User*>::iterator Group::userPointerInGroup(int id) {
    return std::find_if(_members.begin(), _members.end(), [&id](User* u) { return u->_id == id; });
}


void Group::findUser(int id) const {
    auto iter = std::find_if(_members.begin(), _members.end(), [&id](User* u) { return u->_id == id; });
    if (iter != _members.end() && *iter != nullptr) {
        std::cout << **iter << std::endl;
    }
}

void Group::deleteUser(int id) {
    auto iter = userPointerInGroup(id);
    if (iter != _members.end()) {
        (*iter)->_group = nullptr;
        _members.erase(iter);
    }
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
    os << "Group: name " << g._name << ", id " << g._id << ",  userlist - [";
    for (auto user : g._members) {
        os << *user;
    }
    os << "]" << std::endl;
    return os;
}