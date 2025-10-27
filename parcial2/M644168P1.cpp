// Alejandro Longoria Gonzalez
// Matricila: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica

#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

const bool DEBUG = true;

std::string cifrar(std::string &mensaje, int cifrado) {
  if (DEBUG) std::cout << "Iniciando cifrado...\n";
  
  int len = mensaje.length();
  std::string resultado(mensaje);
  
  // Paso 1: Aplicar cifrado César a letras
  if (DEBUG) std::cout << "Aplicando cifrado Cesar...\n";
  for (int i = 0; i < len; i++) {
    char caracter = mensaje[i];
    if (isalpha(caracter)) {
      char base = islower(caracter) ? 'a' : 'A';
      caracter = (caracter - base + cifrado) % 26;
      if (caracter < 0) caracter += 26;
      caracter = caracter + base;
    }
    resultado[i] = caracter;
    if (DEBUG) std::cout << "" << mensaje[i] << " -> " << caracter << std::endl;
  }
  
  // Paso 2: Mover 100 posiciones hacia atrás en ASCII imprimible (32-126)
  if (DEBUG) std::cout << "Aplicando desplazamiento ASCII -100...\n";
  for (int i = 0; i < len; i++) {
    char caracter = resultado[i];
    
    // Solo aplicar a caracteres imprimibles ASCII (32-126)
    if (caracter >= 32 && caracter <= 126) {
      // Convertir a rango 0-94, restar 100, y ajustar módulo 95
      int ascii_val = caracter - 32;
      ascii_val = ascii_val - 100;
      ascii_val = ((ascii_val % 95) + 95) % 95; // Asegurar positivo
      caracter = ascii_val + 32;
    }
    
    resultado[i] = caracter;
    if (DEBUG) std::cout << "ASCII ajustado: " << (int)caracter << " (" << caracter << ")" << std::endl;
  }
  
  if (DEBUG) std::cout << "Cifrado completado.\n";
  return resultado;
}

std::string descifrar(std::string &mensaje, int cifrado) {
  if (DEBUG) std::cout << "Iniciando descifrado...\n";
  
  int len = mensaje.length();
  std::string resultado(mensaje);
  
  // Paso 1: Mover 100 posiciones hacia adelante en ASCII imprimible (32-126)
  if (DEBUG) std::cout << "Aplicando desplazamiento ASCII +100...\n";
  for (int i = 0; i < len; i++) {
    char caracter = mensaje[i];
    
    // Solo aplicar a caracteres imprimibles ASCII (32-126)
    if (caracter >= 32 && caracter <= 126) {
      // Convertir a rango 0-94, sumar 100, y ajustar módulo 95
      int ascii_val = caracter - 32;
      ascii_val = ascii_val + 100;
      ascii_val = ascii_val % 95;
      caracter = ascii_val + 32;
    }
    
    resultado[i] = caracter;
    if (DEBUG) std::cout << "ASCII ajustado: " << (int)mensaje[i] << " (" << mensaje[i] << ") -> " << (int)caracter << " (" << caracter << ")" << std::endl;
  }
  
  // Paso 2: Revertir cifrado César a letras
  if (DEBUG) std::cout << "Revirtiendo cifrado Cesar...\n";
  for (int i = 0; i < len; i++) {
    char caracter = resultado[i];
    if (isalpha(caracter)) {
      char base = islower(caracter) ? 'a' : 'A';
      caracter = (caracter - base - cifrado) % 26;
      if (caracter < 0) caracter += 26;
      caracter = caracter + base;
    }
    resultado[i] = caracter;
    if (DEBUG) std::cout << "Cesar revertido: " << resultado[i] << std::endl;
  }
  
  if (DEBUG) std::cout << "Descifrado completado.\n";
  return resultado;
}

int main(int argc, char **argv) {
  if (DEBUG) std::cout << "Iniciando programa - DEBUG habilitado\n";
  
  std::string mensaje;
  int cifra;

  std::cout << "Cual es el mensaje:\n";
  getline(std::cin, mensaje);

  do {
    std::cout << "Cual es el valor de cifrado(1-25): ";
    std::cin >> cifra;
  } while (cifra < 1 || cifra > 25);

  int len = mensaje.length();

  int opcion;
  do {
    std::cout << "=== CIFRADO CESAR ===\n";
    std::cout << "1. Cifrar\n";
    std::cout << "2. Descifrar\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    switch (opcion) {
    case 1:
      std::cout << cifrar(mensaje, cifra) << std::endl;
      break;
    case 2:
      std::cout << descifrar(mensaje, cifra) << std::endl;
      break;
    default:
      std::cout << "Opcion no valida";
    }
  } while (opcion != 1 && opcion != 2);

  if (DEBUG) std::cout << "Programa terminado exitosamente\n";
  
  return 0;
}
