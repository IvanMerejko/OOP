//
// Created by ivan on 21.02.19.
//

#ifndef OOP2_3_BUS_H
#define OOP2_3_BUS_H


#include <ostream>

class Bus {
public:
    friend std::ostream& operator <<(std::ostream &stream , const Bus &bus);

private:
    std::string driverName;
    int bus_number;
    int route_number;
public:
    Bus();
    Bus(std::string , int , int);
    Bus(const Bus&);
    Bus(Bus&&) noexcept ;
    int getBusNumber() const noexcept ;
    int getBusRoute() const noexcept ;


};


#endif //OOP2_3_BUS_H
