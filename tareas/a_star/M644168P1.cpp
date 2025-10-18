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

bool DEBUG = true;

struct Coord {
  int x;
  int y;
  
  bool operator==(const Coord& other) const {
    return x == other.x && y == other.y;
  }
  
  bool operator!=(const Coord& other) const {
    return !(*this == other);
  }
  
  bool operator<(const Coord& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};

struct Node {
  Coord coord;
  int g;  // Costo desde el inicio
  int h;  // Heurística (distancia estimada al final)
  int f;  // f = g + h
  Node* parent;
  
  Node(Coord c, int g_cost, int h_cost, Node* p = nullptr) 
    : coord(c), g(g_cost), h(h_cost), f(g_cost + h_cost), parent(p) {}
};

// Función para calcular la heurística (distancia Euclidiana)
int heuristic(const Coord& a, const Coord& b, double heuristic_factor = 1.0) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return (heuristic_factor * sqrt(dx * dx + dy * dy) * 10); // Multiplicar por 10 para mantener enteros
}

// Función para verificar si una coordenada es válida
bool isValid(const Coord& coord, int size = 10) {
  return coord.x >= 0 && coord.x < size && coord.y >= 0 && coord.y < size;
}

// Función para verificar si una coordenada es un obstáculo
bool isObstacle(const Coord& coord, const std::vector<Coord>& obstacles) {
  return std::find(obstacles.begin(), obstacles.end(), coord) != obstacles.end();
}

// Función para calcular el costo de movimiento entre dos coordenadas adyacentes
int getMovementCost(const Coord& from, const Coord& to) {
  int dx = abs(to.x - from.x);
  int dy = abs(to.y - from.y);
  
  // Si es movimiento diagonal (ambos dx y dy son 1)
  if (dx == 1 && dy == 1) {
    return 14; // sqrt(2) * 10, aproximado a entero
  } else {
    return 10; // Movimiento cardinal
  }
}

// Función para leer y validar una coordenada
int readValidCoordinate(const std::string& prompt, const std::string& coordinate_name, int size = 10) {
  int value;
  while (true) {
    std::cout << prompt;
    if (!(std::cin >> value)) {
      std::cout << "Error: Entrada inválida para " << coordinate_name << ". Por favor, ingrese un número entero.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }
    
    if (value < 0 || value >= size) {
      std::cout << "Error: " << coordinate_name << " debe estar entre 0 y " << (size - 1) 
                << " (inclusive). Ingrese de nuevo: " << value << " es inválido.\n";
      continue;
    }
    
    break;
  }
  return value;
}

// Función para leer y validar una coordenada completa
Coord readValidCoord(const std::string& coord_name, const std::vector<Coord>& obstacles = {}, bool checkObstacles = false) {
  Coord coord;
  while (true) {
    coord.x = readValidCoordinate("x: ", "x de " + coord_name);
    coord.y = readValidCoordinate("y: ", "y de " + coord_name);
    
    if (checkObstacles && isObstacle(coord, obstacles)) {
      std::cout << "Error: La coordenada (" << coord.x << ", " << coord.y 
                << ") está en un obstáculo. Ingrese una coordenada diferente.\n";
      continue;
    }
    
    break;
  }
  return coord;
}

// Función para leer el factor de heurística
double readHeuristicFactor() {
  double factor;
  while (true) {
    std::cout << "\nFactor de heurística (valor que altera h): ";
    if (!(std::cin >> factor)) {
      std::cout << "Error: Entrada inválida para el factor de heurística. Por favor, ingrese un número.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }
    
    if (factor <= 0) {
      std::cout << "Error: El factor de heurística debe ser mayor a 0. Ingrese de nuevo: " << factor << " es inválido.\n";
      continue;
    }
    
    break;
  }
  return factor;
}

// Función para obtener vecinos válidos
std::vector<Coord> getNeighbors(const Coord& coord, const std::vector<Coord>& obstacles) {
  std::vector<Coord> neighbors;
  // Movimientos cardinales (costo 10) y diagonales (costo 14, aproximadamente sqrt(2)*10)
  std::vector<Coord> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},          // Cardinales: arriba, derecha, abajo, izquierda
    {1, 1}, {1, -1}, {-1, -1}, {-1, 1}         // Diagonales: diagonal arriba-derecha, diagonal abajo-derecha, etc.
  };
  
  for (const Coord& dir : directions) {
    Coord neighbor = {coord.x + dir.x, coord.y + dir.y};
    if (isValid(neighbor) && !isObstacle(neighbor, obstacles)) {
      neighbors.push_back(neighbor);
    }
  }
  
  return neighbors;
}

