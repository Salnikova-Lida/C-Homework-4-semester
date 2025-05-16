#ifndef __BUILDERS_H__
#define __BUILDERS_H__

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

template <typename T> std::string tostr(const T& t) { 
   std::ostringstream os; 
   os<<t; 
   return os.str(); 
} 

struct ControlPoint{
    std::string name;
    double latitude;
    double longitude;
    double penalty;

    ControlPoint(const std::string& _name, double _latitude, double _longitude, double _penalty): name{_name}, latitude{_latitude}, longitude{_longitude}, penalty{_penalty}{}
    std::string str_val{"Point: "};
};

class Builder{
  public:
    virtual ~Builder(){}
    virtual void printPoint() const = 0;
    virtual int sum() const = 0;
};

class ConcreteBuilder : Builder{
  public:
    ConcreteBuilder(){}
    ~ConcreteBuilder(){
        delete product;
    }
    void SetProduct(ControlPoint* point){
        product = point;
    }

    virtual void printPoint() const override{
        product->str_val += "name: " + product->name + "; coords: [" + tostr(product->latitude) + ", " + tostr(product->longitude) + "]; ";
        std::string penalty = product->penalty == -1 ? "незачет СУ" : tostr(product->penalty);
        product->str_val += std::string("penalty: ") + penalty;
    };

    virtual int sum() const{
        if (product->penalty < 0){
            return 0;
        }
        return product->penalty;
    }

  private:
    ControlPoint* product;
};

#endif