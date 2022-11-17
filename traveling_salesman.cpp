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
// End of Address Class Methods

// AddressList Class Methods
AddressList::AddressList(){}; 
AddressList::AddressList(std::vector<Address> address_list) : address_list(address_list){}; 
void AddressList::add_address(Address new_address){
    // same address checker
    // for (Address addy: address_list){
    //     if (addy == new_address){
    //         std::cout << "adding duplicate Address Object" << std::endl;
    //     }
    // }
    address_list.push_back(new_address);
    // add new address to vector of addresses
}
double AddressList::length(){

    // for each address, we calculate the distance to next address.
    // (except for the last address).
    double total_distance = 0;
    for (int i=0;i++;i<address_list.size()){
        if  (i != address_list.size()-1){
            Address current_address = address_list.at(i);
            Address next_address = address_list.at(i+1);
            total_distance += current_address.distance(next_address);
        }
    }

    return total_distance;
}
// End of AddressList Class Methods
