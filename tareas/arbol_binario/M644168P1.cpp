// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <iostream>
#include "ABB.h"

// Definición de la variable global de debug
bool DEBUG = true;

// Función para mostrar menú
void mostrarMenu() {
    std::cout << "\n=== MENÚ PRINCIPAL - ÁRBOL BINARIO DE BÚSQUEDA ===\n";
    std::cout << "1. Insertar elemento\n";
    std::cout << "2. Buscar elemento\n";
    std::cout << "3. Eliminar elemento\n";
    std::cout << "4. Mostrar recorridos\n";
    std::cout << "5. Mostrar propiedades del árbol\n";
    std::cout << "6. Visualizar árbol\n";
    std::cout << "7. Balancear árbol\n";
    std::cout << "8. Verificar si es ABB válido\n";
    std::cout << "9. Salir\n";
    std::cout << "Seleccione una opción: ";
}

// Función para mostrar recorridos
void mostrarRecorridos(ABB& arbol) {
    std::vector<int> pre = arbol.preorden();
    std::vector<int> in = arbol.inorden();
    std::vector<int> post = arbol.postorden();
    std::vector<int> amplitud = arbol.porAmplitud();
    
    std::cout << "\n=== RECORRIDOS DEL ÁRBOL ===\n";
    
    std::cout << "Preorden (Raíz, Izquierda, Derecha): ";
    for (int val : pre) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Inorden (Izquierda, Raíz, Derecha): ";
    for (int val : in) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Postorden (Izquierda, Derecha, Raíz): ";
    for (int val : post) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Por Amplitud (Nivel por Nivel): ";
    for (int val : amplitud) std::cout << val << " ";
    std::cout << std::endl;
}

// Función para mostrar propiedades
void mostrarPropiedades(ABB& arbol) {
    std::cout << "\n=== PROPIEDADES DEL ÁRBOL ===\n";
    std::cout << "Altura: " << arbol.altura() << std::endl;
    std::cout << "Total de nodos: " << arbol.contarNodos() << std::endl;
    std::cout << "Nodos hoja: " << arbol.contarHojas() << std::endl;
    std::cout << "Nodos internos: " << arbol.contarInternos() << std::endl;
    std::cout << "Valor mínimo: " << arbol.encontrarMinimo() << std::endl;
    std::cout << "Valor máximo: " << arbol.encontrarMaximo() << std::endl;
    std::cout << "¿Es ABB válido? " << (arbol.esABB() ? "Sí" : "No") << std::endl;
}

int main() {
    ABB arbol;
    int opcion, valor;
    
    // Insertar algunos valores iniciales para demostración
    if (DEBUG) {
        std::cout << "Insertando valores iniciales para demostración...\n";
        int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 45};
        for (int val : valores) {
            arbol.insertar(val);
        }
    }
    
    while (true) {
        mostrarMenu();
        std::cin >> opcion;
        
        switch (opcion) {
            case 1: {
                std::cout << "Ingrese el valor a insertar: ";
                std::cin >> valor;
                arbol.insertar(valor);
                break;
            }
            
            case 2: {
                std::cout << "Ingrese el valor a buscar: ";
                std::cin >> valor;
                if (arbol.buscar(valor) != nullptr) {
                    std::cout << "El valor " << valor << " se encuentra en el árbol." << std::endl;
                } else {
                    std::cout << "El valor " << valor << " NO se encuentra en el árbol." << std::endl;
                }
                break;
            }
            
            case 3: {
                std::cout << "Ingrese el valor a eliminar: ";
                std::cin >> valor;
                arbol.eliminar(valor);
                break;
            }
            
            case 4:
                mostrarRecorridos(arbol);
                break;
            
            case 5:
                mostrarPropiedades(arbol);
                break;
            
            case 6:
                arbol.visualizar();
                break;
            
            case 7:
                std::cout << "Balanceando el árbol..." << std::endl;
                arbol.balancear();
                std::cout << "Árbol balanceado exitosamente." << std::endl;
                break;
            
            case 8:
                std::cout << "\n=== VERIFICACIÓN DE ABB ===\n";
                std::cout << "¿Es un ABB válido? " << (arbol.esABB() ? "SÍ" : "NO") << std::endl;
                break;
            
            case 9:
                std::cout << "¡Hasta luego!" << std::endl;
                return 0;
            
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
    }
    
    return 0;
}