// Función para reconstruir el camino
std::vector<Coord> reconstructPath(Node* node) {
  std::vector<Coord> path;
  while (node != nullptr) {
    path.push_back(node->coord);
    node = node->parent;
  }
  std::reverse(path.begin(), path.end());
  return path;
}

// Algoritmo A*
std::vector<Coord> a_star(const Coord& start, const Coord& goal, 
                         const std::vector<Coord>& obstacles, double heuristic_factor = 1.0) {
  if (DEBUG) {
    std::cout << "Iniciando algoritmo A*..." << std::endl;
  }
  
  // Verificar que las coordenadas sean válidas
  if (!isValid(start) || !isValid(goal)) {
    throw std::invalid_argument("Coordenadas de inicio o final inválidas");
  }
  
  if (isObstacle(start, obstacles) || isObstacle(goal, obstacles)) {
    throw std::invalid_argument("El punto de inicio o final está en un obstáculo");
  }
  
  // Estructuras para el algoritmo
  std::priority_queue<Node*, std::vector<Node*>, 
                     std::function<bool(Node*, Node*)>> openSet(
    [](Node* a, Node* b) { return a->f > b->f; });
  std::set<Coord> closedSet;
  std::set<Coord> openSetCoords;
  std::vector<Node*> allNodes; // Para gestión de memoria
  
  // Crear nodo inicial
  Node* startNode = new Node(start, 0, heuristic(start, goal, heuristic_factor));
  openSet.push(startNode);
  openSetCoords.insert(start);
  allNodes.push_back(startNode);
  
  while (!openSet.empty()) {
    Node* current = openSet.top();
    openSet.pop();
    openSetCoords.erase(current->coord);
    
    if (DEBUG) {
      std::cout << "Procesando nodo: (" << current->coord.x << ", " << current->coord.y 
                << ") f=" << current->f << " g=" << current->g << " h=" << current->h << std::endl;
    }
    
    // Si llegamos al objetivo
    if (current->coord == goal) {
      if (DEBUG) {
        std::cout << "¡Objetivo encontrado!" << std::endl;
      }
      std::vector<Coord> path = reconstructPath(current);
      
      // Limpiar memoria
      for (Node* node : allNodes) {
        delete node;
      }
      
      return path;
    }
    
    closedSet.insert(current->coord);
    
    // Explorar vecinos
    std::vector<Coord> neighbors = getNeighbors(current->coord, obstacles);
    for (const auto& neighbor : neighbors) {
      if (closedSet.find(neighbor) != closedSet.end()) {
        continue;
      }
      
      int tentative_g = current->g + getMovementCost(current->coord, neighbor);
      
      // Si el vecino no está en el open set o encontramos un mejor camino
      if (openSetCoords.find(neighbor) == openSetCoords.end()) {
        Node* neighborNode = new Node(neighbor, tentative_g, 
                                     heuristic(neighbor, goal, heuristic_factor), current);
        openSet.push(neighborNode);
        openSetCoords.insert(neighbor);
        allNodes.push_back(neighborNode);
      }
    }
  }
  
  // Limpiar memoria
  for (Node* node : allNodes) {
    delete node;
  }
  
  // No se encontró camino
  throw std::runtime_error("No se encontró un camino válido");
}

