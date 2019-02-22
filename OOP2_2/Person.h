#pragma once

#include <string>
#include <memory>

class Person{
public:
    using PersonPtr = std::shared_ptr<Person>;
public:
    Person() = default;
    Person(std::string f_name , std::string l_name , int age)
            : age{age} , f_name{std::move(f_name)} , l_name{std::move(l_name)}{}
    virtual void Display(bool) noexcept = 0;
protected:
    std::string f_name;
    std::string l_name;
    int age;
};


