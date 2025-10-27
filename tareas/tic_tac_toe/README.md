# Gato Inteligente - Tic Tac Toe con IA

## Descripción
Este es un programa de gato (tic-tac-toe) donde la computadora utiliza el algoritmo minimax para ser extremadamente inteligente y siempre elegir la mejor jugada posible. La computadora está diseñada para ganar o al menos empatar en cada partida.

## Características
- **IA Inteligente**: Utiliza el algoritmo minimax para evaluar todas las posibles jugadas
- **Debug Mode**: Incluye mensajes de debug para entender las decisiones de la IA
- **Manejo de Errores**: Implementa try-catch para manejar entradas inválidas
- **Validación de Entrada**: Verifica que las coordenadas sean válidas y las casillas estén vacías
- **Interfaz Amigable**: Tablero visual claro y mensajes informativos

## Compilación y Ejecución

### Usando Makefile (Recomendado)
```bash
# Compilar
make

# Compilar con debug
make debug

# Compilar y ejecutar
make run

# Limpiar archivos compilados
make clean
```

### Compilación Manual
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o gato_inteligente gato_inteligente.cpp
```

## Cómo Jugar
1. Ejecuta el programa
2. El tablero se muestra con coordenadas (0,0) hasta (2,2)
3. Ingresa tu jugada como "fila columna" (ej: "0 1")
4. La computadora responderá automáticamente con su mejor jugada
5. El juego termina cuando hay un ganador o empate

## Algoritmo Minimax
La computadora evalúa todas las posibles jugadas futuras:
- **+1**: La computadora gana
- **0**: Empate
- **-1**: El humano gana

La IA siempre elige la jugada que maximiza su puntuación y minimiza la del oponente.

## Debug Mode
Para activar mensajes de debug, cambia la constante `DEBUG` a `true` en el código. Esto mostrará:
- Evaluación de cada casilla posible
- La mejor jugada encontrada por la IA
- Coordenadas de las jugadas realizadas

## Ejemplo de Salida
```
=== GATO INTELIGENTE ===
Eres X, la computadora es O
¡Buena suerte! La computadora es muy inteligente...

Tablero actual:
  0   1   2
0   |   |  
  ---------
1   |   |  
  ---------
2   |   |  

Ingresa tu jugada (fila columna, ej: 0 1): 1 1
Turno de la computadora...
¡La computadora ha ganado! ¡Mejor suerte la próxima vez!
```
