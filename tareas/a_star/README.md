# Algoritmo A* para Ruta Más Corta

## Descripción
Este programa implementa el algoritmo A* para encontrar la ruta más corta entre dos puntos en una matriz de 10x10, evitando obstáculos.

## Características
- **Tablero**: Matriz de 10x10 (coordenadas de 0 a 9)
- **Obstáculos**: Hasta 4 obstáculos configurables
- **Heurística**: Factor configurable que altera la función heurística h
- **Visualización**: Tablero gráfico que muestra la ruta encontrada
- **Manejo de errores**: Validación de entrada con try-catch
- **Debug**: Modo debug para mostrar el proceso del algoritmo

## Entrada
El programa solicita:
1. **Nodo inicial**: Coordenadas (x, y) del punto de partida
2. **Nodo final**: Coordenadas (x, y) del punto de destino
3. **Obstáculos**: 4 obstáculos con sus coordenadas (x, y)
4. **Factor de heurística**: Valor que multiplica la función heurística

## Salida
- Lista de coordenadas que forman la ruta más corta
- Visualización del tablero con:
  - `S` = Punto de inicio
  - `G` = Punto final
  - `X` = Obstáculos
  - `*` = Ruta encontrada
  - `.` = Espacios libres

## Compilación
```bash
g++ -o M644168P1 M644168P1.cpp -std=c++11
```

## Ejecución
```bash
./M644168P1
```

## Ejemplo de uso
```
=== ALGORITMO A* PARA RUTA MÁS CORTA ===
Tablero: 10x10 (coordenadas de 0 a 9)

Nodo inicial:
x: 0
y: 0

Nodo final:
x: 9
y: 9

Obstáculos (4 obstáculos):
Obstáculo 1:
x: 1
y: 1
Obstáculo 2:
x: 2
y: 2
Obstáculo 3:
x: 3
y: 3
Obstáculo 4:
x: 4
y: 4

Factor de heurística (valor que altera h): 1.0
```

## Algoritmo A*
El algoritmo A* utiliza:
- **f(n) = g(n) + h(n)**
  - `g(n)`: Costo real desde el inicio hasta el nodo n
  - `h(n)`: Heurística (distancia Manhattan estimada al objetivo)
  - `f(n)`: Función de evaluación total

- **Estructuras de datos**:
  - Cola de prioridad para nodos abiertos (open set)
  - Conjunto para nodos cerrados (closed set)
  - Gestión automática de memoria

## Factor de Heurística
- **Factor = 1.0**: Algoritmo óptimo (garantiza la ruta más corta)
- **Factor > 1.0**: Algoritmo más rápido pero puede no ser óptimo
- **Factor < 1.0**: Algoritmo más lento pero más preciso

## Manejo de Errores
- Validación de coordenadas dentro del rango [0,9]
- Verificación de que inicio/final no estén en obstáculos
- Manejo de casos sin solución posible
- Validación de entrada con try-catch

## Autor
M644168P1 - Programación Avanzada
