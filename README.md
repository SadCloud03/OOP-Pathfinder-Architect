## Practice of coding skills by Making an OOP Pathfinding System

### About 
This project is a secondary evolution of the original maze. The focus here was to transition from procedural programming to Object-Oriented Programming (OOP), encapsulating logic into distinct classes for better scalability and cleaner code.

## This is a practice of software architecture, class encapsulation, and pathfinding logic.

### Proyect Structure
* /Clases: Contains the core logic.

   * Mapa: Handles grid generation, manual/random obstacle placement, and memory management.

   * CalculadoraDeRutas_BFS: Implements the A* Search Algorithm within a class scope to find the  most efficient route.

* /functions: Decoupled utility functions for UI rendering and map visualization.

* main.cpp: The entry point that orchestrates the interaction between the User, the Map, and the Pathfinding engine.

### Requirements
* **C++11 Compiler or higher**: (MinGW, GCC, or Clang) — Necessary for the Node struct initialization and memory management.

* **Standard Template Library (STL)**: The project relies on <queue> for the A* Priority Queue and <vector> for path tracking.

* **Operating System**: 
    * Linux/macOS: Uses system("clear") for smooth animations.

    * Windows: You may need to change system("clear") to system("cls") in the code for the best experience.

### Features
* **Dynamic Map Interaction**: Add or remove obstacles (Stones, Water, Buildings) manually or randomly.
* **Encapsulated A Solver**: The calculation engine is separated from the map data, allowing for modular updates.
* **Smart Coordinate System**: Automatic indexing for rows and columns for easier user interaction.
* **Real-time Path Visualization**: Animates the solution from the destination back to the origin.

### Setup & Execution 
1. **Clone the repo**
```bash
git clone https://github.com/SadCloud03/OOP-Pathfinder-Architect.git
cd OOP-Pathfinder-Architect
```

2. **Compile the project**
```bash
g++ main.cpp Clases/*.cpp functions/*.cpp -o oop_pathfinder.exe
```

3. **Run the application**
```bash
./oop_pathfinder.exe
```
