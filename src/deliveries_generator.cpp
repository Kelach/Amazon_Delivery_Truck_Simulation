#include "cxxopts.hpp"
#include "traveling_salesman.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>

  std::random_device rd; //obtain a random number hardware
  std::mt19937 gen(rd()); // seed the generator

/**
 * @brief generates random integer between low-high (inclusive)
 * */ 
int random(int low, int high){
    // std::cout <<"Low is: " << low << " High is: " << high << "\n";
    std::uniform_int_distribution<> dist(low, high); // define range
    return dist(gen); // generats random number
}

/**
 * @brief generates Address Object w/random coordinates and delivery date.
 * @param space defines space of x-y coordinate system.
 * */ 
TravelingSalesman::Address generateAddress(int& space, int& offset){
        int i = random(0, space);
        int j = random(0, space);
        int delivery_by = random(1+offset, 7+offset);
        // only hub can have coordinates (0, 0)
        // if ((i+j)==0) std::cout <<"entering loop\n";
        while ((i+j) == 0){
            // std::cout << "generating new addresses "
            //     << "because " << i << " + " << j << " is 0\n"
            //     << "even though the space is: " << space << "\n";
           
            // std::random_device rd; // seed the generato 
            // gen = std::mt19937(rd()); // seed the generator
            j = random(0, space);
            i = random(0, space);
        }
        // get 2 random ints within range of space
        // and one random int between 1 and 7 for delivery date
        // return Address object
        return TravelingSalesman::Address(i, j, delivery_by);
}
/**
 * @brief generates route with a starting hub at (0, 0)
 * @param keyword generates route with "random" or "primes" coordinate points Addresses
 * @param space defines space of x-y coordinate system.
 * @param address_count # of addresses to generate per route
 * */ 

int main(int argc, char **argv){
    //*******declare options*******
    
    // -help option
    cxxopts::Options options
        ("Deliveries Generator", "Commandline options");
    options.add_options()
        ("h,help","usage information");
    
    // # addresses per route
    options.add_options()
        ("a,addresses","# of addresses to generate",
        cxxopts::value<int>()->default_value("5"));

    // coordinate space option
    options.add_options()
        ("s,space","defines x-y coordinate space",
        cxxopts::value<int>()->default_value("10"));
    
    options.add_options()
        ("d,days","defines # of days orders should be generated for. (all delivery days are relative to 0)",
        cxxopts::value<int>()->default_value("14"));


    //*****parse options****
    auto result = options.parse(argc, argv);
    
    // ****perform operation based on options***
    
    // performs help operation
    if (result.count("help")>0) {
        std::cout << options.help() << '\n';
        return 0;
    }

    // parse options
    auto num_adds = result["addresses"].as<int>();
    auto space = result["space"].as<int>();
    auto days = result["days"].as<int>();

// perform address generation:
// First iterate through # of days
    auto counter = 0;
    for (int i=1; i < days+1; i++){

        // for each day, we generate a list of orders
        std::ofstream file;
        std::string filename("day" + std::to_string(i));
        std::string path("..\\Delivery Truck Simulation Data\\Orders\\");
        file.open(path + filename + ".dat");

        for (int j = 0; j < num_adds; j++) {
        counter++;
        std::cout << "count: " << counter << "\n";
        TravelingSalesman::Address addy = generateAddress(space, i); // passing current day as offset
        file << addy.to_string() << "\n";
        }

        file.close();
        std::cout << "Generated Deliveries for Day: " + std::to_string(i) + "!\n";
    }

        std::cout << "Delivery Generations Successful!\n\n";
        return 0;
}