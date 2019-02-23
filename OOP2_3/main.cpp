#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "list.h"
#include "Bus.h"
void loadFromFile(const std::string& path , List<Bus> & inPark){
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::logic_error("Can`t open file");
    }
    std::string one_bus;

    std::vector<std::string> differentInfo;
    unsigned long  tmp ;
    while( file >> one_bus){

        while( (tmp = one_bus.find(';')) != std::string::npos){
            differentInfo.push_back(one_bus.substr(0 , tmp));
            one_bus = one_bus.substr(tmp + 1);
        }

        differentInfo.push_back(one_bus);

        inPark.push_front(Bus(differentInfo[0] , std::stoi(differentInfo[1]) , std::stoi(differentInfo[2])));

        differentInfo.clear();
    }
}
bool removeBusFromFirstVectorAndInsertItInSecond (List<Bus>& first , List<Bus>& second , size_t number){
    for(auto it = first.begin() ; it != first.end() ; ++it){
        if((*it).data.getBusNumber() == number){
            first.splice(it , second);
            return true;
        }
    }
    return false;
}
/*
 * @param number - number of the bus to be removed from park
 *
 * */
void removeBusFromParkToRoute(List<Bus>& busInPark , List<Bus>& busOnRoute , size_t number){
    if(!removeBusFromFirstVectorAndInsertItInSecond(busInPark , busOnRoute , number)){
        throw std::logic_error("Incorrect bus");
    }
}
/*
 * @param bus - iterator for bus that must be removed from park
 *
 * */
void removeBusFromParkToRoute(List<Bus>& busInPark , List<Bus>& busOnRoute , typename List<Bus>::iterator bus){
    busInPark.splice(bus , busOnRoute);
}
/*
 * @param number - number of the bus to be removed from park
 *
 * */
void removeBusFromRouteToPark(List<Bus>& busInPark , List<Bus>& busOnRoute , size_t number){
    if(!removeBusFromFirstVectorAndInsertItInSecond(busOnRoute , busInPark , number)){
        throw std::logic_error("Incorrect bus");
    }
}


/*
 * @param bus - iterator for bus that must be removed from park
 *
 * */
void removeBusFromRouteToPark(List<Bus>& busInPark , List<Bus>& busOnRoute , typename List<Bus>::iterator bus){
    busOnRoute.splice(bus , busInPark);
}
void printBusesThatAreOnGivenRoute(List<Bus>& busOnRoute , size_t route){
    std::cout << "Buses on route :" << route << '\n';
    std::cout << "------------\n";
    for(auto it = busOnRoute.begin() ; it != busOnRoute.end() ; ++it ){
        if((*it).data.getBusRoute() == route){
            std::cout << (*it).data;
        }
    }
    std::cout << "------------\n";
}
int main() {
    List<Bus> inPark , onRoute;
    try {
        loadFromFile("input.csv" , inPark);
        std::cout << "\n ------------- in park ------------\n";
        inPark.print();
        std::cout << "\n ------------- on route ------------\n";
        onRoute.print();
        removeBusFromParkToRoute(inPark , onRoute , 24);
        removeBusFromParkToRoute(inPark , onRoute , 100);
        std::cout << "\n ------------- in park ------------\n";
        inPark.print();
        std::cout << "\n ------------- on route ------------\n";
        onRoute.print();
        printBusesThatAreOnGivenRoute(onRoute , 3);
        removeBusFromRouteToPark(inPark , onRoute , 100);
        std::cout << "\n ------------- in park ------------\n";
        inPark.print();
        std::cout << "\n ------------- on route ------------\n";
        onRoute.print();
    } catch (std::exception& exception){
        std::cout << exception.what();
        exit(1);
    }


    return 0;
}