#include <string>
using std::string;
#include "traveling_salesman.h"
#include <iostream>
#include <fstream>
#include <chrono>

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
 * @brief Conducts all tasks needed to divy up a list of Addresses to different truck drivers for a day.
 * 
 * @note files must follow specifications to be read in correctly.
 * 
 * @param day_no current date
 * @param unfulfilled_orders_from file path to access unfulfilled orders from previous days
 * @param new_orders_from file path to access new orders from today
 * @param num_trucks number of trucks available on that day to divy up
 * @param max_dist maximum distance that a truck may drive in a day
 * @param hub delivery hub Address
 * 
 * @return number of undelivered orders in a day
*/
int day(int day_no, string unfulfilled_orders_from, string new_orders_from, int num_trucks, double max_dist, Address hub) {
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
    
    // Return number of unfulfilled orders
    return unfulfilled_orders.size();
}

int main() {
    // Start timing simulation
    auto start = std::chrono::high_resolution_clock::now();

    // First scenario, varying distance
    int num_trucks1 = 5;
    std::vector<double> max_dist1 = {250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0};

    // Second scenario, varying num_trucks
    std::vector<int> num_trucks2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double max_dist2 = 450.0;

    // For both
    Address hub(0, 0, 0);
    int day_max = 9;

    // Experiment 1: Varying Maximum Distance

    // Experiment 2: Varying Number of Trucks

    // Stop timing simulation
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Execution time: " << duration.count() << " milliseconds\n";

    return 0;
}