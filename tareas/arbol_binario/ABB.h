// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#ifndef ABB_H
#define ABB_H

#include <queue>
#include <vector>
#include <climits>

// Variable global de debug
extern bool DEBUG;

// Estructura del nodo
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    
    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

// Clase Árbol Binario de Búsqueda
class ABB {
private:
    Nodo* raiz;
    
public:
    ABB() : raiz(nullptr) {}
    
    ~ABB() {
        liberarMemoria(raiz);
    }
    
    // Operaciones fundamentales
    void insertar(int valor) {
        raiz = insertarRecursivo(raiz, valor);
        if (DEBUG) {
            std::cout << "Insertado: " << valor << std::endl;
        }
    }
    
    Nodo* buscar(int valor) {
        return buscarRecursivo(raiz, valor);
    }
    
    void eliminar(int valor) {
        if (buscar(valor) != nullptr) {
            raiz = eliminarRecursivo(raiz, valor);
            if (DEBUG) {
                std::cout << "Eliminado: " << valor << std::endl;
            }
        } else {
            std::cout << "El valor " << valor << " no existe en el árbol." << std::endl;
        }
    }
    
    // Recorridos
    std::vector<int> preorden() {
        std::vector<int> resultado;
        preordenRecursivo(raiz, resultado);
        return resultado;
    }
    
    std::vector<int> inorden() {
        std::vector<int> resultado;
        inordenRecursivo(raiz, resultado);
        return resultado;
    }
    
    std::vector<int> postorden() {
        std::vector<int> resultado;
        postordenRecursivo(raiz, resultado);
        return resultado;
    }
    
    std::vector<int> porAmplitud() {
        std::vector<int> resultado;
        if (raiz == nullptr) {
            return resultado;
        }
        
        std::queue<Nodo*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            Nodo* actual = cola.front();
            cola.pop();
            
            resultado.push_back(actual->valor);
            
            if (actual->izquierdo != nullptr) {
                cola.push(actual->izquierdo);
            }
            if (actual->derecho != nullptr) {
                cola.push(actual->derecho);
            }
        }
        
        return resultado;
    }
    
    // Propiedades
    int altura() {
        return alturaRecursiva(raiz);
    }
    
    int contarNodos() {
        return contarNodosRecursivo(raiz);
    }
    
    int contarHojas() {
        return contarHojasRecursivo(raiz);
    }
    
    int contarInternos() {
        return contarInternosRecursivo(raiz);
    }
    
    int encontrarMinimo() {
        if (raiz == nullptr) {
            return INT_MIN;
        }
        Nodo* minimo = encontrarMinimo(raiz);
        return minimo->valor;
    }
    
    int encontrarMaximo() {
        if (raiz == nullptr) {
            return INT_MIN;
        }
        Nodo* maximo = encontrarMaximo(raiz);
        return maximo->valor;
    }
    
    bool esABB() {
        return esABBRecursivo(raiz, INT_MIN, INT_MAX);
    }
    
    void balancear() {
        std::vector<int> elementos = inorden();
        raiz = construirABBbalanceado(elementos, 0, elementos.size() - 1);
    }
    
    void visualizar() {
        if (raiz == nullptr) {
            std::cout << "El árbol está vacío." << std::endl;
            return;
        }
        
        std::cout << "\nEstructura del Árbol (visualización simple):\n";
        visualizarRecursivo(raiz, 0);
    }

