#include "user.h"
#include "group.h"

User::~User(){
  if (_group == nullptr){
    return;
  }
  _group->deleteUser(_id);
}
 
std::ostream& operator<<(std::ostream& os, User& u){
    os << "User: id " << u._id << ", name " << u._name;
    if (u._group != nullptr){
        os << ", group " << u._group->_id;
    } else{
        os << ". User does not belong to any group";
    }
    os << std::endl;
    return os;
}