/**
 * traveling_salesman.cpp
 * 
 * Function definition file for Traveling Salesman Project library
*/

#include "traveling_salesman.h"   
#include <iostream>  
#include <fstream>
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
using std::string;

using namespace TravelingSalesman;


string TravelingSalesman::get_now() {
    time_t current_time;
    tm* current_tm;
    char buff[50];
    time(&current_time);
    current_tm = localtime(&current_time);
    strftime(buff, sizeof(buff), "%Y%m%d%H%M%S", current_tm);
    string ret(buff);
    return ret;
}

// Address Class Methods

Address::Address(int i, int j, int deliver_by) : i(i), j(j), deliver_by(deliver_by) {};
Address::~Address(){};

double Address::distance(const Address& other){
    //Cartesian distance
    return sqrt( (i-other.i)*(i - other.i) + (j-other.j)*(j-other.j) ) ;
    
    //Manhattan distance
    //return abs(i-other.i) + abs(j-other.j);
};

// not very robust
bool Address::operator==(const Address& rhs){
    return (rhs.i==i && rhs.j==j && rhs.deliver_by==deliver_by);
}

std::vector<int> Address::get_coords(){
    return std::vector<int> {i, j};
}

// End of Address Class Methods

// AddressList Class Methods
AddressList::AddressList(){}; 
AddressList::AddressList(std::vector<Address> address_list) : address_list(address_list){}
    
AddressList::~AddressList(){};

void AddressList::add_address(Address new_address){
    // Checks if address already current exists

    for (Address addy: address_list){
        if (addy == new_address){
            std::cout << "Ignoring duplicate address" << std::endl;
            return;
        }
    }
    
    // add new address to vector of addresses
    address_list.push_back(new_address);


}
void AddressList::display(){
    for (auto addy:address_list){
        std::vector<int> point = addy.get_coords();
        std::cout << "(" << point[0]
            << ", " << point[1] << ") ";
    }
}
double AddressList::length(){

    // for each address, we calculate the distance to next address.
    // (except for the last address).
    double total_distance = 0;
    for (int i=0;i < address_list.size();i++){
        if  (i != address_list.size()-1){
            Address current_address = address_list.at(i);
            Address next_address = address_list.at(i+1);
            total_distance += current_address.distance(next_address);
        }
    }

    return total_distance;
}
int AddressList::size(){
    return address_list.size();
}
Address AddressList::at(int i){
    return address_list.at(i);
}
int AddressList::index_closest_to(Address main){
    double minDistance = 10^8;
    int minIndex = 0;
    // for each element (conditionally), 
    // updates minDistance and minIndex
    for (int i=0;i<address_list.size();i++){
        Address addy = address_list.at(i);
        
        if ( (addy==main)==false 
            && main.distance(addy) < minDistance){
            minIndex = i;
            minDistance = main.distance(addy);
        }
    }
    return minIndex;
}
Address AddressList::pop(int i){
    Address popped_addy = address_list.at(i);
    address_list.erase(address_list.begin()+i);
    return popped_addy;
}

AddressList AddressList::greedy_route(Address we_are_here){
    AddressList current_route(address_list);
    AddressList new_route;
    while (current_route.size() > 0) {
        int index = current_route.index_closest_to(we_are_here);
        new_route.add_address( current_route.at(index) );
        we_are_here = current_route.pop( index );
    }
return new_route;
    
}

std::vector<Address> AddressList::get_list() {
    return address_list;
}

// End of AddressList Class Methods

// Route Class methods

Route::Route(std::vector<Address> address_list, Address hub) : AddressList(address_list), hub(hub) {}

Route::Route(const AddressList& address_list, Address hub) : AddressList(address_list), hub(hub) {} // Note that this uses a copy constructor

Route::~Route() {}

void Route::to_dat() {
    to_dat(get_now() + ".dat");
}

void Route::to_dat(string fname) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords = hub.get_coords();
    // First, write hub
    file << coords[0] << " " << coords[1] << '\n';
    // Then, write AddressList
    for (Address address : address_list) {
        coords = address.get_coords();
        file << coords[0] << " " << coords[1] << '\n';
    }
    // Finally, write hub
    coords = hub.get_coords();
    file << coords[0] << " " << coords[1];
    file.close();
}

void Route::to_tikz() {
    to_tikz(get_now() + ".tikz");
}

void Route::to_tikz(string fname) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords = hub.get_coords();
    std::vector<int> coords_prev;
    // First, write hub
    file << "\\draw (" << coords[0] << ", " << coords[1] << ") -- ";
    // Then, write AddressList
    for (Address address : address_list) {
        coords_prev = coords;
        coords = address.get_coords();
        file << "(" << coords[0] << ", " << coords[1] << ");\n\\filldraw (" << coords_prev[0] << ", " << coords_prev[1] << ") circle (2pt);\n\\draw (" << coords[0] << ", " << coords[1] << ") --";
    }
    // Finally, write hub
    coords_prev = coords;
    coords = hub.get_coords();
    file << "(" << coords[0] << ", " << coords[1] << ");\n\\filldraw (" << coords_prev[0] << ", " << coords_prev[1] << ") circle (2pt);\n\\filldraw [red] (" << coords[0] << ", " << coords[1] << ") circle (4pt);";
    file.close();
}

// End of Route Class Methods