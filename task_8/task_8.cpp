#include <iostream>

#include "factory.h"


int main(int, char **) {
    ExprFactory factory;
    auto c = factory.newConstant(2);
    auto v = factory.newVariable("x");
    auto expr = std::make_shared<Add>(std::make_shared<Multiply>(c, v), c);
    std::map<std::string, double> value{{"x", 3}};
    std::cout << expr->print() << std::endl;
    std::cout << expr->print(&value) <<  " = " << expr->calculate(value) << std::endl;
    factory.clear_pointers();
}