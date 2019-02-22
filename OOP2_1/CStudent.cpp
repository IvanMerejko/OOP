//
// Created by ivan on 19.02.19.
//

#include "CStudent.h"
#include <algorithm>
#include <numeric>
#include <iostream>


CStudent::CStudent(const CStudent &student)
        :id{student.id} , f_name{student.f_name} , l_name{student.l_name} , grades{student.grades}{
}
int CStudent::getId() const {
    return this->id;
}
void CStudent::setId(int id) {
    this->id = id;
}
void CStudent::setInfo( int id , const std::string &f_name, const std::string &l_name) {
    this->f_name = f_name;
    this->l_name = l_name;
    this->id = id;

}
void CStudent::setInfo(int id, std::string&& f_name, std::string&& l_name) {
    this->f_name = std::move(f_name);
    this->l_name = std::move(l_name);
    this->id = id;
}
void CStudent::setGrades(const std::vector<int>& _grades) {
    grades = _grades;

}
void CStudent::setGrades(std::vector<int> &&_grades) {
    grades = std::move(_grades);
}
float CStudent::averageGrade() const {
    if(grades.empty()){
        return 0.0;
    } else {
        return static_cast<float>(std::accumulate(grades.begin() , grades.end() , 0.0) / grades.size());
    }
}
CStudent& CStudent::operator=(const CStudent &student) {
    if(this == &student){
        return *this;
    }
    this->id = student.id;
    this->l_name = student.l_name;
    this->f_name = student.f_name;
    grades = student.grades;
    return *this;
}
bool CStudent::operator<(const CStudent &student) const {
    return id < student.id;
}
void CStudent::printEssentials() const {
    std::cout << "Id:"              << id       << '\n'
              << "fname:"           << f_name   << '\n'
              << "lname:"           << l_name   << '\n'
              << "averageGrade:"    << averageGrade() << '\n';
}