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
    // add new address to vector of addresses
}
double AddressList::length(){
    double total_distance = 0;
    for (int i=0;i++;i<address_list.size()){
        if  (i != address_list.size()-1){
        }
    }
    // return total length of all addresses
}


// End of AddressList Class Methods



