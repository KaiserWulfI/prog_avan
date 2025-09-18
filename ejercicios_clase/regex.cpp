#include <iostream>
#include <string>
#include <regex>

int main()
{
  std::string text = "Nombre Juan Perez, Edad: 30, Ciudad: Madrid";

  // El patron busca "Edad: " seguida por uno o mas digitos, y los captua en un grupo
  std::regex pattern("Edad: (\\d+)");
  std::smatch matches;

  //Busca la primera coincidencia del patron en la cadena de texto
  if(std::regex_search(text, matches, pattern))
  {
    // matches[0] es la coincidencia completa ("Edad: 30")
    std::cout << "Coincidencia completa: " << matches[0] << std::endl;
    // matches[1] es el primer grupo de captura (solo "30")
    std::cout << "Edad extraida: " << matches[1] << std::endl;
  }
  else
  {
    std::cout << "No se enconto una edad." << std::endl;
  }

  return 0;
}
