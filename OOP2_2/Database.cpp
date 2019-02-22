//
// Created by ivan on 29.01.19.
//

#include <fstream>
#include "Database.h"
bool Database::loadFromFile(const char *file) {
    if(file == nullptr){
        exit(1);
    }
    std::ifstream data(file);
    if(!data.is_open()){
        return false;
    }
    std::string oneLineFromFile;
    unsigned long  tmp ;
    std::vector <std::string>  allInformation;
    while(data >> oneLineFromFile){
        while( (tmp = oneLineFromFile.find(';')) != std::string::npos){
            allInformation.push_back(oneLineFromFile.substr(0 , tmp));
            oneLineFromFile = oneLineFromFile.substr(tmp + 1);
        }

        allInformation.push_back(oneLineFromFile);
        if(std::stoi(allInformation[0])){
            auto employee_p = std::make_shared<Manager>(allInformation[2] ,
                                                                allInformation[3] ,
                                                                std::stoi(allInformation[4]) ,
                                                                std::stoi(allInformation[1]) ,
                                                                std::stoi(allInformation[6]) ,
                                                                allInformation[5]);
            employees.push_back(std::move(employee_p));
        } else {
            auto employee_p = std::make_shared<Employee>(allInformation[2] ,
                                                                  allInformation[3] ,
                                                                  std::stoi(allInformation[4]) ,
                                                                  std::stoi(allInformation[1]) ,
                                                                  std::stoi(allInformation[6]) ,
                                                                  allInformation[5]);
            employees.push_back(std::move(employee_p));
        }


        allInformation.clear();
    }
}
void Database::DisplayAll(){
    std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << '\n';
    for(const auto& it : employees){
        std::cout << "Employee type:" << ( isManager(it) ?  "Manager" : "Employee" ) << '\n';
        it->Display(true);
        std::cout << '\n';
    }
    std::cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << '\n';
}
void Database::arrangeSubordinates(){
    for( auto& it : employees){
        if(isManager(it)){
            for(auto& findEmployees : employees){
                if(isSameDepartment(it , findEmployees) && !isManager(findEmployees)){
                    addEmployees(it, findEmployees);
                }
            }
        }
    }
}
void Database::DisplayDepartmentEmployees(std::string_view department) {
    for(const auto& it : employees){
        if(castFromPersonToEmployee(it)->getDepartment() == department){
            std::cout << "Employee type:" << ( isManager(it) ?  "Manager" : "Employee" ) << '\n';
            it->Display(true);
        }
    }
}
void  Database::HireEmployee(typename Person::PersonPtr&&  p){
    if(typeid(*p) == typeid(Employee) ){

        employees.push_back(std::move(p));
        castFromPersonToManager(
                findManagerOfDepartment(castFromPersonToEmployee(employees[employees.size() - 1])->getDepartment())
        )->addSubordinate(employees[employees.size() - 1]);
    } else {
        employees.push_back(std::move(p));
    }
}
typename Person::PersonPtr& Database::findManagerOfDepartment(std::string_view department){
    for(auto& it : employees){
        if(castFromPersonToEmployee(it)->getDepartment() == department  && isManager(it)){
            return it;
        }
    }
}
bool Database::FireEmployee(int id) {
    for(auto it = employees.begin(); it != employees.end() ; ++it){
        if(castFromPersonToEmployee(*it)->getId() == id){
            if(!isManager(*it)){
                castFromPersonToManager(findManagerOfDepartment(castFromPersonToEmployee(*it)->getDepartment()))->fireWorkerById(id);
            }
            employees.erase(it);
            return true;
        }
    }
    return false;
}
bool Database::isManager(const typename Person::PersonPtr& person) const noexcept {
    return typeid(*person) == typeid(Manager);
}
bool Database::isSameDepartment( const typename Person::PersonPtr& left ,  const typename Person::PersonPtr& right) noexcept{
    return castFromPersonToEmployee(left)->getDepartment() == castFromPersonToEmployee(right)->getDepartment();
}
void Database::addEmployees(   typename Person::PersonPtr& manager,  typename Person::PersonPtr& employee)  {
    dynamic_cast< Manager *>(manager.get())->addSubordinate(employee);
}
Employee* Database::castFromPersonToEmployee( typename Person::PersonPtr person) noexcept{
    return dynamic_cast< Employee *>(person.get());
}
Manager* Database::castFromPersonToManager( typename Person::PersonPtr& person) noexcept {
    return dynamic_cast< Manager *>(person.get());
}


bool  Database::compareBySalary( const typename Person::PersonPtr& person,  CONDITIONAL conditional,std::string_view value){
    switch(conditional){
        case CONDITIONAL::EQUAl:
            return castFromPersonToEmployee(person)->getSalary() == std::stoi(std::string(value));
        case CONDITIONAL::LESS:
            return castFromPersonToEmployee(person)->getSalary() < std::stoi(std::string(value));
        case CONDITIONAL::MORE:
            return castFromPersonToEmployee(person)->getSalary() > std::stoi(std::string(value));
    }
}
bool  Database::compareByAge(const typename Person::PersonPtr& person,  CONDITIONAL conditional,std::string_view value){
    switch(conditional){
        case CONDITIONAL::EQUAl:
            return castFromPersonToEmployee(person)->getAge() == std::stoi(std::string(value));
        case CONDITIONAL::LESS:
            return castFromPersonToEmployee(person)->getAge() < std::stoi(std::string(value));
        case CONDITIONAL::MORE:
            return castFromPersonToEmployee(person)->getAge() > std::stoi(std::string(value));
    }
}

Database::comparator Database::getCompareFunctionForField(std::string_view field){
    if(field == "age"){
        return &Database::compareByAge;
    }  else if (field == "salary"){
        return &Database::compareBySalary;
    }
    exit(1);
}

Database::workers Database::SQL(std::string_view field,CONDITIONAL conditional,std::string_view value){
    workers vector;
    auto compareFunction = getCompareFunctionForField(field);
    for(const auto& it : employees){
        if( (this->*compareFunction)(it , conditional , value) ){
            vector.push_back(it);
        }
    }

    return vector;
}
void Database::ShowRecordSet(const workers& rs) {
    std::cout << "\n\nRECORD SET\n\n";
    for (const auto& it : rs) {
        it->Display(true);
    }
}