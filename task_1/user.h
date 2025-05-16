#ifndef __USER__
#define __USER__

#include <iostream>
#include <string>

struct Group;
struct User{
  User(std::string name, int id) : _name{name}, _id{id}{}
  User(const User& user) : _name{user._name}, _id{user._id}{}
  ~User();

  std::string _name;
  int _id;
  Group* _group;
};

std::ostream& operator<<(std::ostream& os, User& u);

#endif