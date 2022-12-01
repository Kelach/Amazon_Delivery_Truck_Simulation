/**
 * 
 * Function testing File for Traveling Salesman Project
*/

#include "traveling_salesman.h" // imports TSP header file
#include <iostream>             // imports standard library thingies
using namespace TravelingSalesman; // we may not want to keep this

int main() {

    
    // Address Distance Tester
    Address addy1(1, 1, 10);
    Address addy2(3, 3, 10);
    

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
    address_list.add_address(addy1);
    address_list.add_address(addy2);
    Address addy3(3, 2, 10);
    address_list.add_address(addy3);

    std::cout << "Total travel distance: " 
            << address_list.length()<< std::endl;
    
    // AddresList index_closest_to() tester
    std::cout << "Closest address to 1 is: " << 
        address_list.index_closest_to(addy1) 
        << std::endl;

    address_list.add_address(Address(1, 3, 10));
    address_list.add_address(Address(1, 2, 10));
    address_list.add_address(Address(3, 1, 10));
    
    // Route class test 1
    Route address_route(address_list, Address(0, 0, 0));
    std::cout << "old route: " << std::endl;
    address_route.display();
    std::cout << std::endl;
    std::cout << "greedy route: " << std::endl;
    Route greedy = address_route.greedy_route();
    greedy.display();
    std::cout << std::endl;
    std::cout << "opt2 route: " << std::endl;
    Route opt2 = address_route.opt2();
    opt2.display();
    std::cout << std::endl;
    std::cout << "Greedy length: " << greedy.length()
        << std::endl << "Opt2 Length: " 
        << opt2.length() << std::endl;

    std::cout << std::endl << std::endl;
    
    address_route.to_dat("..\\dataout\\demo_1_old.dat");
    address_route.to_tikz("..\\dataout\\demo_1_old.tikz", "red", "black", "black", "-latex");
    greedy.to_dat("..\\dataout\\demo_1_greedy.dat");
    greedy.to_tikz("..\\dataout\\demo_1_greedy.tikz", "red", "blue", "blue", "-latex");
    opt2.to_dat("..\\dataout\\demo_1_opt2.dat");
    opt2.to_tikz("..\\dataout\\demo_1_opt2.tikz", "red", "green", "green", "-latex");
    
    Route route1(std::vector<Address>{}, Address(0, 0, 0));
    route1.add_address(Address(2, 0, 10));
    route1.add_address(Address(3, 2, 10));
    route1.add_address(Address(2, 3, 10));
    route1.add_address(Address(0, 2, 10));
    
    Route route2(std::vector<Address>{}, Address(0, 0, 0));
    route2.add_address(Address(3, 1, 10));
    route2.add_address(Address(2, 1, 10));
    route2.add_address(Address(1, 2, 10));
    route2.add_address(Address(1, 3, 10));
    
    std::cout << "before swap: " << std::endl
        << "route 1: ";
    route1.display();
    std::cout << std::endl << "route 2: ";
    route2.display();
    std::cout << std::endl << std::endl;

    route1.to_dat("..\\dataout\\demo_2_route1_unswapped.dat");
    route1.to_tikz("..\\dataout\\demo_2_route1_unswapped.tikz", "red", "black", "black", "-latex");
    route1.to_job("..\\dataout\\demo_2_route1_unswapped.txt");
    route2.to_dat("..\\dataout\\demo_2_route2_unswapped.dat");
    route2.to_tikz("..\\dataout\\demo_2_route2_unswapped.tikz", "red", "gray", "gray", "-latex");
    route1.to_job("..\\dataout\\demo_2_route2_unswapped.txt");

    route1.multi_opt2(route2);

    std::cout << "after swap: " << std::endl
    << "route 1: ";
    route1.display();
    std::cout << std::endl << "route 2: ";
    route2.display();
    std::cout << std::endl;

    // Route r(std::vector<Address> {}, Address(0, 0, 0));
    // r.add_address(Address(2, 0, 10));
    // r.add_address(Address(2, 1, 10));
    // r.add_address(Address(1, 2, 10));
    // r.add_address(Address(0, 2, 10));

    // Route s(std::vector<Address> {}, Address(0, 0, 0));
    // s.add_address(Address(3, 1, 10));
    // s.add_address(Address(3, 2, 10));
    // s.add_address(Address(2, 3, 10));
    // s.add_address(Address(1, 3, 10));
    // std::cout << r.length() << " and "
    //     << s.length() << "\n"; 

    route1.to_dat("..\\dataout\\demo_2_route1_swapped.dat");
    route1.to_tikz("..\\dataout\\demo_2_route1_swapped.tikz", "red", "black", "black", "-latex");
    route1.to_job("..\\dataout\\demo_2_route1_swapped.txt");
    route2.to_dat("..\\dataout\\demo_2_route2_swapped.dat");
    route2.to_tikz("..\\dataout\\demo_2_route2_swapped.tikz", "red", "gray", "gray", "-latex");
    route1.to_job("..\\dataout\\demo_2_route2_swapped.txt");

    address_list.to_dat("..\\dataout\\demorw.dat");
    std::cout << "\nWritten to file: ";
    address_list.display();
    AddressList from_file = AddressList::from_dat("..\\dataout\\demorw.dat");
    std::cout << "\nRead from file: ";
    from_file.display();
    from_file.to_dat("..\\dataout\\demorw2.dat");

    return 0;
}