private:
    // Funciones auxiliares recursivas
    Nodo* insertarRecursivo(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }
        
        if (valor < nodo->valor) {
            nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            nodo->derecho = insertarRecursivo(nodo->derecho, valor);
        }
        
        return nodo;
    }
    
    Nodo* buscarRecursivo(Nodo* nodo, int valor) {
        if (nodo == nullptr || nodo->valor == valor) {
            return nodo;
        }
        
        if (valor < nodo->valor) {
            return buscarRecursivo(nodo->izquierdo, valor);
        } else {
            return buscarRecursivo(nodo->derecho, valor);
        }
    }
    
    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->izquierdo != nullptr) {
            nodo = nodo->izquierdo;
        }
        return nodo;
    }
    
    Nodo* encontrarMaximo(Nodo* nodo) {
        while (nodo->derecho != nullptr) {
            nodo = nodo->derecho;
        }
        return nodo;
    }
    
    Nodo* eliminarRecursivo(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return nodo;
        }
        
        if (valor < nodo->valor) {
            nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            nodo->derecho = eliminarRecursivo(nodo->derecho, valor);
        } else {
            // Caso 1: Nodo hoja o sin hijos
            if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: Nodo con un solo hijo
            else if (nodo->izquierdo == nullptr) {
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == nullptr) {
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Caso 3: Nodo con dos hijos
            else {
                Nodo* sucesor = encontrarMinimo(nodo->derecho);
                nodo->valor = sucesor->valor;
                nodo->derecho = eliminarRecursivo(nodo->derecho, sucesor->valor);
            }
        }
        
        return nodo;
    }
    
    void preordenRecursivo(Nodo* nodo, std::vector<int>& resultado) {
        if (nodo != nullptr) {
            resultado.push_back(nodo->valor);
            preordenRecursivo(nodo->izquierdo, resultado);
            preordenRecursivo(nodo->derecho, resultado);
        }
    }
    
    void inordenRecursivo(Nodo* nodo, std::vector<int>& resultado) {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izquierdo, resultado);
            resultado.push_back(nodo->valor);
            inordenRecursivo(nodo->derecho, resultado);
        }
    }
    
    void postordenRecursivo(Nodo* nodo, std::vector<int>& resultado) {
        if (nodo != nullptr) {
            postordenRecursivo(nodo->izquierdo, resultado);
            postordenRecursivo(nodo->derecho, resultado);
            resultado.push_back(nodo->valor);
        }
    }
    
    int alturaRecursiva(Nodo* nodo) {
        if (nodo == nullptr) {
            return -1;
        }
        
        int alturaIzq = alturaRecursiva(nodo->izquierdo);
        int alturaDer = alturaRecursiva(nodo->derecho);
        
        return 1 + std::max(alturaIzq, alturaDer);
    }
    
    int contarNodosRecursivo(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + contarNodosRecursivo(nodo->izquierdo) + contarNodosRecursivo(nodo->derecho);
    }
    
    int contarHojasRecursivo(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            return 1;
        }
        return contarHojasRecursivo(nodo->izquierdo) + contarHojasRecursivo(nodo->derecho);
    }
    
    int contarInternosRecursivo(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        if (nodo->izquierdo == nullptr && nodo->derecho == nullptr) {
            return 0;
        }
        return 1 + contarInternosRecursivo(nodo->izquierdo) + contarInternosRecursivo(nodo->derecho);
    }
    
    bool esABBRecursivo(Nodo* nodo, int min, int max) {
        if (nodo == nullptr) {
            return true;
        }
        
        if (nodo->valor < min || nodo->valor > max) {
            return false;
        }
        
        return esABBRecursivo(nodo->izquierdo, min, nodo->valor - 1) &&
               esABBRecursivo(nodo->derecho, nodo->valor + 1, max);
    }
    
    void liberarMemoria(Nodo* nodo) {
        if (nodo != nullptr) {
            liberarMemoria(nodo->izquierdo);
            liberarMemoria(nodo->derecho);
            delete nodo;
        }
    }
    
    Nodo* construirABBbalanceado(const std::vector<int>& elementos, int inicio, int fin) {
        if (inicio > fin) {
            return nullptr;
        }
        
        int medio = (inicio + fin) / 2;
        Nodo* nodo = new Nodo(elementos[medio]);
        
        nodo->izquierdo = construirABBbalanceado(elementos, inicio, medio - 1);
        nodo->derecho = construirABBbalanceado(elementos, medio + 1, fin);
        
        return nodo;
    }
    
    void visualizarRecursivo(Nodo* nodo, int nivel) {
        if (nodo != nullptr) {
            visualizarRecursivo(nodo->derecho, nivel + 1);
            for (int i = 0; i < nivel; i++) {
                std::cout << "    ";
            }
            std::cout << nodo->valor << std::endl;
            visualizarRecursivo(nodo->izquierdo, nivel + 1);
        }
    }
};

#endif // ABB_H
