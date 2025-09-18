#include <iostream>
#include <algorithm>

int main()
{
  std::string frase, reverse;
  std::cout << "Ingrese una palabra" << std::endl;
  std::cin >> frase;
  reverse = frase;

  std::reverse(reverse.begin(), reverse.end());
  if (frase == reverse)
  {
    std::cout << "La palabra es palindrome" << std::endl;
  }
  else
  {
    std::cout << "La palabra NO es palindrome" << std::endl;
  }

  return 0;
}