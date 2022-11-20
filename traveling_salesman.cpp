/**
 * traveling_salesman.cpp
 * 
 * Function definition file for Traveling Salesman Project library
*/

#include <iostream>  
#include "traveling_salesman.h"           
#include <math.h>
#include <vector>
using namespace TravelingSalesman;


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

AddressList AddressList::greedy_route(Address hub){
    AddressList current_route(address_list);
    AddressList new_route;
    for (auto adddress : address_list){

        int index = current_route.index_closest_to(hub);
        new_route.add_address( current_route.at(index) );
        current_route.pop( index );
        hub = new_route.at( new_route.size()-1 );
    }
return new_route;
    
}


// End of AddressList Class Methods