// Función para visualizar el tablero
void printTabla(const std::vector<Coord>& path, const std::vector<Coord>& obstacles, 
                const Coord& start, const Coord& goal, int size = 10) {
  std::cout << "\n=== TABLERO 10x10 ===\n";
  std::cout << "I = Inicio, F = Final, X = Obstáculo, * = Ruta\n\n";
  
  // Crear matriz para el tablero
  std::vector<std::vector<char>> tabla(size, std::vector<char>(size, '.'));
  
  // Marcar obstáculos
  for (const auto& obs : obstacles) {
    if (isValid(obs, size)) {
      tabla[obs.y][obs.x] = 'X';
    }
  }
  
  // Marcar inicio y final
  tabla[start.y][start.x] = 'I';
  tabla[goal.y][goal.x] = 'F';
  
  // Marcar ruta (sin sobrescribir inicio y final)
  for (const auto& coord : path) {
    if (coord != start && coord != goal && isValid(coord, size)) {
      tabla[coord.y][coord.x] = '*';
    }
  }
  
  // Imprimir tablero
  std::cout << "   ";
  for (int i = 0; i < size; i++) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  
  for (int y = 0; y < size; y++) {
    std::cout << y << "  ";
    for (int x = 0; x < size; x++) {
      std::cout << tabla[y][x] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main() {
  try {
    int num_obst = 4;
    Coord ini, fin;
    std::vector<Coord> obst(num_obst);
    double heuristic_factor = 1.0;

    std::cout << "=== ALGORITMO A* PARA RUTA MÁS CORTA ===\n";
    std::cout << "Tablero: 10x10 (coordenadas de 0 a 9)\n\n";

    // Entrada del nodo inicial
    std::cout << "Nodo inicial:\n";
    ini = readValidCoord("nodo inicial");

    // Entrada del nodo final
    std::cout << "\nNodo final:\n";
    fin = readValidCoord("nodo final");
    
    // Verificar que inicio y final no sean iguales
    while (ini == fin) {
      std::cout << "Error: El nodo inicial y final no pueden ser iguales. Ingrese un nodo final diferente.\n";
      std::cout << "Nodo final:\n";
      fin = readValidCoord("nodo final");
    }

    // Entrada de obstáculos
    std::cout << "\nObstáculos (4 obstáculos):\n";
    for (int i = 0; i < num_obst; i++) {
      Coord temp_obst;
      while (true) {
        std::cout << "Obstáculo " << (i + 1) << ":\n";
        temp_obst = readValidCoord("obstáculo " + std::to_string(i + 1));
        
        // Verificar que el obstáculo no esté en inicio o final
        if (temp_obst == ini || temp_obst == fin) {
          std::cout << "Error: El obstáculo no puede estar en la posición inicial o final. Ingrese una coordenada diferente.\n";
          continue;
        }
        
        // Verificar que no haya obstáculos duplicados
        bool duplicate = false;
        for (int j = 0; j < i; j++) {
          if (obst[j] == temp_obst) {
            duplicate = true;
            break;
          }
        }
        
        if (duplicate) {
          std::cout << "Error: Ya existe un obstáculo en esa posición. Ingrese una coordenada diferente.\n";
          continue;
        }
        
        break;
      }
      obst[i] = temp_obst;
    }

    // Entrada del factor de heurística
    heuristic_factor = readHeuristicFactor();

    if (DEBUG) {
      std::cout << "\n=== INFORMACIÓN DE ENTRADA ===\n";
      std::cout << "Inicio: (" << ini.x << ", " << ini.y << ")\n";
      std::cout << "Final: (" << fin.x << ", " << fin.y << ")\n";
      std::cout << "Factor de heurística: " << heuristic_factor << "\n";
      std::cout << "Obstáculos:\n";
      for (int i = 0; i < num_obst; i++) {
        std::cout << "  " << (i + 1) << ": (" << obst[i].x << ", " << obst[i].y << ")\n";
      }
      std::cout << "\n";
    }

    // Ejecutar algoritmo A*
    std::vector<Coord> path = a_star(ini, fin, obst, heuristic_factor);

    // Mostrar resultados
    std::cout << "\n=== RESULTADO ===\n";
    std::cout << "Ruta encontrada con " << path.size() << " pasos:\n";
    for (size_t i = 0; i < path.size(); i++) {
      std::cout << "  " << i << ": (" << path[i].x << ", " << path[i].y << ")";
      if (i < path.size() - 1) {
        std::cout << " ->";
      }
      std::cout << "\n";
    }

    // Visualizar tablero
    printTabla(path, obst, ini, fin);

  } catch (const std::exception& e) {
    std::cout << "\nERROR: " << e.what() << std::endl;
    std::cout << "Por favor, verifique las entradas y vuelva a intentar.\n";
    return 1;
  }

  return 0;
}
