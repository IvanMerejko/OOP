#pragma once

#include <iostream>
#include <vector>
#include "Person.h"
#include "Employee.h"
#include "Manager.h"

class Database {
public:

    using CONDITIONAL = enum class cond{
        MORE,
        LESS,
        EQUAl
    };
    using comparator = bool (Database::* )(const typename Person::PersonPtr& ,  CONDITIONAL , std::string_view);
    using workers = std::vector<typename Person::PersonPtr >;
private:
    bool isManager(const typename Person::PersonPtr&  person) const noexcept;
    bool isSameDepartment( const typename Person::PersonPtr&  , const typename Person::PersonPtr& ) noexcept;
    void addEmployees(  typename Person::PersonPtr&  ,   typename Person::PersonPtr& ) ;
    typename Person::PersonPtr&  findManagerOfDepartment(std::string_view department);

    Employee*  castFromPersonToEmployee(typename Person::PersonPtr ) noexcept ;
    Manager* castFromPersonToManager( typename Person::PersonPtr& ) noexcept ;

    bool  compareBySalary(const typename Person::PersonPtr& ,  CONDITIONAL , std::string_view);
    bool  compareByAge(const typename Person::PersonPtr&  , CONDITIONAL , std::string_view);

    comparator getCompareFunctionForField(std::string_view field);

public:
    Database() = default;
    ~Database() = default;//no need in destructor
    //creates “flat” database
    bool loadFromFile(const char *file);
    //arranges "flat" database after loading from the file
    void arrangeSubordinates();
//hire a new employee
    void  HireEmployee(typename Person::PersonPtr&& p);
    void DisplayDepartmentEmployees(std::string_view _department);
    //fire the employee
    bool FireEmployee(int id);
    void DisplayAll();
//Add here whatever you need
    workers SQL(std::string_view field,CONDITIONAL conditional,std::string_view value);
    void ShowRecordSet(const workers& rs);

private:
    workers employees;
};