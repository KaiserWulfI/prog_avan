#include <iostream>
#include <string>

using namespace std;

bool email_valido(string email)
{
  int n = email.length();

  // No vacio
  if (n == 0) return false;

  // No espacios
  for (char c : email)
  {
    if (c == ' ') return false;
  }

  // @ no al inicio ni al final
  int pos_arroba = -1;
  for (int i = 0; i < n; i++)
  {
    if (email[i] == '@')
    {
      if (pos_arroba != -1) return false; // mas de una @
      pos_arroba = i;
    }
  }

  if (pos_arroba == -1 || pos_arroba == 0 || pos_arroba == n - 1) return false; // no hay '@', '@' al inicio o '@' al final
                                                                                
  int pos_punto = -1;
  for (int i = 0; i < n; i++)
  {
    if (email[i] == '.')
    {
      pos_punto = i;
      break;
    }
  }

  if (pos_punto == -1 || pos_punto == pos_arroba + 1 || pos_punto == n - 1) return false; // no hay '.', '.' justo despues de '@' o '.' al final

  return true;
}

int main()
{
  string email;

  cout << "Cual es el email? ";
  cin >> email;
  if (email_valido(email))
  {
    cout << "email es valido" << endl;
  }
  else
  {
    cout << "email NO es valido" << endl;
  }

  return 0;
}
