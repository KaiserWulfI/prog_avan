// Nombre:    Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <iostream>
#include <string>

const bool DEBUG = false;

char rotar(char original, int rotacion) {
  original += rotacion;
  if (original > 'Z') {
    original -= ('Z' + 1);
    original += 'A';
  }
  return original;
}

std::string descifrar(std::string texto) {
  int mitad = texto.length() / 2;

  std::string valor = texto.substr(0, mitad);
  std::string final = texto.substr(mitad);

  if (DEBUG)
    std::cout << "valor: " << valor << "\nfinal: " << final << std::endl;

  int rotacion_valor = 0;
  int rotacion_final = 0;
  for (int i = 0; i < valor.length(); i++) {
    rotacion_valor += valor[i] - 'A';
    rotacion_final += final[i] - 'A';
  }

  if (DEBUG) {
    std::cout << "rotacion valor: " << rotacion_valor << std::endl;
    std::cout << "rotacion final: " << rotacion_final << std::endl;
  }

  rotacion_valor = rotacion_valor % 26;
  rotacion_final = rotacion_final % 26;
  for (int i = 0; i < valor.length(); i++) {
    valor[i] = rotar(valor[i], rotacion_valor);
    final[i] = rotar(final[i], rotacion_final);
  }

  if (DEBUG) {
    std::cout << "Rotacion Completa\n";
    std::cout << "valor: " << valor << "\nfinal: " << final << std::endl;
  }

  for (int i = 0; i < valor.length(); i++) {
    valor[i] = rotar(valor[i], final[i] - 'A');
  }

  return valor;
}

int main() {
  int casos;
  std::string texto;

  std::cin >> casos;
  for (int i = 0; i < casos; i++) {
    std::cin >> texto;
    std::cout << descifrar(texto) << std::endl;
  }
}
