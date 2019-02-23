//
// Created by ivan on 21.02.19.
//

#include "Bus.h"
Bus::Bus()
    :Bus{"" , 0 , 0}{};
Bus::Bus(const Bus &bus)
    :Bus{bus.driverName , bus.bus_number , bus.route_number}{};
Bus::Bus(Bus &&bus) noexcept
    :Bus{std::move(bus.driverName) , bus.bus_number , bus.route_number} {};
Bus::Bus(std::string name, int bus_number, int route_number)
        :driverName{std::move(name)} , bus_number{bus_number} , route_number{route_number}{};
std::ostream& operator <<(std::ostream &stream , const Bus &bus){
    stream << "name: "       << bus.driverName   << '\n'
           << "Bus number: "   << bus.bus_number   << '\n'
           << "Route number: " << bus.route_number << '\n';
    return stream;
}
int Bus::getBusNumber() const noexcept {
    return this->bus_number;
}
int Bus::getBusRoute() const noexcept {
    return this->route_number;
}