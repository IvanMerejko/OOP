
#include <iostream>
#include "Person.h"
#include "Manager.h"
#include "Employee.h"
#include "Database.h"


int main() {

    Database database;
    database.loadFromFile("input.csv");
    database.DisplayAll();
    database.arrangeSubordinates();
    database.DisplayAll();
    database.HireEmployee(std::make_shared<Employee>("ivan" , "merezhko" , 19 , 8 , 1000 , "IT"));
    database.DisplayAll();
    database.FireEmployee(0);

    database.DisplayAll();
    database.DisplayDepartmentEmployees("IT");
    database.ShowRecordSet(database.SQL("salary" , Database::CONDITIONAL::MORE , "900"));
    return 0;
}