# A* Algorithm Implementation Explanation

## Overview
This C++ program implements the A* (A-star) pathfinding algorithm to find the shortest path between two points on a 10x10 grid while avoiding obstacles.

## Code Structure Breakdown

### 1. Header and Includes (Lines 1-12)
```cpp
// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <functional>
```

**Purpose**: 
- Author identification and academic integrity statement
- Includes necessary C++ standard libraries:
  - `iostream`: For input/output operations
  - `vector`: For dynamic arrays (path storage, obstacles)
  - `queue`: For priority queue implementation
  - `set`: For closed/open set management
  - `cmath`: For mathematical functions (abs)
  - `algorithm`: For algorithms like reverse and find
  - `functional`: For function objects and lambda expressions

### 2. Debug Flag (Line 13)
```cpp
bool DEBUG = true;
```

**Purpose**: Global flag to control debug output throughout the program. When enabled, provides detailed information about the algorithm's execution process.

### 3. Coordinate Structure (Lines 15-31)
```cpp
struct Coord {
  int x;
  int y;
  
  bool operator==(const Coord& other) const;
  bool operator!=(const Coord& other) const;
  bool operator<(const Coord& other) const;
};
```

**Purpose**: 
- Represents a 2D coordinate point on the grid
- Essential operators for:
  - **Equality (`==`)**: Compare if two coordinates are the same
  - **Inequality (`!=`)**: Opposite of equality
  - **Less than (`<`)**: Required for `std::set` ordering; enables coordinate comparison for set operations

### 4. Node Structure (Lines 33-42)
```cpp
struct Node {
  Coord coord;
  int g;  // Costo desde el inicio
  int h;  // Heurística (distancia estimada al final)
  int f;  // f = g + h
  Node* parent;
  
  Node(Coord c, int g_cost, int h_cost, Node* p = nullptr);
};
```

**Purpose**: Core data structure for the A* algorithm nodes containing:
- **`coord`**: Grid position (x, y)
- **`g`**: Actual cost from start to current node
- **`h`**: Heuristic estimate from current node to goal
- **`f`**: Total estimated cost (g + h) - the key value for A* prioritization
- **`parent`**: Pointer to previous node for path reconstruction

### 5. Heuristic Function (Lines 44-49)
```cpp
int heuristic(const Coord& a, const Coord& b, double heuristic_factor = 1.0) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return (heuristic_factor * sqrt(dx * dx + dy * dy) * 10);
}
```

**Purpose**: 
- Calculates Euclidean distance between two points: `√((x1-x2)² + (y1-y2)²) * 10`
- **Heuristic factor**: Allows tuning of the heuristic's influence
  - Factor = 1.0: Standard A* (optimal if h is admissible)
  - Factor < 1.0: More Dijkstra-like (prioritizes actual cost)
  - Factor > 1.0: More greedy (prioritizes heuristic, faster but potentially suboptimal)
- **Euclidean distance**: Appropriate for diagonal movement capabilities
- **Multiplication by 10**: Maintains integer precision and consistency with movement costs

### 6. Validation Functions (Lines 51-59)
```cpp
bool isValid(const Coord& coord, int size = 10);
bool isObstacle(const Coord& coord, const std::vector<Coord>& obstacles);
```

**Purpose**: 
- **`isValid`**: Ensures coordinates are within the 10x10 grid bounds (0-9)
- **`isObstacle`**: Checks if a coordinate contains an obstacle using `std::find`

### 7. Movement Cost Function (Lines 61-72)
```cpp
int getMovementCost(const Coord& from, const Coord& to) {
  int dx = abs(to.x - from.x);
  int dy = abs(to.y - from.y);
  
  if (dx == 1 && dy == 1) {
    return 14; // sqrt(2) * 10, aproximado a entero
  } else {
    return 10; // Movimiento cardinal
  }
}
```

