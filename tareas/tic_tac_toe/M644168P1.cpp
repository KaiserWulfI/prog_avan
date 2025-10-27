#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <string>

bool DEBUG = false;

class TicTacToe {
private:
    std::vector<std::vector<char>> tablero;
    char jugador_humano;
    char computadora;
    
public:
    TicTacToe() : tablero(3, std::vector<char>(3, ' ')), jugador_humano('X'), computadora('O') {}
    
    // Función para mostrar el tablero
    void mostrarTablero() {
        std::cout << "\n";
        std::cout << "  0   1   2\n";
        for (int i = 0; i < 3; i++) {
            std::cout << i << " ";
            for (int j = 0; j < 3; j++) {
                std::cout << tablero[i][j];
                if (j < 2) std::cout << " | ";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "  ---------\n";
        }
        std::cout << "\n";
    }
    
    // Verificar si hay un ganador
    char verificarGanador() {
        // Verificar filas
        for (int i = 0; i < 3; i++) {
            if (tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
                return tablero[i][0];
            }
        }
        
        // Verificar columnas
        for (int j = 0; j < 3; j++) {
            if (tablero[0][j] != ' ' && tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
                return tablero[0][j];
            }
        }
        
        // Verificar diagonales
        if (tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
            return tablero[0][0];
        }
        if (tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
            return tablero[0][2];
        }
        
        return ' '; // No hay ganador
    }
    
    // Verificar si el tablero está lleno (empate)
    bool esEmpate() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tablero[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
    
    // Verificar si una casilla está vacía
    bool esCasillaVacia(int fila, int columna) {
        if (fila < 0 || fila >= 3 || columna < 0 || columna >= 3) {
            return false;
        }
        return tablero[fila][columna] == ' ';
    }
    
    // Hacer una jugada
    bool hacerJugada(int fila, int columna, char jugador) {
        if (!esCasillaVacia(fila, columna)) {
            return false;
        }
        tablero[fila][columna] = jugador;
        return true;
    }
    
    // Algoritmo minimax para la IA
    int minimax(bool esMaximizador) {
        char ganador = verificarGanador();
        
        if (ganador == computadora) {
            return 1; // La computadora gana
        } else if (ganador == jugador_humano) {
            return -1; // El humano gana
        } else if (esEmpate()) {
            return 0; // Empate
        }
        
        if (esMaximizador) {
            int mejorPuntuacion = std::numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (esCasillaVacia(i, j)) {
                        tablero[i][j] = computadora;
                        int puntuacion = minimax(false);
                        tablero[i][j] = ' '; // Deshacer jugada
                        mejorPuntuacion = std::max(mejorPuntuacion, puntuacion);
                    }
                }
            }
            return mejorPuntuacion;
        } else {
            int mejorPuntuacion = std::numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (esCasillaVacia(i, j)) {
                        tablero[i][j] = jugador_humano;
                        int puntuacion = minimax(true);
                        tablero[i][j] = ' '; // Deshacer jugada
                        mejorPuntuacion = std::min(mejorPuntuacion, puntuacion);
                    }
                }
            }
            return mejorPuntuacion;
        }
    }
    
    // Encontrar la mejor jugada para la computadora
    std::pair<int, int> obtenerMejorJugada() {
        int mejorPuntuacion = std::numeric_limits<int>::min();
        std::pair<int, int> mejorJugada = {-1, -1};
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (esCasillaVacia(i, j)) {
                    tablero[i][j] = computadora;
                    int puntuacion = minimax(false);
                    tablero[i][j] = ' '; // Deshacer jugada
                    
                    if (DEBUG) {
                        std::cout << "[DEBUG] Evaluando casilla (" << i << "," << j << "): puntuación = " << puntuacion << std::endl;
                    }
                    
                    if (puntuacion > mejorPuntuacion) {
                        mejorPuntuacion = puntuacion;
                        mejorJugada = {i, j};
                    }
                }
            }
        }
        
        if (DEBUG) {
            std::cout << "[DEBUG] Mejor jugada encontrada: (" << mejorJugada.first << "," << mejorJugada.second << ") con puntuación " << mejorPuntuacion << std::endl;
        }
        
        return mejorJugada;
    }
    
    // Obtener entrada del usuario
    std::pair<int, int> obtenerJugadaUsuario() {
        int fila, columna;
        
        while (true) {
            try {
                std::cout << "Ingresa tu jugada (fila columna, ej: 0 1): ";
                std::cin >> fila >> columna;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::invalid_argument("Entrada inválida. Debe ser un número.");
                }
                
                if (fila < 0 || fila >= 3 || columna < 0 || columna >= 3) {
                    throw std::out_of_range("Las coordenadas deben estar entre 0 y 2.");
                }
                
                if (!esCasillaVacia(fila, columna)) {
                    throw std::runtime_error("Esa casilla ya está ocupada.");
                }
                
                break;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << " Inténtalo de nuevo.\n";
            }
        }
        
        return {fila, columna};
    }
    
    // Jugar el juego completo
    void jugar() {
        std::cout << "Eres " << jugador_humano << ", la computadora es " << computadora << std::endl;
        
        mostrarTablero();
        
        while (true) {
            // Turno del usuario
            try {
                std::pair<int, int> jugadaUsuario = obtenerJugadaUsuario();
                hacerJugada(jugadaUsuario.first, jugadaUsuario.second, jugador_humano);
                
                if (DEBUG) {
                    std::cout << "[DEBUG] Usuario jugó en (" << jugadaUsuario.first << "," << jugadaUsuario.second << ")" << std::endl;
                }
                
                mostrarTablero();
                
                char ganador = verificarGanador();
                if (ganador == jugador_humano) {
                    std::cout << "Has ganado" << std::endl;
                    break;
                } else if (esEmpate()) {
                    std::cout << "Empate" << std::endl;
                    break;
                }
                
                // Turno de la computadora
                std::cout << "Turno de la computadora..." << std::endl;
                std::pair<int, int> mejorJugada = obtenerMejorJugada();
                hacerJugada(mejorJugada.first, mejorJugada.second, computadora);
                
                if (DEBUG) {
                    std::cout << "[DEBUG] Computadora jugó en (" << mejorJugada.first << "," << mejorJugada.second << ")" << std::endl;
                }
                
                mostrarTablero();
                
                ganador = verificarGanador();
                if (ganador == computadora) {
                    std::cout << "La computadora ha ganado" << std::endl;
                    break;
                } else if (esEmpate()) {
                    std::cout << "Empate" << std::endl;
                    break;
                }
                
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << std::endl;
                std::cout << "Reiniciando el juego..." << std::endl;
                break;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        // Procesar argumentos de línea de comandos
        for (int i = 1; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "--debug" || arg == "-d") {
                DEBUG = true;
                std::cout << "Modo debug activado." << std::endl;
            } else if (arg == "--help" || arg == "-h") {
                std::cout << "Uso: " << argv[0] << " [opciones]" << std::endl;
                std::cout << "Opciones:" << std::endl;
                std::cout << "  --debug, -d    Activa el modo debug" << std::endl;
                std::cout << "  --help, -h     Muestra esta ayuda" << std::endl;
                return 0;
            }
        }
        
        TicTacToe juego;
        juego.jugar();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
