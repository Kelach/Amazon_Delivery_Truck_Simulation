/**
 * 
 * Function testing File for Traveling Salesman Project
*/

#include "traveling_salesman.h" // imports TSP header file
#include <iostream>             // imports standard library thingies
#include <random>
using namespace TravelingSalesman; 

std::random_device rd; //obtain a random number hardware
std::mt19937 gen(rd()); // seed the generator
int random(int low, int high){
    std::uniform_int_distribution<> dist(low, high); // define range
    return dist(gen); // generats random number
}
Route generateRoute(int space, int size){
    Route newRoute( std::vector<Address>{}, Address(0, 0, 0));
    for (int x = 0; x < size; x++){
        int i = random(0, space);
        int j = random(0, space);
        int delivery_by = random(1, 7);
        // only hub can have coordinates (0, 0)
        while ((i+j) == 0){
            j = random(0, space);
            i = random(0, space);
        }
        newRoute.add_address(Address(i, j, delivery_by));

    }
        return newRoute;
}

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
    Route randoRoute = generateRoute(5, 10);

    std::cout << "old route: " << std::endl;
    std::cout << "length: " << randoRoute.length()
    << "\n\n";
    // randoRoute.display();
    std::cout << std::endl;
    std::cout << "greedy route: " << std::endl;
    Route greedy = randoRoute.greedy_route();
    std::cout << "length: " << greedy.length()
    << "\n";
    // greedy.display();
    std::cout << std::endl;

    std::cout << "\nopt2 route: " << std::endl;
    Route opt2 = randoRoute.opt2();
    std::cout << "length: " << opt2.length()
    << "\n";
    // opt2.display();
    std::cout << std::endl;

    std::cout << "\nbefore opti_opt2: " 
    << randoRoute.length()<< std::endl;
    randoRoute.opti_opt2();

    std::cout << "after opti_opt2: "
    << randoRoute.length() << "\n";

    // address_route.display();
    // address_route.display();
    // std::cout << std::endl;

    // std::cout << "Greedy length: " << greedy.length()
    //     << std::endl << "Opt2 Length: " 
    //     << opt2.length()
    //     << std::endl << "Opti_opt2 Length: "
    //     << address_route.length()
    //     << std::endl;

    // std::cout << std::endl << std::endl;
    
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

 

    route1.to_dat("..\\dataout\\demo_2_route1_swapped.dat");
    route1.to_tikz("..\\dataout\\demo_2_route1_swapped.tikz", "red", "black", "black", "-latex");
    route1.to_job("..\\dataout\\demo_2_route1_swapped.txt");
    route2.to_dat("..\\dataout\\demo_2_route2_swapped.dat");
    route2.to_tikz("..\\dataout\\demo_2_route2_swapped.tikz", "red", "gray", "gray", "-latex");
    route2.to_job("..\\dataout\\demo_2_route2_swapped.txt");

    // address_list.to_dat("..\\dataout\\demorw.dat");
    // std::cout << "\nWritten to file: ";
    // address_list.display();
    // AddressList from_file = AddressList::from_dat("..\\dataout\\demorw.dat");
    // std::cout << "\nRead from file: ";
    // from_file.display();
    // from_file.to_dat("..\\dataout\\demorw2.dat");
    
    // Route pre_greedy = generateRoute(3, 5);
    // std::cout << "previous dist: " << pre_greedy.length() << "\n";
    // pre_greedy.to_tikz("..\\Report\\route_figures\\pre_greedy.tikz", "red", "gray", "black", "-latex");
    // Route post_greedy = pre_greedy.greedy_route();
    // std::cout << "new dist: " << post_greedy.length() << "\n";
    // post_greedy.to_tikz("..\\Report\\route_figures\\post_greedy.tikz", "red", "green", "black", "-latex");
    
    // Route pre_opt2 = generateRoute(3, 5);
    // std::cout << "\nprevious dist: " << pre_opt2.length() << "\n";
    // pre_opt2.to_tikz("..\\Report\\route_figures\\pre_opt2.tikz", "red", "gray", "black", "-latex");
    // Route post_opt2 = pre_opt2.greedy_route();
    // std::cout << "new dist: " << post_opt2.length() << "\n";
    // post_opt2.to_tikz("..\\Report\\route_figures\\post_opt2.tikz", "red", "green", "black", "-latex");
     
    // Route r1 = generateRoute(3, 8);
    // std::cout << "\nprevious dist: " << r1.length() << "\n";
    // r1.to_tikz("..\\Report\\route_figures\\r1_pre.tikz", "red", "gray", "black", "-latex");

    // Route r2 = generateRoute(3, 6);
    // std::cout << "\nprevious dist: " << r2.length() << "\n";
    // r2.to_tikz("..\\Report\\route_figures\\r2_pre.tikz", "red", "gray", "black", "-latex");
    
    // r1.multi_opt2(r2);
    // std::cout << "\nnew dist1: " << r1.length() << "\n";
    // std::cout << "\nnew dist2: " << r2.length() << "\n";

    // r1.to_tikz("..\\Report\\route_figures\\r1_post.tikz", "red", "gray", "black", "-latex");
    // r2.to_tikz("..\\Report\\route_figures\\r2_post.tikz", "red", "gray", "black", "-latex");

    // Route r(std::vector<Address> {}, Address(0, 0, 0));
    // r.add_address(Address(2, 0, 10));
    // r.add_address(Address(3, 2, 10));
    // r.add_address(Address(2, 3, 10));
    // r.add_address(Address(0, 2, 10));

    // Route s(std::vector<Address> {}, Address(0, 0, 0));
    // s.add_address(Address(3, 1, 10));
    // s.add_address(Address(2, 1, 10));
    // s.add_address(Address(1, 2, 10));
    // s.add_address(Address(1, 3, 10));

    // s.display();
    // std::cout << "\n";
    // s.swap(r, 3, 4, 3, 4);
    // s.display();
    // r.multi_opt2(s);
    // s.to_tikz("..\\Report\\route_figures\\fig_5_1.tikz", "red", "gray", "green", "-latex");
    // r.to_tikz("..\\Report\\route_figures\\fig_5_2.tikz", "red", "gray", "green", "-latex");
    // std::cout << r.length() << " and "
    //     << s.length() << "\n";


    
    return 0;
}