**Purpose**: 
- Calculates the movement cost between adjacent coordinates
- **Cardinal movements**: Cost of 10 (up, down, left, right)
- **Diagonal movements**: Cost of 14 (approximately √2 × 10 for diagonal paths)
- Ensures accurate pathfinding with proper cost accounting

### 7.1. Input Validation Functions (Lines 74-135)

#### `readValidCoordinate()` Function
```cpp
int readValidCoordinate(const std::string& prompt, const std::string& coordinate_name, int size = 10)
```

**Purpose**: 
- Validates individual coordinate values (x or y)
- **Range validation**: Ensures values are between 0 and (size-1)
- **Input error handling**: Clears buffer and retries on invalid input
- **User-friendly**: Shows specific error messages for different validation failures

#### `readValidCoord()` Function
```cpp
Coord readValidCoord(const std::string& coord_name, const std::vector<Coord>& obstacles = {}, bool checkObstacles = false)
```

**Purpose**: 
- Reads and validates complete coordinate pairs
- **Obstacle checking**: Optional validation to prevent placing items on obstacles
- **Comprehensive validation**: Uses `readValidCoordinate()` for individual values

#### `readHeuristicFactor()` Function
```cpp
double readHeuristicFactor()
```

**Purpose**: 
- Validates the heuristic factor input
- **Range validation**: Ensures factor is greater than 0
- **Input error handling**: Robust error handling for numeric input

### 8. Neighbor Generation (Lines 74-84)
```cpp
std::vector<Coord> getNeighbors(const Coord& coord, const std::vector<Coord>& obstacles) {
  std::vector<Coord> neighbors;
  std::vector<Coord> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},          // Cardinales
    {1, 1}, {1, -1}, {-1, -1}, {-1, 1}         // Diagonales
  };
```

**Purpose**: 
- Generates valid neighboring coordinates for expansion
- **Directions**: 8-directional movement including:
  - **Cardinal**: up, right, down, left (cost: 10)
  - **Diagonal**: up-right, down-right, down-left, up-left (cost: 14)
- **Validation**: Only returns neighbors that are:
  - Within grid bounds (`isValid`)
  - Not blocked by obstacles (`!isObstacle`)

### 9. Path Reconstruction (Lines 86-95)
```cpp
std::vector<Coord> reconstructPath(Node* node) {
  std::vector<Coord> path;
  while (node != nullptr) {
    path.push_back(node->coord);
    node = node->parent;
  }
  std::reverse(path.begin(), path.end());
  return path;
}
```

**Purpose**: 
- Traces back from goal node to start using parent pointers
- **Process**: 
  1. Start from goal node
  2. Follow parent links to start
  3. Reverse the collected coordinates to get start→goal sequence

### 10. A* Algorithm Implementation (Lines 97-179)

#### Setup and Validation (Lines 88-107)
```cpp
std::priority_queue<Node*, std::vector<Node*>, 
                   std::function<bool(Node*, Node*)>> openSet(
  [](Node* a, Node* b) { return a->f > b->f; });
std::set<Coord> closedSet;
std::set<Coord> openSetCoords;
std::vector<Node*> allNodes; // Para gestión de memoria
```

**Data Structures**:
- **`openSet`**: Priority queue prioritizing nodes by lowest f-value (min-heap behavior)
- **`closedSet`**: Set of already processed coordinates
- **`openSetCoords`**: Fast lookup for coordinates in open set
- **`allNodes`**: Memory management for proper cleanup

#### Main Algorithm Loop (Lines 115-160)
```cpp
while (!openSet.empty()) {
  Node* current = openSet.top();
  openSet.pop();
  
  if (current->coord == goal) {
    // Goal found - reconstruct and return path
  }
  
  closedSet.insert(current->coord);
  
  // Explore neighbors
  std::vector<Coord> neighbors = getNeighbors(current->coord, obstacles);
  for (const auto& neighbor : neighbors) {
    // Add new nodes or update existing ones
  }
}
```

