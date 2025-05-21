#include <iostream>
#include <list>
#include <memory>

#include "builder.h"

int main(){
    std::list<std::shared_ptr<ControlPoint>> ControlPoints;
    ControlPoints.push_back(std::make_shared<ControlPoint>("Theo   ", 64.81, -64.2, 3));
    ControlPoints.push_back(std::make_shared<ControlPoint>("VÆB    ", 0.75, 135.8, -1));
    ControlPoints.push_back(std::make_shared<ControlPoint>("Tommy  ", -82.7, 95.29, 5));
    ControlPoints.push_back(std::make_shared<ControlPoint>("KAJ    ", 25.36, 144.7, 2));
    ControlPoints.push_back(std::make_shared<ControlPoint>("Shkodra", 46.75, 2.64, -1));
    ControlPoints.push_back(std::make_shared<ControlPoint>("NAPA   ", -86.4, -158.1, 4));
    ControlPoints.push_back(std::make_shared<ControlPoint>("Erika  ", 73.51, 76.76, 3));
    ControlPoints.push_back(std::make_shared<ControlPoint>("Melody ", 27.6, 32.24, -1));

    auto builder = std::make_unique<ConcreteBuilder>(); // хватит полагаться на нью, иначе нужно делиты. тут подошел бы uniqueptr. Done
    double fine = 0;
    for (auto&& ControlPoint : ControlPoints){
        builder->SetProduct(ControlPoint);
        builder->printPoint();
        std::cout << ControlPoint->str_val << std::endl;
        fine += builder->sum();
    }
    std::cout << "Max penalty is " << fine << std::endl;
}