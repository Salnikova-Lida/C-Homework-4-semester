#ifndef __MIXIN_H__
#define __MIXIN_H__
#include <iostream>
#include <string>

template <typename Derived>
struct less_than_comparable{
    bool operator>(Derived const& other) const{
        return other < (*static_cast<const Derived*>(this));
    }

    bool operator<=(Derived const& other) const{
        return !(other < (*static_cast<const Derived*>(this)));
    }

    bool operator>=(Derived const& other) const{
        return !(other > (*static_cast<const Derived*>(this)));
    }

    bool operator==(Derived const& other) const{
        return !((other > (*static_cast<const Derived*>(this))) || (other < (*static_cast<const Derived*>(this))));
    }

    bool operator!=(Derived const& other) const{
        return !(other ==(*static_cast<const Derived*>(this)));
    }
};

template <typename Derived>
struct MixInCounter{
    static int calc;
    MixInCounter(){
        ++calc;
    }
    ~MixInCounter(){
        --calc;
    }
    static int count(){
        return calc;
    }
};

template <typename Derived>
int MixInCounter<Derived>::calc = 0;
#endif