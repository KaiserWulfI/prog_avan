#include <iostream>

int main()
{
  std::string nombre, apellido, nombre_completo;
  std::cout << "Ingresa tu nombre" << std::endl;
  std::cin >> nombre;
  std::cout << "Ingresa tu apellido" << std::endl;
  std::cin >> apellido;

  nombre_completo = nombre + ' ' + apellido;
  std::cout << nombre_completo << std::endl;

  return 0;
}