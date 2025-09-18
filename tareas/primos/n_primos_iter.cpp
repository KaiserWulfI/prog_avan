#include <iostream>
#include <cmath>
#include <vector>

bool numero_primo(int numero)
{
  int mitad = numero/2 + 1;
  for (int i = 2; i < mitad; i++)
  {
    if(numero % i == 0)
    {
      return false;
    }
  }
  return true;
}

int main()
{
  int final;
  std::cout << "Hasta que numero quieres los primos? ";
  std::cin >> final;

  for (int i = 2; i < final; i++)
  {
    if(numero_primo(i))
    {
      std::cout << i << ",";
    }
  }
  std::cout << std::endl;
  return 0;
}
