/**
 * 
 * Function testing File for Traveling Salesman Project
*/

#include "traveling_salesman.h" // imports TSP header file
#include <iostream>             // imports standard library thingies
using namespace TravelingSalesman; // we may not want to keep this

int main(){

    
    // Address Distance Tester
    Address addy1(0, 1, 10);
    Address addy2(0, 3, 10);
    Address addy3(0, 5, 13);
    Address addy4(4, 5, 13);
    Address addy5(4, 5, 13);


    std::cout << "Distance: " << addy1.distance(addy2) << std::endl;
    
    // AddressList add_address tester
    AddressList address_list;
    address_list.add_address(addy1);
    address_list.add_address(addy1);
    address_list.add_address(addy1);
    

    // AddressList size() tester
    std::cout << "address length: " 
        << address_list.size() << std::endl;
   
    // AddressList pop() tester
    address_list.pop(0);
    std::cout << "address length: " 
        << address_list.size() << std::endl;

    // AddressList length() tester
    address_list.add_address(addy2);
    address_list.add_address(addy3);

    std::cout << "Total travel distance: " 
            << address_list.length()<< std::endl;
    
    // AddresList index_closest_to() tester
    std::cout << "Closest address to 1 is: " << 
        address_list.index_closest_to(addy1) 
        << std::endl;

    address_list.add_address(addy1);
    address_list.add_address(addy4);

    // Route class test
    Route address_route(address_list, Address(0, 0, 0));
    std::cout << "old route: " << std::endl;
    address_route.display();
    std::cout << std::endl;
    std::cout << "new route: " << std::endl;
    address_route.greedy_route().display();

    // Route class test
    Route route1(address_list, hub);
    route1.to_dat("..\\dataout\\graph" + get_now() + "unsorted.dat");
    route1.to_tikz("..\\dataout\\graph" + get_now() + "unsorted.tikz");
    return 0;
}