#include "cxxopts.hpp"
#include "traveling_salesman.h"
#include <iostream>
#include <string>
#include <random>
#include <vector>

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
int nextprime(int cur_prime){
  int prime_num = cur_prime;
    // if current prime is 2, set to 3
    if (cur_prime == 2){
      cur_prime = 3;
    } else{
      // else, loop through odd numbers 
      // and return next prime number
      int next_prime = cur_prime + 2;
      while(is_prime(next_prime) == false){
        next_prime += 2;
      }
      cur_prime = next_prime;
    } 
    
    return prime_num;
  }
std::vector<int> generate_primes(int max_num){
  // initalize an empty vector, 
  // find every nextprime that is less
  // than or equal to our max and add to our
  // vector of primes
  std::vector<int> primes = {};
  int prime_num = 2;
  while (max_num >= prime_num){
      primes.push_back(prime_num);
      prime_num = nextprime(prime_num);
  }
  // return vector of primes
  return primes;
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
TravelingSalesman::Address generateAddress(std::string& keyword, int& space, std::vector<int>& primes){
    if (keyword == "random"){
        int i = random(0, space);
        int j = random(0, space);
        int delivery_by = random(1, 7);
        // only hub can have coordinates (0, 0)
        while ((i+j) == 0){
            int j = random(0, space);
            int i = random(0, space);
        }
        // get 2 random ints within range of space
        // and one random int between 1 and 7 for delivery date
        // return Address object
        return TravelingSalesman::Address(i, j, delivery_by);


    } else if (keyword == "primes"){
        // generate random i and j indicies
        int index_i = random(0, primes.size());
        int index_j = random(0, primes.size());
        // get 2 prime ints within range of space
        int i = primes.at(index_i);
        int j = primes.at(index_j);
        int delivery_by = random(1, 7);
        // and one random int between 1 and 7 for delivery date
        // return Address object
        return TravelingSalesman::Address(i, j, delivery_by);

    } else{
        // throw error for invalid keyword
        throw(5);
    }
}
/**
 * @brief generates route with a starting hub at (0, 0)
 * @param keyword generates route with "random" or "primes" coordinate points Addresses
 * @param space defines space of x-y coordinate system.
 * @param address_count # of addresses to generate per route
 * */ 
TravelingSalesman::Route generateRoute(std::string& keyword, int& space, int& address_count){
  if (keyword == "random"){
    std::vector<TravelingSalesman::Address> address_vec{};
    for (int i=0;i<=address_count;i++){
      std::vector<int> primes{};
      // create address and add to vector address vec
      TravelingSalesman::Address new_address = generateAddress(keyword, space, primes);
      address_vec.push_back(new_address);
    }
    return TravelingSalesman::Route(address_vec, TravelingSalesman::Address(0, 0, 0));
  } else if (keyword == "primes"){
    std::vector<TravelingSalesman::Address> address_vec{};
    // generate primes vector
    for (int i=0;i<=address_count;i++){
      // generate vector of primes
      std::vector<int> primes = generate_primes(space);

      // create random addresse co-ords based off of prime vector
      TravelingSalesman::Address new_address = generateAddress(keyword, space, primes);
      address_vec.push_back(new_address);
    }
    return TravelingSalesman::Route(address_vec, TravelingSalesman::Address(0, 0, 0));

  } else{
      std::vector<TravelingSalesman::Address> address_vec{};
      throw(5);
    return TravelingSalesman::Route(address_vec, TravelingSalesman::Address(0, 0, 0));
  }
}


int main(int argc, char **argv){
    //*******declare options*******
    
    // -help option
    cxxopts::Options options
        ("cxxopts", "Commandline options");
    options.add_options()
        ("h,help","usage information");
    
    // # of routes option
    options.add_options()
        ("r,routes","# of routes to generate",
        cxxopts::value<int>()->default_value("5"));

    // # addresses per route
    options.add_options()
        ("a,addresses","# of addresses to generate per route",
        cxxopts::value<int>()->default_value("5"));

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
    auto num_adds = result["addresses"].as<int>();
    auto num_routes = result["routes"].as<int>();
    auto space = result["space"].as<int>();
    auto keyword = result["primes"].as<std::string>();
    
    std::vector<int> vec{};
    for (int i = 0; i < num_adds; i++) {
      generateAddress(keyword, space, vec).display();
    }
    // do for loop 
        // try generateRoute, catch errors
        // each time, make route generation output
        // Route route = generateRoute(keyword, space);
    
    // std::cout << "Generating " << num_routes << " routes" << '\n';
    // // read the positional keyword
    // std::cout << "Found keyword: " << keyword << '\n';

    
    return 0;
}