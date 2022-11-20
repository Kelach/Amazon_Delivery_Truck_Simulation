/**
 * 
 * Function testing File for Traveling Salesman Project
*/

#include "traveling_salesman.h" // imports TSP header file
#include <iostream>             // imports standard library thingies
using namespace TravelingSalesman; // we may not want to keep this

int main(){

    
    // Address Distance Tester
    Address addy1(4, 2, 10);
    Address addy2(4, 3, 10);
    Address addy3(4, 5, 13);
    std::cout << "Distance: " << addy1.distance(addy2) << std::endl;
    
    // AddressList add_address tester
    AddressList address_list;
    address_list.add_address(addy1);
    address_list.add_address(addy1);
    address_list.add_address(addy1);

    std::cout << "address length: " 
        << address_list.size() << std::endl;


    // AddressList length() tester
    address_list.add_address(addy2);
    address_list.add_address(addy3);

    std::cout << "Total travel distance: " 
            << address_list.length()<< std::endl;
    
    std::cout << "Closest address to 1 is: " << 
        address_list.index_closest_to(addy1) 
        << std::endl;
    return 0;
}