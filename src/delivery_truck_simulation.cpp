#include <string>
using std::string;

int main() {
    // Probably a loop of sorts
    // Call day() for each day

    return 0;
}

/**
 * @brief Conducts all tasks needed to divy up a list of Addresses to different truck drivers for a day.
 * 
 * @note files must follow specifications to be read in correctly.
 * 
 * @param unfulfilled_orders file path to access unfulfilled orders from previous days
 * @param new_orders file path to access new orders from today
 * @param dat_to file path to output each generated route's dat file
 * @param tikz_to file path to output each generated route's tikz file
 * @param jobs_to file path to output each generated route's instructions for drivers
 * @param status_to file path to output status report with order data
 * @param num_trucks number of trucks available on that day to divy up
 * @param max_dist maximum distance that a truck may drive in a day
*/
void day(string unfulfilled_orders, string new_orders, string dat_to, string tikz_to, string jobs_to, int num_trucks, double max_dist) {
    // Read in unfulfilled and new orders, combine into megalist
    // Divy up amongst trucks
    // Round 1 optimization
    // Cut things by delivery date priority
    // Round 2 optimization
    // Each new route is written to dat, tikz, and job files (use existing Route functions to_dat() and to_tikz())
    // All leftover orders are the new unfulfilled orders, overwriting existing file
    // Manager gets status report with previous orders, new orders, fulfilled orders, unfulfilled orders, overdue orders
}