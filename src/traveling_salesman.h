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

#include <string>
using std::string;

namespace TravelingSalesman {
    
    /**
     * @brief Returns current time as string for use in file names.
     * @returns string in format YYYYMMDDHHMMSS
    */
    string get_now();

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
        
        /**
         * @brief equality operator of Address Objects
         * @param rhs "right-hand side" address Object to be compared
         * @returns True if Objects are equal (same cordinates and delivery date)
        */
        bool operator==(const Address& rhs);
        
        /**
         * @brief accessor method to retrieve i,j coordinates of an Address
         * @returns vector with i,j coordinates (in respective order)
        */
        std::vector<int> get_coords();
        /**
         * @brief displays the cartesian coordinates of an Address point
        */
        void display();
    };
    /**
     * @class AddressList
     * @brief Holds a vector of Addresses
    */
    class AddressList{
        protected:
        std::vector<Address> address_vec;
        public:
        /**
         * @brief Default constructor for AddressList class
        */
        AddressList();

        /**
         * @brief Parameterized constructor for AddressList class
         * @param address_vec vector of Object type "Address"
        */
        AddressList(std::vector<Address> address_vec);

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
         * @brief accessor method for address_vec vector length
         * @returns length of vector address_vec
        */
        int size();

        /**
         * @brief accessor method for address_vec (0-indexed)
         * @param i index of address
         * @returns address Object corresponding to index
        */
        Address at(int i);

        /**
         * @brief Locates closest Address nearby
         * @param main Address (relative origin point) from which the closest address is determined
         * @returns index of Address closest to "main" Addresss
        */
        int index_closest_to(Address main);

        /**
         * @brief removes ith Address from address_vec
         * @param i 0-based index at which the Address is located 
         * @returns Address removed from address_vec
        */
        Address pop(int i);

        /**
         * @brief Displays a row of all cartesian points in an AddressList object
        */
        void display();

        /**
         * @brief Returns vector of AddressList.
         * @returns Address vector of addresses in AddressList, in order.
        */
        std::vector<Address> get_vec();
        
        /**
         * @brief Reverse order of given range of elements in a vector
         * @param i starting 0-based index of reverse range
         * @param j ending 0-based index of reverse range
         * @param byref if true, the modified vector will take the place current address_vec, 
         * otherwise the current_vec will not be updated to the modified vector
         * @returns Modified Address vector (byref=false) or empty vector (byref=true)
        */
        std::vector<Address> reverse(int i, int j, bool byref=false);


    };



    /**
     * @class Route
     * @brief AddressList with a hub Address.
    */
    class Route : public AddressList {
        private:
        Address hub;
        public:

        /**
         * @brief Paramaterized constructor for Route class.
         * @param address_list Address vector of delivery addresses.
         * @param hub Address of base station.
        */
        Route(std::vector<Address> address_vec, Address hub);

        /**
         * @brief Paramaterized constructor for Route class.
         * @param address_vec AddressList of delivery addresses.
         * @param hub Address of base station.
        */
        Route(const AddressList& address_list, Address hub);

        /**
         * @brief Destructor for Route class.
        */
        ~Route();
        
        /**
         * @brief Accessor method for Route hub
         * @returns The hub (Address Object) of the Route
        */
        Address get_hub();

        /**
         * @brief Constructs new route based on greedy method algorithm.
         * 
         * Iteratively caculates the next shortest address until all addresses have been reached starting at the hub.
         * 
         * @returns newly constructed Route with same starting hub
        */
        Route greedy_route();
       
        /**
         * @brief Uses the opt-2 heuristic to construct a new (shorter) route. 
         * 
         * See https://en.wikipedia.org/wiki/2-opt for more on the heuristic.
         * 
         * @returns Route Object.
        */
        Route opt2();

        /**
         * @brief Swaps segment of Route with the segments of another Route
         * @param route2 Route to be swapped with
         * @param i Starting index of route 1 segment
         * @param j Ending index of route 1 segment
         * @param n Starting index of route 2 segment
         * @param m Ending index of route 2 segment
         * @see https://en.wikipedia.org/wiki/2-opt for more on the heuristic.
         * 
         * @returns None
        */         
        void swap(Route& route2, int i, int j, int n, int m);
        
        /**
         * @brief Uses the opt-2 heuristic to optimize TWO Route Objects simeltaneously 
         * 
         * @see https://en.wikipedia.org/wiki/2-opt for more on the heuristic.
         * 
        */        
        void multi_opt2(Route& path2);
        
        /**
         * @brief Displays a row of all cartesian coordinate points within a given Route 
        */
        void display();

        /**
         * @brief Calculates distance needed starting from hub to reach all addresses and return back to hub.
         * @returns Total distance
        */
        double length();
        
        /**
         * @brief Writes the Route to a .dat file.
         * 
         * Creates a matrix with rows corresponding to each Address and columns representing the i and j coordinates. The first and last row are the hub, while the coordinates in between are the Address objects in the AddressList, in order.
         * 
         * @param fname name of the file
        */
       void to_dat(string fname);

        /**
         * @brief Writes the Route to a .dat file.
         * 
         * Creates a matrix with rows corresponding to each Address and columns representing the i and j coordinates. The first and last row are the hub, while the coordinates in between are the Address objects in the AddressList, in order. By default, the file name is in the format yyyymmddhhmmss.dat
        */
       void to_dat();

       /**
         * @brief Writes the Route to a .txt file to TikZ specification, for use in LaTeX.
         * @param fname name of the file
        */
       void to_tikz(string fname);

       /**
         * @brief Writes the Route to a .txt file to TikZ specification, for use in LaTeX.
         * 
         * By default, file name is in the format yyyymmddhhmmss.tikz
        */
       void to_tikz();
    };

    /**
     * @todo use opt2 heuristic for multipath problem
     * @todo 
     * @todo  
     * @todo  
    */
}


#endif