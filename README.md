Inventory Management System (C++ Graphics-Based)
This is a simple Inventory Management System built in C++, using graphics.h for a graphical user interface. It allows users to add items, view inventory, buy items, and manage stock in a text-based file storage system.

Features
Graphical User Interface (GUI) built using graphics.h

Add Items: Enter product details such as ID, name, quantity, price, batch number, and expiry date.

View Items: Displays a list of all items in the inventory.

Buy Items: Allows users to purchase items by entering the ID and quantity, updating the inventory accordingly.

Mouse Click Interactions: Users can navigate using mouse clicks on buttons.

Persistent Storage: Inventory data is stored in inventory.txt for future sessions.

How It Works
The program initializes a graphical window.

Users can interact with buttons to perform various inventory management tasks.

Data is stored and retrieved from inventory.txt.

The system checks for duplicate IDs and ensures inventory limits.

Requirements
Turbo C++ (or a compatible graphics environment)

graphics.h library

conio.h, fstream, and iostream

How to Run
Install Turbo C++ and configure BGI for graphics.h.

Compile and run inventory.cpp in Turbo C++.

The graphical window will open with options to Add, View, and Buy Items.
