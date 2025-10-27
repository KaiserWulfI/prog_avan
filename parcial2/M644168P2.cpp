// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

const int FILAS = 5;
const int COLUMNAS = 5;
const bool DEBUG = true;

void buscarSumaMaxima(int matriz[FILAS][COLUMNAS]) {
  if (DEBUG) std::cout << "Iniciando busqueda por filas...\n";
  
  int sumaMaxima = -1;
  int totalCombinaciones = 0;
  
  for (int i = 0; i < FILAS; i++) {
    if (DEBUG) std::cout << "Procesando fila " << (i+1) << std::endl;
    
    for (int j = 0; j < COLUMNAS - 2; j++) { // -2 porque necesitamos 3 elementos consecutivos
      totalCombinaciones++;
      int suma = matriz[i][j] + matriz[i][j+1] + matriz[i][j+2];
      std::string ubicacion = "Fila " + std::to_string(i+1) + ", posiciones " + std::to_string(j+1) + "-" + std::to_string(j+3);
      
      if (DEBUG) std::cout << "Calculando suma: matriz[" << i << "][" << j << "]=" << matriz[i][j] 
                           << " + matriz[" << i << "][" << (j+1) << "]=" << matriz[i][j+1] 
                           << " + matriz[" << i << "][" << (j+2) << "]=" << matriz[i][j+2] 
                           << " = " << suma << std::endl;
      
      std::cout << ubicacion << ": " << matriz[i][j] << " + " << matriz[i][j+1] << " + " << matriz[i][j+2] 
                << " = " << suma;
      
      if (suma > sumaMaxima) {
        if (DEBUG) std::cout << "Nueva suma maxima en filas: " << suma;
        sumaMaxima = suma;
      }
      std::cout << std::endl;
    }
  }
  
  if (DEBUG) std::cout << "Iniciando busqueda del maximo por columnas\n";
  
  for (int j = 0; j < COLUMNAS; j++) {
    if (DEBUG) std::cout << "Procesando columna " << (j) << std::endl;
    
    for (int i = 0; i < FILAS - 2; i++) { // -2 porque necesitamos 3 elementos consecutivos
      totalCombinaciones++;
      int suma = matriz[i][j] + matriz[i+1][j] + matriz[i+2][j];
      std::string ubicacion = "Columna " + std::to_string(j+1) + ", posiciones " + std::to_string(i+1) + "-" + std::to_string(i+3);
      
      if (DEBUG) std::cout << "Calculando suma: matriz[" << i << "][" << j << "]=" << matriz[i][j] 
                           << " + matriz[" << (i+1) << "][" << j << "]=" << matriz[i+1][j] 
                           << " + matriz[" << (i+2) << "][" << j << "]=" << matriz[i+2][j] 
                           << " = " << suma << std::endl;
      
      std::cout << ubicacion << ": " << matriz[i][j] << " + " << matriz[i+1][j] << " + " << matriz[i+2][j] 
                << " = " << suma;
      
      if (suma > sumaMaxima) {
        sumaMaxima = suma;
        if (DEBUG) std::cout << "Nueva suma maxima en columnas: " << suma;
      }
      std::cout << std::endl;
    }
  }
  
  if (DEBUG) {
    std::cout << "\nResumen del analisis:\n";
    std::cout << "- Total de combinaciones evaluadas: " << totalCombinaciones << std::endl;
    std::cout << "- Suma maxima final: " << sumaMaxima << std::endl;
  }
  
  std::cout << "La suma mas grande es " << sumaMaxima << std::endl;
}

int main() {
  if (DEBUG) std::cout << "DEBUG habilitado\n";
  
  // Matriz de la imagen proporcionada
  int matriz[FILAS][COLUMNAS] = {
    {80, 200, 50, 30, 5},
    {40, 25, 10, 20, 30},
    {67, 110, 20, 200, 100},
    {80, 6, 45, 3, 12},
    {24, 7, 34, 15, 10}
  };

  std::cout << "=== ANALISIS DE MATRIZ 5x5 ===\n";
  std::cout << "Matriz:\n";
  
  // Mostrar la matriz
  for (int i = 0; i < FILAS; i++) {
    if (DEBUG) std::cout << "Imprimiendo fila " << (i) << ": ";
    
    for (int j = 0; j < COLUMNAS; j++) {
      std::cout << matriz[i][j] << "\t";
    }
    
    if (DEBUG) std::cout << " (fila " << (i) << " completa)";
    std::cout << std::endl;
  }

  // Buscar la suma más grande de 3 elementos consecutivos
  buscarSumaMaxima(matriz);
  
  return 0;
}
