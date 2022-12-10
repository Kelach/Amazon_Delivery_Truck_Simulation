/**
 * Ashton C, Hannah B, Kelechi E,
 * traveling_salesman.cpp
 * 
 * Function definition file for Traveling Salesman Project library
*/

#include "traveling_salesman.h"   
#include <iostream>  
#include <fstream>
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
using std::string;

using namespace TravelingSalesman;


string TravelingSalesman::get_now() {
    time_t current_time;
    tm* current_tm;
    char buff[50];
    time(&current_time);
    current_tm = localtime(&current_time);
    strftime(buff, sizeof(buff), "%Y%m%d%H%M%S", current_tm);
    string ret(buff);
    return ret;
}

// Address Class Methods

Address::Address(int i, int j, int deliver_by) : i(i), j(j), deliver_by(deliver_by) {};
Address::~Address(){};

double Address::distance(const Address& other){
    //Cartesian distance
    return sqrt( (i-other.i)*(i - other.i) + (j-other.j)*(j-other.j) ) ;
    
    //Manhattan distance
    //return abs(i-other.i) + abs(j-other.j);
};

// not very robust for detecting duplicate addresses
bool Address::operator==(const Address& rhs){
    return (rhs.i==i && rhs.j==j);
}

std::vector<int> Address::get_coords(){
    return std::vector<int> {i, j};
}

int Address::get_deliver_by() {
    return deliver_by;
}

void Address::set_deliver_by(int deliver_by) {
    this->deliver_by = deliver_by;
}

void Address::display(){
    std::cout << "(" << i << ", " 
        << j << ") ";
}

string Address::to_string() {
    return std::to_string(i) + " " + std::to_string(j) + " " + std::to_string(deliver_by);
}

// End of Address Class Methods

// AddressList Class Methods
AddressList::AddressList(){}; 
AddressList::AddressList(std::vector<Address> address_vec) : address_vec(address_vec){}
    
AddressList::~AddressList(){};

void AddressList::add_address(Address new_address){
    // Checks if address already current exists
    for (Address addy : address_vec){
        if (addy == new_address){
            // If the order is duplicate, it may still have an earlier deliver_by date. In that case, both orders should be delivered on the earlier date.
            if (new_address.get_deliver_by() < addy.get_deliver_by()) {
                addy.set_deliver_by(new_address.get_deliver_by());
            }
            return;
        }
    }
    address_vec.push_back(new_address);
}

Address AddressList::remove_least_priority() {
    Address to_remove = address_vec.at(0);
    int r = 0;

    for (int i = 1; i < address_vec.size(); i++) {
        if (to_remove.get_deliver_by() < address_vec.at(i).get_deliver_by()) {
            to_remove = address_vec.at(i);
            r = i;
        }
    }

    address_vec.erase(address_vec.begin() + r);
    return to_remove;
}

void AddressList::display(){
    for (Address& addy : address_vec){
        addy.display();
    }
}

double AddressList::length(){

    // for each address, we calculate the distance to next address.
    // (except for the last address).
    double total_distance = 0;
    for (int i=0;i < address_vec.size();i++){
        if  (i != address_vec.size()-1){
            Address current_address = address_vec.at(i);
            Address next_address = address_vec.at(i+1);
            total_distance += current_address.distance(next_address);
        }
    }

    return total_distance;
}
int AddressList::size(){
    return address_vec.size();
}
Address AddressList::at(int i){
    return address_vec.at(i);
}
int AddressList::index_closest_to(Address main){
    double minDistance = pow(2, 32)-1; // large integer number
    int minIndex = 0;
    // for each element (under given condition), 
    // updates minDistance and minIndex
    for (int i=0;i<address_vec.size();i++){
        Address addy = address_vec.at(i);
        
        if ( ((addy==main)==false) 
            && (main.distance(addy) < minDistance)){
            minIndex = i;
            minDistance = main.distance(addy);
            
        } else{
        }
    }

    return minIndex;
}
Address AddressList::pop(int i){
    Address popped_addy = address_vec.at(i);
    address_vec.erase(address_vec.begin()+i);
    return popped_addy;
}

std::vector<Address> AddressList::get_vec() {
    return address_vec;
}

std::vector<Address> AddressList::reverse(int i, int j, bool byref){
    if (byref){
        std::reverse(address_vec.begin()+i, address_vec.begin()+j);
        return {};
    }else{
        std::vector<Address> copy_vec(address_vec);
        std::reverse(copy_vec.begin()+i, copy_vec.begin()+j);
        return copy_vec;
    }

}

