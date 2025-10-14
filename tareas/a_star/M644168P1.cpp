/*
 * Desarrolla un programa que utilize A *para identificar la ruta más corta
 * entre dos puntos Toma en cuenta una matriz de 10 x 10 como tablero de
 * funcionamiento.Input :
 * - Nodo inicia(x, y)
 * - Nodo final(x, y)
 * - Obstaculo 1, 2, 3, 4
 * - Valor que altera la Heurística h
 * Output: Impresión del grafo indicando la ruta más corta y eficiente
 * Recuerda utilizar, debug, try y lo visto en clase.
 */

#include <iostream>
#include <vector>

bool DEBUG = true;

struct Coord {
  int x;
  int y;
};

bool a_star() { return false; }

int main() {
  int x, y, num_obst = 4;
  Coord ini, fin;
  std::vector<Coord> obst(num_obst);

  // Inicio
  std::cout << "Inicio:\nx: ";
  std::cin >> x;
  std::cout << "y: ";
  std::cin >> y;
  ini = {x, y};

  // Final
  std::cout << "Final:\nx: ";
  std::cin >> x;
  std::cout << "y: ";
  std::cin >> y;
  fin = {x, y};

  // Obstaculos
  std::cout << "Obstaculos:\n";
  for (int i = 0; i < num_obst; i++) {
    printf("%i:\n x: ", i);
    std::cin >> x;
    std::cout << " y: ";
    std::cin >> y;
    obst[i] = {x, y};
  }

  if (DEBUG) {
    std::printf("Calculando ruta mas corta de:\n"
                " Inicio:(%i,%i)\n"
                " Fin:(%i,%i)\n"
                "Con obstaculos:\n",
                ini.x, ini.y, fin.x, fin.y);
    for (int i = 0; i < num_obst; i++) {
      std::printf(" %i:(%i,%i)\n", i, obst[i].x, obst[i].y);
    }
  }
}
