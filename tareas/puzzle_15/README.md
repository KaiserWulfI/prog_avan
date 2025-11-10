# Puzzle 15 con ncurses

Este proyecto implementa una versión en consola del clásico rompecabezas deslizante 15. El programa genera un tablero de 4x4 con números del 1 al 15 y un espacio vacío. Puedes mover el espacio usando las flechas del teclado o las teclas `W`, `A`, `S`, `D`.

## Requisitos

- Compilador con soporte para C++20 (`g++` recomendado).
- Biblioteca `ncurses` instalada.

En Arch Linux, instala `ncurses` con:

```bash
sudo pacman -S ncurses
```

## Compilación

Usa el `Makefile` incluido:

```bash
cd /home/alex/Work/school/prog_avan/tareas/puzzle_15
make
```

Esto generará el ejecutable `puzzle15`.

## Ejecución

```bash
./puzzle15
```

Controles:

- `↑` / `W`: mover el espacio vacío hacia arriba.
- `↓` / `S`: mover el espacio vacío hacia abajo.
- `←` / `A`: mover el espacio vacío hacia la izquierda.
- `→` / `D`: mover el espacio vacío hacia la derecha.
- `Q`: salir del juego.
- `--debug` o `-d`: habilita mensajes de depuración en la salida estándar de error.

## Depuración

Ejecuta el programa con `./puzzle15 --debug` (o `./puzzle15 -d`) para habilitar mensajes de depuración. Los mensajes se muestran en un panel dentro de la interfaz.

