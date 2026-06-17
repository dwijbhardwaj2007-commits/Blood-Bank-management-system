# Blood Bank Management System

A C++ based Blood Bank Management System designed to manage blood donations, blood inventory, and recipient requests efficiently. The project focuses on applying Object-Oriented Programming, STL containers, file handling, and system design concepts such as caching, persistence, and scalability.

## Features

- Donor registration and blood donation management
- Blood inventory tracking
- Blood compatibility checking
- Blood issuance based on compatibility
- Automatic removal of expired blood units
- File-based persistent storage
- Inventory caching using STL vectors for improved performance
- Modular OOP-based architecture

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- STL (Vector, Map, Algorithms)
- File Handling
- Data Structures and Algorithms

## Project Structure

- Core.h – Common utilities and base classes
- Donor.h – Donor management and registration
- Receiver.h – Blood request and compatibility logic
- Inventory.h – Inventory storage and blood unit management
- main.cpp – Program entry point
- donors.txt – Donor records
- inventory.txt – Blood inventory records

## How It Works

1. Donors register and donate blood.
2. Blood units are added to inventory with collection and expiry dates.
3. Recipients request blood units.
4. The system checks blood-group compatibility.
5. Compatible blood units are issued and removed from inventory.
6. Expired blood units are automatically removed.

## Performance Improvements

The inventory is loaded into memory once and stored using STL vectors, reducing repeated file reads and improving runtime performance while maintaining persistence through file storage.

## Future Enhancements

- Waitlist management for pending blood requests
- MySQL database integration
- Multithreading and synchronization using mutexes
- Network-based multi-user support
- GUI/Web Interface

## Learning Outcomes

This project was built to explore:
- OOP design in C++
- File handling and persistence
- STL containers
- Memory management concepts
- Caching and performance optimization
- System design and scalability considerations

## Author

Dwij Bhardwaj
