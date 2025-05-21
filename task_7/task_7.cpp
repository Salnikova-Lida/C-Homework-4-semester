#include <iostream>

#include "bridge.h"

int main(int, char**) {
    Set<int> a({1, 2, 3});
    Set<int> b({1, 4, 9});
    a.add_elem(4);

    std::cout << a << std::endl;
    for (int i = 0; i < 10; ++i) { 
        a.add_elem(i * 2);
        b.add_elem(i * i);
    }

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "a or b: " << a.get_union(b) << std::endl;
    std::cout << "a and b: " << a.get_intersection(b) << std::endl;
}