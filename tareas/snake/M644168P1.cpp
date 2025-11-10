/*
Desarrolla el famoso juego snake de los 70tas utilizando C++
- Los movimientos deben suceder con las flechas disponibles en el teclado.
- El tablero tiene una medida de 100 x 100
- Cada 5 segundos debe aparecer alimento y desaparecer 10 segundos después.
- Cada vez que la vibora come crece un segménto, un segménto esta compuesto por
un espacio.
- Si la vibora choca contra las paredes o contra sí misma pierde.
- Utiliza colores y código ascii para pintar el tablero y la vibora.
Objetivo:
El objetivo principal es comer la mayor cantidad de comida (generalmente un
punto o un bloque) para hacer crecer a tu serpiente y obtener el puntaje más
alto posible. Reglas: Movimiento: Controlas a una serpiente que se mueve
constantemente en una dirección. Solo puedes cambiar la dirección hacia arriba,
abajo, izquierda o derecha (nunca puedes retroceder 180 grados de forma
instantánea). Comida: Un trozo de comida aparece aleatoriamente en el campo de
juego. Crecimiento: Cuando la cabeza de la serpiente toca la comida, esta
desaparece, y la serpiente crece un segmento(se hace más larga). El juego
termina (Game Over) cuando la serpiente comete alguna de las siguientes
acciones: Chocar con las paredes: Si la cabeza de la serpiente toca el borde o
el límite del área de juego. Chocarse consigo misma: Si la cabeza de la
serpiente toca cualquier parte de su propio cuerpo (incluyendo la cola).
Recuerda utilizar try y debug, sube tu programa y evidencia utilizando la
nomenclatura estandar.
*/

#include <iostream>

const int BOARD_SIZE = 100;
char board[BOARD_SIZE][BOARD_SIZE];

void fill_board() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = '.';
    }
  }
}

int main() {
  fill_board();
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      std::cout << board[i][j];
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}
