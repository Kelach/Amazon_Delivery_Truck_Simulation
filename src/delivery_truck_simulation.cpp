#include <string>
using std::string;
#include "traveling_salesman.h"
#include <iostream>

using namespace TravelingSalesman;

/**
 * @brief Modularizes optimizing the distances of a list of Routes
 * @param routes lits of Routes to be sorted and optimized between each other
*/
void optimize_routes(std::vector<Route>& routes) {
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

    // COULD OPTIMIZE EACH INDIVIDUALLY AGAIN JUST IN CASE???
}

/**
 * @brief Modularizes writing .dat, .tikz, and job files for a list of routes
 * @param routes list of Routes to be written
 * @param day_no current date
 * @param dat_path_to folder path to output each generated route's dat file
 * @param tikz_path_to folder path to output each generated route's tikz file
 * @param jobs_path_to folder path to output each generated route's instructions for drivers
 * @param version version designator to be appended to the end of the filename, if desired
*/
void write_data(std::vector<Route> routes, int day_no, string dat_path_to, string tikz_path_to, string jobs_path_to, string version) {
    for (int i = 0; i < routes.size(); i++) {
        if (dat_path_to != "") routes.at(i).to_dat(dat_path_to + "day" + std::to_string(day_no) + "_truck" + std::to_string(i) + version + ".dat");
        if (tikz_path_to != "") routes.at(i).to_tikz(tikz_path_to + "day" + std::to_string(day_no) + "_truck" + std::to_string(i) + version + ".tikz");
        // JOB NOT IMPLEMENTED YET
    }
}

/**
 * @brief Conducts all tasks needed to divy up a list of Addresses to different truck drivers for a day.
 * 
 * @note files must follow specifications to be read in correctly.
 * 
 * @param day_no current date
 * @param unfulfilled_orders_from file path to access unfulfilled orders from previous days
 * @param new_orders_from file path to access new orders from today
 * @param dat_path_to folder path to output each generated route's dat file
 * @param tikz_path_to folder path to output each generated route's tikz file
 * @param jobs_path_to folder path to output each generated route's instructions for drivers
 * @param status_to file path to output status report with order data
 * @param num_trucks number of trucks available on that day to divy up
 * @param max_dist maximum distance that a truck may drive in a day
 * @param hub delivery hub Address
 * @param analysis whether or not the user wants data from intermediate steps of optimization
*/
void day(int day_no, string unfulfilled_orders_from, string new_orders_from, string dat_path_to, string tikz_path_to, string jobs_path_to, string status_to, int num_trucks, double max_dist, Address hub, bool analysis) {

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

    // Write data from before (for stats and analysis)
    write_data(routes, day_no, dat_path_to, tikz_path_to, "", "_v0");

    // Optimize routes
    optimize_routes(routes);

    // Cut things by delivery date priority
    // NOT IMPLEMENTED YET

    // Round 2 optimization
    // NOT IMPLEMENTED YET

    // Each new route is written to dat, tikz, and job files (use existing Route functions to_dat() and to_tikz())
    write_data(routes, day_no, dat_path_to, tikz_path_to, jobs_path_to, "");
    
    // All leftover orders are the new unfulfilled orders, overwriting existing file
    // UNFULFILLED ORDERS NOT IMPLEMENTED YET

    // Manager gets status report with previous orders, new orders, fulfilled orders, unfulfilled orders, overdue orders
    // STATUS REPORT NOT IMPLEMENTED YET
}

int main() {
    // Probably a loop of sorts
    // Call day() for each day
    Address hub(0, 0, 0);

    day(0,
        "..\\Delivery Truck Simulation Data\\Orders\\dayn.dat",
        "..\\Delivery Truck Simulation Data\\Orders\\unfulfilled.dat",
        "..\\Delivery Truck Simulation Data\\dat\\",
        "..\\Delivery Truck Simulation Data\\tikz\\",
        "..\\Delivery Truck Simulation Data\\Jobs\\",
        "..\\Delivery Truck Simulation Data\\Statuses\\",
        2,
        0,
        hub,
        true);

    return 0;
}