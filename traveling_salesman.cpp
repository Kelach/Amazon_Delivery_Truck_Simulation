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

}


// End of AddressList Class Methods



