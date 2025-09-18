#include <iostream>
#include <string>
#include <regex>

int main()
{
  std::string email;
  std::cout << "Email: ";
  std::cin >> email;

  std::regex pattern("^[\\w\\-\\.]+@[\\w\\-\\.]+\\.+[\\w-]{2,3}$");
  std::smatch matches;

  if(std::regex_search(email, matches, pattern))
  {
    std::cout << "Email valido." << std::endl;
  }
  else
  {
    std::cout << "El email no es correcto." << std::endl;
  }

  return 0;
}
