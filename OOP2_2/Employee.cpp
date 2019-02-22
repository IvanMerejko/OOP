//
// Created by ivan on 29.12.18.
//
#include <iostream>
#include <iomanip>
#include "Employee.h"
void Employee::setSalary(int salary) {
    this->salary = salary;
}
void Employee::setDepartment(std::string  department){
    this->department = std::move(department);
}
void Employee::setId(int id){
    this->id = id;
}
int Employee::getId() const noexcept{
    return this->id;
}
int Employee::getAge() const noexcept{
    return this->age;
}
int Employee::getSalary() const noexcept{
    return this->salary;
}
std::string_view  Employee::getDepartment() const noexcept{
    return this->department;
}
Employee& Employee::operator=(const Employee &e){
    if(this == &e){
        return *this;
    }
    this->department = e.department;
    this->id         = e.id;
    this->salary     = e.salary;
    this->age        = e.age;
    this->l_name     = e.l_name;
    this->f_name     = e.f_name;
    return *this;
}
void Employee::Display(bool department) noexcept{
    setSetw(!department);
    std::cout << "id: "             << this->id         << '\n';
    setSetw(!department);
    std::cout << this->f_name       << ' ' << this->l_name << " age: " << this->age << " salary: " << this->salary << '\n';
    if( department ){
        std::cout << "department: " << this->department << '\n' ;
    }
    //std::cout << '\n';

}
void Employee::setSetw(bool set){
    if(set){
        std::cout << std::setw(10);
    }
}