AddressList AddressList::from_dat(string fname) {
    AddressList address_list;
    std::ifstream file;
    int i = 0;
    int j = 0;
    int deliver_by = 0;
    file.open(fname);
    // Conveniently, file >> x evaluates to false at the end of the file
    while (file >> i) {
        if (file >> j) {
            if (file >> deliver_by) {
                address_list.add_address(Address(i, j, deliver_by));
            }
        }
    }
    file.close();
    return address_list;
}

void AddressList::to_dat(string fname) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords;
    // Then, write AddressList
    for (Address address : address_vec) {
        coords = address.get_coords();
        file << coords[0] << " " << coords[1] << " " << address.get_deliver_by() << '\n';
    }
    file.close();
}

// End of AddressList Class Methods

// Route Class methods

Route::Route(std::vector<Address> address_vec, Address hub) : AddressList(address_vec), hub(hub) {}

Route::Route(const AddressList& address_vec, Address hub) : AddressList(address_vec), hub(hub) {} // Note that this uses a copy constructor

Route::~Route() {}
Address Route::get_hub(){
    return hub;
}
double Route::length(){
    if (address_vec.size() == 0) return 0;
    AddressList copy(address_vec);
    return copy.length() + hub.distance(address_vec.at(0)) + hub.distance(address_vec.at(address_vec.size()-1));
}
Route Route::greedy_route(){
    AddressList current_list(address_vec);
    AddressList new_list;
    Address we_are_here = hub;
    // this could probably be better implemented with pointers
    while (current_list.size() > 0) {
        int index = current_list.index_closest_to(we_are_here);
        // std::cout << index << std::endl;
        new_list.add_address( current_list.at(index) );
        we_are_here = current_list.pop( index );
    }
    Route new_route(new_list, hub);
return new_route;

}
void Route::opti_opt2(){
    bool found_better = false;
    int vec_size = this->size();
    double current_length = this->length();
    for(int i=0; i <= this->size() - 2; i++) {
        for(int j=i+1; j <= this->size() - 1; j++) {
            // calculating length change
            int length_delta = - this->at(i).distance(this->at((i + 1) % vec_size)) 
            - this->at(j).distance(this->at((j + 1) % vec_size))
            + this->at(i).distance(this->at(j))
            + this->at((i + 1) % vec_size).distance(this->at((j + 1) % vec_size));
            
            if (length_delta < 0) {
                this->reverse(i+1, j+1, true);
                current_length += length_delta;
                found_better = true;
            }
        }
    }
}
Route Route::opt2(){
    AddressList address_list(address_vec);

    double current_length = address_list.length();

    for (int m=1 ; m<address_list.size(); m++){
        for (int n=0; n <= m; n++){
            // reverse list, and update vector if modification
            // yields improvements
            AddressList new_list(address_list.reverse(n, m+1));
            if ( new_list.length() < address_list.length() ){        
                address_list = new_list;
                current_length = new_list.length();
            } 
        }

    }
    Route new_route(address_list, hub);
    return new_route;
}
void Route::multi_opt2(Route& route2){
    std::vector<double> current_distances = {this->length(), route2.length()};

    for (int i=0;i<address_vec.size();i++){
        for (int n=0;n<route2.size();n++){
            for (int j=i+1;j<address_vec.size();j++){
                for (int m=n+1;m<route2.size();m++){
                    //** 4 different scenarios to consider.
                    // 1. no reverse swap
                    // 2. one reverse then swap
                    // 3. other one reverse then swap 
                    // 4. both reverse then swap
                    std::vector<Route> routes_1{Route(address_vec, hub), Route(route2.get_vec(), route2.get_hub())};
                    std::vector<Route> routes_2{Route(address_vec, hub), Route(route2.get_vec(), route2.get_hub())};
                    std::vector<Route> routes_3{Route(address_vec, hub), Route(route2.get_vec(), route2.get_hub())};
                    std::vector<Route> routes_4{Route(address_vec, hub), Route(route2.get_vec(), route2.get_hub())};
                    
                    routes_1[0].swap( routes_1[1], i, j, n, m );
                    
                    routes_2[0].reverse( i, j+1, true );

                    routes_2[0].swap( routes_2[1], i, j, n, m );
                    
                    routes_3[1].reverse(n, m+1, true);
                    routes_3[0].swap( routes_3[1], i, j, n, m );

                    routes_4[0].reverse( i, j+1, true );
                    routes_4[1].reverse( n, m+1, true );
                    routes_4[0].swap( routes_4[1], i, j, n, m );
                    
                    std::vector<double> distances1 = {routes_1[0].length(), routes_1[1].length()};
                    std::vector<double> distances2 = {routes_2[0].length(), routes_2[1].length()};
                    std::vector<double> distances3 = {routes_3[0].length(), routes_3[1].length()};
                    std::vector<double> distances4 = {routes_4[0].length(), routes_4[1].length()};
                    if ((distances1[0] < current_distances[0]) 
                    && (distances1[1] < current_distances[1])){

                        current_distances = {routes_1[0].length(), routes_1[1].length()};
                    }

                    if ((distances2[0] < current_distances[0]) 
                        && (distances2[1] < current_distances[1])){

                        current_distances = {routes_2[0].length(), routes_2[1].length()};
                    }

                    if ((distances3[0] < current_distances[0]) 
                        && (distances3[1] < current_distances[1])){

                        current_distances = {routes_3[0].length(), routes_3[1].length()};
                    }

                    if ((distances4[0] < current_distances[0]) 
                        && (distances4[1] < current_distances[1])){
                            
                        current_distances = {routes_4[0].length(), routes_4[1].length()};
                    }
                }
            }
        }
    }
}
void Route::swap(Route& route2, int i, int j, int n, int m){
    Route new_route1(std::vector<Address>{}, hub);
    Route new_route2(std::vector<Address>{}, route2.get_hub());
    // Route1:
    // retain start
    for (int k=0;k<i;k++){
        if (k < this->size()){
            new_route1.add_address(this->at(k));
        }
    }
    // append range of route2
    for (int k=n;k<m;k++){
        if (k<route2.size()){
            new_route1.add_address(route2.at(k));
        }
    }
    // retain end
    for (int k=j;k<this->size();k++){
        new_route1.add_address(this->at(k));
    }
    // Route2:
    // retain start
    for (int k=0;k<n;k++){
        if (k < route2.size()){
            new_route2.add_address(route2.at(k));
        }
    }
    // append range of route1
    for (int k=i;k<j;k++){
        if (k < this->size()){
            new_route2.add_address(this->at(k));
        }
    }
    // retain end
    for (int k=m;k<route2.size();k++){
        new_route2.add_address(route2.at(k));
    }
    route2 = new_route2;
    address_vec = new_route1.get_vec();

}
void Route::display(){
    hub.display();
    AddressList::display();
    hub.display();
}
void Route::to_dat() {
    to_dat(get_now() + ".dat");
}