**Algorithm Flow**:
1. **Pop best node**: Lowest f-value from open set
2. **Check goal**: If reached, reconstruct path
3. **Mark closed**: Add current coordinate to closed set
4. **Expand neighbors**: For each valid neighbor:
   - Skip if already processed (in closed set)
   - Calculate tentative g-cost using `getMovementCost()` (10 for cardinal, 14 for diagonal)
   - Add to open set if new, or check for better path

#### Memory Management (Lines 132-135, 163-165)
```cpp
for (Node* node : allNodes) {
  delete node;
}
```
**Purpose**: Prevents memory leaks by tracking and deleting all allocated nodes.

### 11. Board Visualization (Lines 183-225)
```cpp
void printBoard(const std::vector<Coord>& path, const std::vector<Coord>& obstacles, 
                const Coord& start, const Coord& goal, int size = 10)
```

**Purpose**: 
- Creates a visual 10x10 grid representation
- **Symbols**:
  - `S`: Start position
  - `G`: Goal position  
  - `X`: Obstacles
  - `*`: Path coordinates
  - `.`: Empty cells
- **Coordinate system**: Y-axis as rows, X-axis as columns

### 12. Main Function (Lines 297-395)

#### Input Collection with Validation Loops (Lines 307-356)
**Purpose**: Gathers user input with comprehensive validation for:
- **Start coordinates**: Initial position (x, y) with range validation
- **Goal coordinates**: Target position (x, y) with range validation and uniqueness check
- **Obstacles**: 4 obstacle positions (x, y pairs) with comprehensive validation
- **Heuristic factor**: Tunable parameter with positive value validation

#### Enhanced Input Validation Features
```cpp
// Example validation for coordinates
int readValidCoordinate(const std::string& prompt, const std::string& coordinate_name, int size = 10) {
  while (true) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
      std::cout << "Error: Entrada inválida para " << coordinate_name << "...\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }
    if (value < 0 || value >= size) {
      std::cout << "Error: " << coordinate_name << " debe estar entre 0 y " << (size - 1) << "...\n";
      continue;
    }
    break;
  }
}
```

**Validation Features**:
- **Range validation**: All coordinates must be between 0-9
- **Input type validation**: Handles non-numeric input gracefully
- **Uniqueness checks**: Prevents overlapping start/goal and duplicate obstacles
- **Obstacle placement validation**: Ensures obstacles don't conflict with start/goal positions
- **Retry loops**: Allows users to correct invalid input without restarting

#### Algorithm Execution (Lines 282-297)
```cpp
std::vector<Coord> path = a_star(ini, fin, obst, heuristic_factor);
// Display results and board
```

**Process**:
1. Execute A* algorithm with user parameters
2. Display found path with step-by-step coordinates
3. Show visual board representation
4. Handle exceptions gracefully

## Algorithm Characteristics

### Time Complexity
- **Best case**: O(b^d) where b is branching factor (now 8 with diagonal movement), d is depth
- **Worst case**: O(b^d) but typically much better than BFS due to heuristic guidance
- **Increased branching factor**: Diagonal movement increases neighbors from 4 to 8 per node

### Space Complexity
- O(b^d) for storing the priority queue and closed set
- Slightly higher due to increased branching factor from diagonal movement

### Optimality
- **Guaranteed optimal** when heuristic is admissible (never overestimates true cost)
- **Euclidean distance is admissible** for diagonal movement capabilities
- **Proper cost accounting**: Cardinal moves cost 10, diagonal moves cost 14 (√2 × 10)

### Completeness
- **Complete**: Will always find a solution if one exists, given sufficient time and memory

### Movement Capabilities
- **8-directional movement**: Up, down, left, right, and four diagonal directions
- **Cost differentiation**: Different costs for cardinal vs diagonal movements reflect real path distances

## Usage Example
1. Run the program
2. Enter start coordinates (e.g., 0, 0)
3. Enter goal coordinates (e.g., 9, 9) 
4. Enter 4 obstacle coordinates
5. Enter heuristic factor (1.0 for optimal, other values for different behaviors)
6. View the optimal path and visual grid representation
