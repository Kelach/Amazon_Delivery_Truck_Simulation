#include "cxxopts.hpp"
#include "traveling_salesman.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>

std::random_device rd; //obtain a random number hardware
std::mt19937 gen(rd()); // seed the generator

/**
 * @brief generates random integer between low-high (inclusive)
 * */ 
int random(int low, int high){
    std::uniform_int_distribution<> dist(low, high); // define range
    return dist(gen); // generate #+

}

TravelingSalesman::Route generateRoute(std::string& keyword, int& space){
    if (keyword == "random"){
        int i = random(0, space);
        int j = random(0, space);
        int delivery_by = random(1, 7);
        // only hub can have coordinates (0, 0)
        while ((i+j) == 0){
            int j = random(0, space);
            int i = random(0, space);
        }
        
        return TravelingSalesman::Route(i, j, delivery_by);

        // get 2 random ints within range of space
        // and one random int between 1 and 7 for delivery date
        // return Route object

    } else if (keyword == "primes"){
        std::vector<int> primes{};
        int prime_num = 
        while
        int i =  
        int j = 
        int delivery_by = random(1, 7)
        // get 2 prime ints within range of space
        // and one random int between 1 and 7 for delivery date
        // return Route object
    } else{
        // throw error for invalid keyword
        throw(5);
    }
    return 
}


int main(int argc, char **argv){
    //*******declare options*******
    
    // -help option
    cxxopts::Options options
        ("cxxopts", "Commandline options demo");
    options.add_options()
        ("h,help","usage information");
    
    // # of routes option
    options.add_options()
        ("n,n_routes","# of routes to generate",
        cxxopts::value<int>()->default_value("100"));
    // coordinate space option
    options.add_options()
        ("s,space","defines x-y coordinate space",
        cxxopts::value<int>()->default_value("10"));

    // primes only keyword option
    options.add_options()
        ("primes","primes keyword",
        cxxopts::value<std::string>()->default_value("random"));
    options.parse_positional({"primes"});

    //*****parse options****
    auto result = options.parse(argc, argv);
    
    // ****perform operation based on options***

    // perform help operation
    if (result.count("help")>0) {
        std::cout << options.help() << '\n';
    }

    // perform n option operation
    auto num_routes = result["n_routes"].as<int>();
    auto space = result["space"].as<int>();
    auto keyword = result["primes"].as<std::string>();
    
    // do for loop 
        // try generateRoute, catch errors
        // each time, make route generation output
        // Route route = generateRoute(keyword, space);
    
    // std::cout << "Generating " << num_routes << " routes" << '\n';
    // // read the positional keyword
    // std::cout << "Found keyword: " << keyword << '\n';

    
    return 0;
}