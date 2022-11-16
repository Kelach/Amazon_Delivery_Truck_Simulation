/**
 * traveling_salesman.cpp
 * 
 * Function definition file for Traveling Salesman Project library
*/

#include <iostream>  
#include "traveling_salesman.h"           
#include <math.h>
using namespace TravelingSalesman;

Address::Address(int i, int j, int deliver_by) : i(i), j(j), deliver_by(deliver_by) {};


// ~Address();

double Address::distance(const Address& other){
    // Cartesian distance
    return sqrt( (i-other.i)^2 + (j-other.j)^2 ) ;
    
    //Manhattan distance
    //return abs(i-other.i) + abs(j-other.j);
};



