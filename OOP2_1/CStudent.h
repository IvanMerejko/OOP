//
// Created by ivan on 19.02.19.
//

#ifndef NEW_OOP2_1_CSTUDENT_H
#define NEW_OOP2_1_CSTUDENT_H


#include <string>
#include <vector>

class CStudent{
private:
    int id;
    std::string f_name;
    std::string l_name;
    std::vector<int> grades;
public:
    CStudent() = default;
    CStudent(const CStudent& student);

    ~CStudent() = default;
    void setInfo(int id , const std::string& f_name , const std::string& l_name );
    void setInfo(int id , std::string&& f_name , std::string&& l_name);
    void setGrades(const std::vector<int>& _grades);
    void setGrades(std::vector<int> && _grades);
    float averageGrade() const;

    CStudent& operator= (const CStudent& student);
    bool operator <(const CStudent& student) const;
    void setId(int id);

    int getId() const;
    void printEssentials() const;

};

#endif //NEW_OOP2_1_CSTUDENT_H
