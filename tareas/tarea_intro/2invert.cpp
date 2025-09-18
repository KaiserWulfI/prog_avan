#include <iostream>
#include <algorithm>

int main() {
  
  std::string frase;

  std::cout<<"Ingrese una palabra"<<std::endl;
  std::cin>>frase;

  std::reverse(frase.begin(), frase.end());

  for (char temp : frase) {
    std::cout<<temp;
  }
  std::cout<<std::endl;

  return 0;
}
