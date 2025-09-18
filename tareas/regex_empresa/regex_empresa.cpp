#include <iostream>
#include <string>
#include <regex>

// Realiza un programa utilizando Regex y tu habilidad con el manejo de Strings que sea capaz de obtener. 
// Nombre de la empresa, correo electrónico y código postal.

int main()
{
  std::string parrafo;
  std::cout << "Parrafo: ";
  std::getline(std::cin, parrafo);


  std::smatch matches;
  try
  {
    std::regex nombre("empresa:?\\s?\"(\\w+\\s?.+\\.)\"", std::regex_constants::icase);
    std::regex email("[\\w\\-\\.]+@[\\w\\-\\.]+\\.+[\\w-]{2,3}", std::regex_constants::icase);
    std::regex cod_pos("(?:CP|codigo postal):?\\s?(\\d+)", std::regex_constants::icase);

    if(std::regex_search(parrafo, matches, nombre))
    {
      std::cout << "Nombre: " << matches[1] << std::endl;
    }
    else
    {
      std::cout << "No hay nombre" << std::endl;
    }

    if(std::regex_search(parrafo, matches, email))
    {
      std::cout << "Email: " << matches[0] << std::endl;
    }
    else
    {
      std::cout << "No hay email" << std::endl;
    }

    if(std::regex_search(parrafo, matches, cod_pos))
    {
      std::cout << "Codigo Postal: " << matches[1] << std::endl;
    }
    else
    {
      std::cout << "No hay codigo postal" << std::endl;
    }
  }
  catch(const std::regex_error& e)
  {
    std::cout << "regex_error caught: " << e.what() << std::endl;
  }
  

  return 0;
}
