#pragma once


#include "Person.h"


class Employee : public Person {
public:
    using EmployeePtr = std::shared_ptr<Employee>;
private:
    void setSetw(bool);
public:
    Employee() = default;
    Employee(std::string _f_name, std::string  _l_name, int _age, int _id , int _salary , std::string department) :
            Person( std::move(_f_name) , std::move(_l_name), _age), id(_id) , salary(_salary) , department(std::move(department)){};
    Employee(const Employee &e) = default;
    Employee& operator=(const Employee &e);
    void setSalary(int);
    void setDepartment(std::string  );
    void setId(int);
    int getId() const noexcept;
    std::string_view  getDepartment() const noexcept;
    int getSalary() const noexcept;
    int getAge() const noexcept;
    void Display(bool) noexcept override ;
//Add here whatever you need

protected:
    std::string  department;
    int salary;
    int id;
};


