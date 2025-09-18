#include <iostream>

int main()
{
  std::string frase;
  char caracter;
  int contador = 0;

  std::cout << "Ingrese una Frase" << std::endl;
  std::cin >> frase;
  std::cout << "Que caracter quieres contar" << std::endl;
  std::cin >> caracter;

  for (char letra : frase)
  {
    letra = tolower(letra);
    if (letra == caracter)
    {
      contador++;
    }
  }

  std::cout << "Hay " << contador << " " << caracter << std::endl;
}