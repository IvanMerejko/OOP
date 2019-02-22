#include <iostream>
#include <algorithm>
#include <fstream>
#include "CStudent.h"

void listAll(const std::vector<CStudent>& students){
    std::for_each(students.begin() , students.end() ,[](const CStudent& currentStudent){
        currentStudent.printEssentials();
    });
}
void sortByGrades(std::vector<CStudent>& students){
    std::sort(students.begin() , students.end());
}
void deleteById(std::vector<CStudent>& students , int id){
    auto student = std::find_if(students.begin() , students.end() , [id](const CStudent& student){
        return student.getId() == id;
    });
    if(student != students.end()){
        students.erase(student);
    }

}
CStudent bestAverage(const std::vector<CStudent>& students){
    CStudent student;
    std::for_each(students.begin() , students.end() ,[&student](const CStudent& currentStudent){
        if(student.averageGrade() < currentStudent.averageGrade()){
            student = currentStudent;
        }
    });
    return student;
}
void deleteAll(std::vector<CStudent> & students){
    students.clear();
}
std::vector<CStudent> createStudentsVector( const std::string& path) {
    std::vector<CStudent> students;
    std::vector<int> grades;
    std::ifstream file(path);
    std::string line;
    std::string word;
    std::vector<std::string> words;
    unsigned long tmp;
    while (file >> line) {

        while ((tmp = line.find(';')) != std::string::npos) {
            words.push_back(line.substr(0, tmp));
            line = line.substr(tmp + 1);
        }

        words.push_back(line);
        for (size_t i = 0; i < std::atoi(words[3].c_str()); ++i) {
            grades.push_back(std::atoi(words[4 + i].c_str()));
        }

        CStudent student{};
        student.setGrades(std::move(grades));
        student.setInfo(std::atoi(words[0].c_str()), std::move(words[1]), std::move(words[2]) );
        students.push_back(std::move(student));
        words.clear();

    }
    return students;
}
int main() {

    auto students  =  createStudentsVector("Student.csv");
    std::cout << "\n-----------------------------\n";
    listAll(students);
    sortByGrades(students);
    std::cout << "\n-----------------------------\n";
    listAll(students);
    std::cout << "\n-----------------------------\n";
    bestAverage(students).printEssentials();
    deleteById(students , 4);
    std::cout << "\n-----------------------------\n";
    listAll(students);

    return 0;
}