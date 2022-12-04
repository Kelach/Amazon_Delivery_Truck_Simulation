#include <string>
using std::string;
#include "traveling_salesman.h"
#include <iostream>
#include <fstream>

using namespace TravelingSalesman;

/**
 * @brief Modularizes optimizing the distances of a list of Routes
 * @param routes list of Routes to be sorted and optimized between each other
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
 * @brief Modularizes manager's status report generation.
*/
void write_status_report(string status_to, std::vector<Route> routes, std::vector<Address> unfulfilled_orders, int day_no, int max_dist) {
    std::ofstream file;
    file.open(status_to + "day" + std::to_string(day_no) + "_status.txt");

    file << "Status Report for Day " << day_no
        << "\n\nNumber of trucks: " << routes.size()
        << "\nTruck distance limit: " << max_dist
        << "\n\nTRUCK DATA\n";

    int del_e = 0; // Delivered early
    int del_o = 0; // Delivered on time
    int del_l = 0; // Delivered late
    int und_e = 0; // Undelivered, not due
    int und_o = 0; // Undelivered, due tomorrow
    int und_l = 0; // Undelivered, overdue

    for (int j = 0; j < routes.size(); j++) {
        file << "Truck 1: " << routes.at(j).size() << " deliveries, distance " << routes.at(j).length() << '\n';
        for (int k = 0; k < routes.at(j).size(); k++) {
            int due = routes.at(j).at(k).get_deliver_by(); // Due date of particular order
            if (due - day_no < 0) del_l++;
            else if (due - day_no == 0) del_o++;
            else if (due - day_no > 0) del_e++;
        }
    }

    for (int i = 0; i < unfulfilled_orders.size(); i++) {
        int due = unfulfilled_orders.at(i).get_deliver_by(); // Due date of particular order
        if (due - day_no < 1) und_l++;
        else if (due - day_no == 1) und_o++; // Since it won't be delivered today, on time is tomorrow
        else if (due - day_no > 1) und_e++;
    }

    file << "\nORDER DATA\n"
        << "Delivered: "
        << del_e << " early, "
        << del_o << " on time, "
        << del_l << " late\n"
        << "Unfulfilled: "
        << und_e << " not due, "
        << und_o << " due tomorrow, "
        << und_l << " overdue";

    file.close();
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
        if (dat_path_to != "") routes.at(i).to_dat(dat_path_to + "day" + std::to_string(day_no) + "_truck" + std::to_string(i + 1) + version + ".dat");
        if (tikz_path_to != "") routes.at(i).to_tikz(tikz_path_to + "day" + std::to_string(day_no) + "_truck" + std::to_string(i + 1) + version + ".tikz");
        if (jobs_path_to != "") routes.at(i).to_job(jobs_path_to + "day" + std::to_string(day_no) + "_truck" + std::to_string(i + 1) + version + ".txt");
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
    AddressList orders;
    for (Address unfulfilled_order : unfulfilled_orders) orders.add_address(unfulfilled_order); // Loop add_address to prevent duplicates
    for (Address new_order : new_orders) orders.add_address(new_order); // Loop add_address to prevent duplicates

    // Reuse unfilfilled orders
    unfulfilled_orders.clear();

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

    // Cut out stops by delivery date priority
    for (int j = 0; j < routes.size(); j++) {
        // While a Route is longer than max_dist, remove low priority Addresses until it returns to compliance
        // Add these removed Addresses to unfulfilled_orders
        while (routes.at(j).length() > max_dist) {
            unfulfilled_orders.push_back(routes.at(j).remove_least_priority());
        }
    }

    // Each new route is written to dat, tikz, and job files (use existing Route functions to_dat() and to_tikz())
    write_data(routes, day_no, dat_path_to, tikz_path_to, jobs_path_to, "");
    
    // All leftover orders are the new unfulfilled orders, overwriting existing file
    AddressList unfulfilled_orders_list(unfulfilled_orders);
    unfulfilled_orders_list.to_dat(unfulfilled_orders_from);

    // Manager gets status report with previous orders, new orders, fulfilled orders, unfulfilled orders, overdue orders
    write_status_report(status_to, routes, unfulfilled_orders, day_no, max_dist);
}

int main() {
    // Probably a loop of sorts
    // Call day() for each day
    Address hub(0, 0, 0);

    day(0,
        "..\\Delivery Truck Simulation Data\\Orders\\unfulfilled.dat",
        "..\\Delivery Truck Simulation Data\\Orders\\dayn.dat",
        "..\\Delivery Truck Simulation Data\\dat\\",
        "..\\Delivery Truck Simulation Data\\tikz\\",
        "..\\Delivery Truck Simulation Data\\Jobs\\",
        "..\\Delivery Truck Simulation Data\\Statuses\\",
        2,
        27.0,
        hub,
        true);

    return 0;
}