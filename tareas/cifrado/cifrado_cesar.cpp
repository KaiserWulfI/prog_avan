#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

void cifrar(std::string mensaje, int cifrado)
{
  int len = mensaje.length();
  for (int i = 0; i < len; i++)
  {
    char caracter = mensaje[i];
    if(isalpha(mensaje[i]))
    {
      caracter = tolower(caracter) + cifrado;
      if (caracter > 'z')
      {
        int restante = caracter - 'z' - 1;
        caracter = 'a' + restante;
      }
    }
    std::cout << caracter;
  }
  std::cout << std::endl;
}

void descifrar(std::string mensaje, int cifrado)
{
  int len = mensaje.length();
  for (int i = 0; i < len; i++)
  {
    if (mensaje[i] == ' ')
    {
      std::cout << ' ';
      continue;
    }
    char caracter = tolower(mensaje[i]) - cifrado;
    if (caracter < 'a')
    {
      int restante = 'a' - caracter - 1;
      caracter = 'z' - restante;
    }
    std::cout << caracter;
  }
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  std::string mensaje;
  int cifra;

  std::cout << "Cual es el mensaje:\n";
  getline(std::cin, mensaje);

  do {
    std::cout << "Cual es el valor de cifrado(1-25): ";
    std::cin >> cifra;
  } while(cifra < 1 || cifra > 25);

  int len = mensaje.length();

  int opcion;
  do {
    std::cout << "=== CIFRADO CESAR ===\n";
    std::cout << "1. Cifrar\n";
    std::cout << "2. Descifrar\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    switch(opcion) {
      case 1:
        cifrar(mensaje, cifra);
        break;
      case 2:
        descifrar(mensaje, cifra);
        break;
      default:
        std::cout << "Opcion no valida";
    }
  } while(opcion != 1 && opcion != 2);

  return 0;
}
