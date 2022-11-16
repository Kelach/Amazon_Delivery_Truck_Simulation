/**
 * traveling_salesman.h
 * 
 * Address Class
 * Address List Class
 * Route
 * 
 * Header file for Traveling Salesman Project library
*/    
#ifndef TRAVELLING_SALESMAN_H
#define TRAVELLING_SALESMAN_H
#include <vector>

namespace TravelingSalesman {

    /**
     * @class Address
     * @brief Represents a single destination along a traveling salesman's route.
    */
    class Address {
    private:
        int i, j, deliver_by;
    public:
        /**
         * @brief Constructor for Address class.
         * @param i horizontal coordinate of address in arbitrary units
         * @param j vertical coordinate of address in arbitrary units
         * @param deliver_by (WIP) number of days after day 0 by which the order must be fulfilled
        */
        Address(int i, int j, int deliver_by);
        /**
         * @brief Destructor for Address class.
        */
        ~Address();

        /**
         * @brief Calculates the distance from this Address to other.
         * 
         * Note that this function could be implemented to return the Cartesian birds-eye distance or Manhattan distance, depending on what best suits the road layout in your hypothetical region.
         * 
         * @param other address to which distance is computed
         * @returns magnitude of Cartesian or Manhattan distance
        */
        double distance(const Address& other);
            
    };
    /**
     * @class AddressList
     * @brief Holds a vector of Addresses
    */
    class AddressList{
        private:
            std::vector<Address> address_list;
        public:
        AddressList();
        /**
         * @brief Constructor for AddressList class.
         * @param address_list vector of Object type "Address"
        */
        AddressList(std::vector<Address> address_list);
        /**
         * @brief Destructor for AddressList class.
        */
        ~AddressList();
        /**
         * @brief Appends a new Address object
         * @param new_address New Address object to be appended
         * @returns None
        */
        void add_address(Address new_address);
        /**
         * @brief Calculates distance one has to visit all addresses in order
         * @returns Total distance
        */
        double length();
        /**
         * @brief Calculates distance one has to visit all addresses in order
         * @param main the Address (relative origin point) from which the closest address is determined
         * @returns Address closest to input Addresss
        */
        Address index_closest_to(Address main);
    };
    /**
     * @todo Define attributes of AddressList class (Done I think)
     * 
     * @todo Define attributes of Route class
    */
}


#endif