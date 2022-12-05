#include "cxxopts.hpp"
#include "traveling_salesman.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <fstream>

bool is_prime(int num){
  // returns true/false if number is/not prime
  // loop from 2 to half of the input and checks
  // if num is divisible by i. 
  for (int i=2; i<= num/2; i++){
    if ((num % i) == 0){
    return false;
    }
  }
  return true;
}
void nextprime(int& cur_prime){
    // if current prime is 2, set to 3
    if (cur_prime == 2){
      cur_prime = 3;
    } else{
      // else, loop through odd numbers 
      // and return next prime number
      cur_prime += 2;
      while(is_prime(cur_prime) == false){
        cur_prime += 2;
      }
    } 
  }


  std::random_device rd; //obtain a random number hardware
  std::mt19937 gen(rd()); // seed the generator

/**
 * @brief generates random integer between low-high (inclusive)
 * */ 
int random(int low, int high){

    std::uniform_int_distribution<> dist(low, high); // define range
    return dist(gen); // generats random number
}

/**
 * @brief generates Address Object w/random coordinates and delivery date.
 * @param keyword generates "random" or "primes" coordinate points Address Object. 
 * @param space defines space of x-y coordinate system.
 * */ 
TravelingSalesman::Address generateAddress(std::string& keyword, int& space, int& offset){
        int i = random(0, space);
        int j = random(0, space);
        int delivery_by = random(1+offset, 7+offset);
        // only hub can have coordinates (0, 0)
        while ((i+j) == 0){
            int j = random(0, space);
            int i = random(0, space);
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

    // primes only keyword option
    // options.add_options()
    //     ("primes","primes keyword",
    //     cxxopts::value<std::string>()->default_value("random"));
    // options.parse_positional({"primes"});

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
    std::string keyword("woddle");  // delete this if sure we won't incoperate prime stuff in report
    
    // // catch invalid keywords
    // if ((keyword != "primes") && (keyword != "random")){
    //   std::cerr << "Invalid positional argument:\n\b"
    //     << keyword << "\n\tuse 'random' or 'primes' positional arguments only!";
    //   return 0;
    // }

// perform address generation:
// First iterate through # of days
  for (int i=1; i < days+1; i++){

    // for each day, we generate a list of orders
    std::ofstream file;
    std::string filename("day" + std::to_string(i) + ".dat");
    std::string path("..\\Delivery Truck Simulation Data\\Orders\\");
    file.open(path + filename + ".txt");

    for (int j = 0; j < num_adds; j++) {
      TravelingSalesman::Address addy = generateAddress(keyword, space, i); // passing current day as offset
      file << addy.to_string() << "\n";
    }

    file.close();
    std::cout << "Generated Deliveries for Day: " + std::to_string(i) + "!\n";
  }

    std::cout << "Delivery Generations Successful!\n\n";
    return 0;
}