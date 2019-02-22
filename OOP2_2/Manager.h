#pragma once

#include <iostream>
#include <vector>

#include "Employee.h"

class Manager : public Employee{
public:
    using ManagerPtr = std::shared_ptr<Manager>;
public:
    Manager() = default;
    Manager(std::string _f_name, std::string  _l_name, int _age, int _id , int _salary , std::string department) :
            Employee(std::move(_f_name), std::move(_l_name), _age, _id , _salary , std::move(department)){};
    Manager(const Manager &m) = default;
    Manager& operator=(const Manager &m);
    void Display(bool) noexcept override ;

    //add an employee to the subordinates list
    void addSubordinate(typename Person::PersonPtr& p);
    void displaySubordinates() noexcept ;
//Add here whatever you need
    void fireWorkerById(int id);

private:
    std::vector<typename Person::PersonPtr> subordinates;

};



