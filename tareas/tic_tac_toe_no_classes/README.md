# Tic Tac Toe sin Clases

## Descripción
Implementación de Tic Tac Toe (Gato) sin usar clases, empleando únicamente funciones y variables globales. El juego incluye una IA con algoritmo minimax que es invencible.

## Características
- ✅ Implementación sin clases (solo funciones globales)
- ✅ IA con algoritmo Minimax (invencible)
- ✅ Validación de entrada con manejo de errores
- ✅ Modo debug para ver el proceso de decisión de la IA
- ✅ Interfaz de usuario amigable
- ✅ Try-catch para manejo robusto de errores

## Estructura del Código

### Variables Globales
- `tablero`: Tablero 3x3 representado como vector de vectores
- `jugador_humano`: Símbolo del jugador ('X')
- `computadora`: Símbolo de la IA ('O')
- `DEBUG`: Flag para modo debug

### Funciones Principales
- `inicializarTablero()`: Inicializa el tablero vacío
- `mostrarTablero()`: Muestra el estado actual del tablero
- `verificarGanador()`: Verifica si hay un ganador
- `esEmpate()`: Verifica si el juego terminó en empate
- `hacerJugada()`: Realiza una jugada en el tablero
- `minimax()`: Algoritmo minimax para IA
- `obtenerMejorJugada()`: Calcula la mejor jugada para la IA
- `obtenerJugadaUsuario()`: Obtiene y valida la jugada del usuario
- `jugar()`: Función principal que ejecuta el juego completo

## Compilación

Usando Make:
```bash
make
```

Manual:
```bash
g++ -Wall -Wextra -std=c++11 -o M644168P1 M644168P1.cpp
```

## Ejecución

Ejecución normal:
```bash
./M644168P1
```

Con modo debug (muestra el proceso de decisión de la IA):
```bash
./M644168P1 --debug
```

Usando Make:
```bash
make run        # Ejecución normal
make debug      # Ejecución con debug
make help       # Mostrar ayuda
```

## Cómo Jugar

1. El jugador usa 'X' y la computadora usa 'O'
2. Ingresa tus jugadas en formato `fila columna` (ej: `0 1`)
3. El tablero se muestra después de cada jugada
4. Gana quien complete 3 en línea (horizontal, vertical o diagonal)
5. La IA con minimax es invencible (solo puedes ganar si juegas perfectamente)

## Ejemplo de Uso

```
=== TIC TAC TOE (sin clases) ===
Eres X, la computadora es O

  0   1   2
0   |   |  
  ---------
1   |   |  
  ---------
2   |   |  

Ingresa tu jugada (fila columna, ej: 0 1): 1 1

  0   1   2
0   |   |  
  ---------
1   | X |  
  ---------
2   |   |  

Turno de la computadora...

  0   1   2
0   |   |  
  ---------
1   | X |  
  ---------
2   |   | O

...
```

## Ventajas de Implementación sin Clases

1. **Simplicidad**: Código más directo y fácil de entender
2. **Menos overhead**: No hay gestión de objetos
3. **Programación funcional**: Enfoque más procedural
4. **C++ tradicional**: Estilo más cercano a C

## Diferencia con Versión con Clases

- **Sin clases**: Variables globales y funciones independientes
- **Con clases**: Encapsulación de datos y métodos en una clase `TicTacToe`

Ambas implementaciones tienen la misma funcionalidad, pero diferentes estilos de programación.

## Autor
M644168P1 - Programación Avanzada
