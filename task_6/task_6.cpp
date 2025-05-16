#include <iostream>
#include <list>

#include "builder.h"

int main(){
    std::list<ControlPoint*> ControlPoints;
    ControlPoints.push_back(new ControlPoint("Theo   ", 64.81, -64.2, 3));
    ControlPoints.push_back(new ControlPoint("VÆB    ", 0.75, 135.8, -1));
    ControlPoints.push_back(new ControlPoint("Tommy  ", -82.7, 95.29, 5));
    ControlPoints.push_back(new ControlPoint("KAJ    ", 25.36, 144.7, 2));
    ControlPoints.push_back(new ControlPoint("Shkodra", 46.75, 2.64, -1));
    ControlPoints.push_back(new ControlPoint("NAPA   ", -86.4, -158.1, 4));
    ControlPoints.push_back(new ControlPoint("Erika  ", 73.51, 76.76, 3));
    ControlPoints.push_back(new ControlPoint("Melody ", 27.6, 32.24, -1));

    ConcreteBuilder* builder = new ConcreteBuilder();
    double fine = 0;
    for (ControlPoint* ControlPoint : ControlPoints){
        builder->SetProduct(ControlPoint);
        builder->printPoint();
        std::cout << ControlPoint->str_val << std::endl;
        fine += builder->sum();
    }
    std::cout << "Max penalty is " << fine << std::endl;
}