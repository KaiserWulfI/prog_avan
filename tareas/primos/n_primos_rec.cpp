#include <iostream>

bool numero_primo(int numero, int divisor = 2)
{
  if (numero == 2) return true;
  if (numero % divisor == 0) return false;
  if (divisor > numero/2) return true;
  return numero_primo(numero, divisor + 1);
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
