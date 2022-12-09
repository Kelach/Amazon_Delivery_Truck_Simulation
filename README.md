# Amazon Delivery Truck Simulation

Ashton Cole, Hanna Butt, Kelechi Emeruwa

Fall 2022

## Introduction

Welcome to our COE 322 final project! We chose to solve the Traveling Salesman Problem. We also implemented a simulation of a delivery company dividing orders between delivery trucks across several days. 

## Navigation

There are many files and folders in our directory, so we created a guide to navigating through.

### Quick Links

- [Report/Report.pdf](/Report/Report.pdf) final report
- [src/traveling_salesman.cpp](/src/traveling_salesman.cpp) library implementing solutions to Traveling Salesman Problem
- [src/tester.cpp](/src/tester.cpp) scripts testing functionality of Traveling Salesman library
- [src/deliveries_generator.cpp](/src/deliveries_generator.cpp) script randomly generating orders for simulations
- [src/delivery_truck_simulation.cpp](/src/delivery_truck_simulation.cpp) main simulation; takes in orders and outputs route assignments and status reports
- [src/experimental.cpp](/src/experimental.cpp) experimental simulation; takes in orders and outputs backlog data

### Folder Structure

- [dataout/](/dataout/) output of our initial tests. Contains automatically generated TikZ commands to generate figures in our final report
- [Delivery Truck Simulation Data/](/Delivery%20Truck%20Simulation%20Data/) all inputs and outputs associated with our main simulation
    - [dat/](/Delivery%20Truck%20Simulation%20Data/dat/) simple whitespace-delimited files of intermediate and optimized routes
    - [Jobs/](/Delivery%20Truck%20Simulation%20Data/Jobs/) formated .txt files to distribute to delivery truck drivers
    - [Orders/](/Delivery%20Truck%20Simulation%20Data/Orders/) simple whitespace-delimited files of orders input into the simulation
    - [Statuses/](/Delivery%20Truck%20Simulation%20Data/Statuses/) daily status reports sent to management for analytics
    - [tikz/](/Delivery%20Truck%20Simulation%20Data/tikz/) automatically generated TikZ commands to generate figures in our final report
- [Experimental/](/Experimental/) all inputs and outputs associated with our experimental simulation
    - [datain/](/Experimental/datain/) simple whitespace-delimited files of orders input into the simulation
    - [dataout/](/Experimental/dataout/) simple whitespace-delimited files of simulation results
- [Report/](/Report/) our final report and all of the scripts and resources used to generate it with LaTeX
- [src/](/src/) contains all libraries, header files, scripts, and binaries