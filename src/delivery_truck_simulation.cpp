#include <string>
using std::string;
#include "traveling_salesman.h"
#include <iostream>

using namespace TravelingSalesman;

/**
 * @brief Conducts all tasks needed to divy up a list of Addresses to different truck drivers for a day.
 * 
 * @note files must follow specifications to be read in correctly.
 * 
 * @param unfulfilled_orders_from file path to access unfulfilled orders from previous days
 * @param new_orders_from file path to access new orders from today
 * @param dat_path_to folder path to output each generated route's dat file
 * @param tikz_path_to folder path to output each generated route's tikz file
 * @param jobs_path_to folder path to output each generated route's instructions for drivers
 * @param status_to file path to output status report with order data
 * @param num_trucks number of trucks available on that day to divy up
 * @param max_dist maximum distance that a truck may drive in a day
 * @param hub delivery hub Address
*/
void day(string unfulfilled_orders_from, string new_orders_from, string dat_path_to, string tikz_path_to, string jobs_path_to, string status_to, int num_trucks, double max_dist, Address hub) {

    // Read in unfulfilled and new orders, combine into megalist
    std::vector<Address> unfulfilled_orders = AddressList::from_dat(unfulfilled_orders_from).get_vec();
    std::vector<Address> new_orders = AddressList::from_dat(new_orders_from).get_vec();
    AddressList orders(unfulfilled_orders);
    for(Address new_order : new_orders) orders.add_address(new_order); // Loop add_address to prevent duplicates

    // Divy up amongst trucks
    std::vector<Route> routes = {};
    for(int j = 0; j < num_trucks; j++) {
        routes.push_back(Route(AddressList(), hub));
    }
    for (int i = 0; i < orders.size(); i++) {
        routes.at(i % num_trucks).add_address(orders.at(i));
    }

    // Optimize each individual route
    for (int j = 0; j < routes.size(); j++) {
        routes.at(j) = routes.at(j).greedy_route();
        routes.at(j) = routes.at(j).opt2();
    }

    // Optimize between each other
    for(int a = 0; a < routes.size(); a++) {
        for (int b = a + 1; b < routes.size(); b++) {
            routes.at(a).multi_opt2(routes.at(b));
        }
    }

    std::cout << "and\n";

    // Cut things by delivery date priority
    // NOT IMPLEMENTED YET

    // Round 2 optimization
    // NOT IMPLEMENTED YET

    // Each new route is written to dat, tikz, and job files (use existing Route functions to_dat() and to_tikz())
    // All leftover orders are the new unfulfilled orders, overwriting existing file
    // Manager gets status report with previous orders, new orders, fulfilled orders, unfulfilled orders, overdue orders
    for (int i = 0; i < routes.size(); i++) {
        std::cout << "Printing route " << i << '\n';
        routes.at(i).to_dat(dat_path_to + "_truck" + std::to_string(i) + ".dat");
        routes.at(i).to_tikz(tikz_path_to + "_truck" + std::to_string(i) + ".tikz");
        // JOB NOT IMPLEMENTED YET
    }

    // UNFULFILLED ORDERS NOT IMPLEMENTED YET
    // STATUS REPORT NOT IMPLEMENTED YET
}

int main() {
    // Probably a loop of sorts
    // Call day() for each day
    Address hub(0, 0, 0);

    day("..\\Delivery Truck Simulation Data\\Orders\\dayn.dat",
        "..\\Delivery Truck Simulation Data\\Orders\\unfulfilled.dat",
        "..\\Delivery Truck Simulation Data\\dat\\dayn",
        "..\\Delivery Truck Simulation Data\\tikz\\dayn",
        "..\\Delivery Truck Simulation Data\\Jobs\\dayn",
        "..\\Delivery Truck Simulation Data\\Statuses\\dayn",
        2,
        0,
        hub);

    return 0;
}