void Route::to_dat(string fname) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords = hub.get_coords();
    // First, write hub
    file << coords[0] << " " << coords[1] << " " << hub.get_deliver_by() << '\n';
    // Then, write AddressList
    for (Address address : address_vec) {
        coords = address.get_coords();
        file << coords[0] << " " << coords[1] << " " << address.get_deliver_by() << '\n';
    }
    // Finally, write hub
    coords = hub.get_coords();
    file << coords[0] << " " << coords[1] << " " << hub.get_deliver_by();
    file.close();
}

void Route::to_tikz() {
    to_tikz(get_now() + ".tikz");
}

void Route::to_tikz(string fname, string hub_color, string address_color, string route_color, string route_arrow) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords = hub.get_coords();
    std::vector<int> coords_prev;
    // Add comma to route_arrow for TikZ formatting
    if (route_arrow != "") {
        route_arrow = ", " + route_arrow;
    }
    // First, write hub
    file << "\\draw [" << route_color << route_arrow << "] (" << coords[0] << ", " << coords[1] << ") -- ";
    // Then, write AddressList
    for (Address address : address_vec) {
        coords_prev = coords;
        coords = address.get_coords();
        file << "(" << coords[0] << ", " << coords[1] << ");\n\\filldraw [" << address_color << "] (" << coords_prev[0] << ", " << coords_prev[1] << ") circle (2pt);\n\\draw [" << route_color << route_arrow << "] (" << coords[0] << ", " << coords[1] << ") --";
    }
    // Finally, write hub
    coords_prev = coords;
    coords = hub.get_coords();
    file << "(" << coords[0] << ", " << coords[1] << ");\n\\filldraw (" << coords_prev[0] << ", " << coords_prev[1] << ") [" << address_color << "] circle (2pt);\n\\filldraw [" << hub_color << "] (" << coords[0] << ", " << coords[1] << ") circle (4pt);";
    file.close();
}

void Route::to_job(string fname) {
    std::ofstream file;
    file.open(fname);
    std::vector<int> coords = hub.get_coords();
    // First, write hub
    file << fname << "\n\nToday's Route\n\nStart at hub: " << coords[0] << " " << coords[1] << '\n';
    // Then, write AddressList
    for (Address address : address_vec) {
        coords = address.get_coords();
        file << coords[0] << " " << coords[1] << '\n';
    }
    // Finally, write hub
    coords = hub.get_coords();
    file << "Finish at hub: " << coords[0] << " " << coords[1] << '\n';
    file << "\nStats\n\nLength: " + std::to_string(this->length()) + "\nStops: " + std::to_string(this->size()) + "\n\nHave a nice day! You are ~not~ a corporate wage slave :-)";
    file.close();
}

// End of Route Class Methods