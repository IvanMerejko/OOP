//
// Created by ivan on 29.12.18.
//

#include <iomanip>
#include "Manager.h"
Manager& Manager::operator=(const Manager &m){
    Employee::operator = (m);
}

void Manager::Display(bool department) noexcept{
    Employee::Display(department);
    std::cout << "\tsubordinates :\n";

    displaySubordinates();
}
void Manager::addSubordinate(typename Person::PersonPtr& p){
    subordinates.push_back(p);
}
void Manager::displaySubordinates() noexcept {
    if  (subordinates.empty()){
        std::cout << "\tnone";
    } else {
        for(const auto& it : subordinates){
            it->Display(false);
        }
    }
    std::cout << std::endl;
}
void Manager::fireWorkerById(int id){
    for(auto it = subordinates.begin() ; it != subordinates.end() ; ++it){
        if(dynamic_cast<Employee* >(it->get())->getId() == id){
            subordinates.erase(it);
            break;
        }
    }
}