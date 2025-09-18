#include <iostream>
#include <string>

std::string comprimir(std::string palabra)
{
  int len = palabra.length();
  int contador = 1;
  std::string comprimida = "";
  char anterior = palabra[0];
  for (int i = 1; i < len; i++)
  {
    if (anterior == palabra[i])
    {
      contador++;
    }
    else
    {
      comprimida += anterior;
      if (contador != 1)
      {
        comprimida += std::to_string(contador);
      }
      anterior = palabra[i];
      contador = 1;
    }
  }
  comprimida += anterior;
  if (contador != 1)
  {
    comprimida += std::to_string(contador);
  }
  return comprimida;
}

std::string descomprimir(std::string palabra)
{
  int len = palabra.length();
  std::string descomprimida = "";
  char caracter, anterior;

  for (int i = 0; i < len; i++)
  {
    caracter = palabra[i];
    if (isdigit(caracter))
    {
      int pos = i;
      int digitos = i;
      while (isdigit(palabra[digitos]) != 0)
      {
        digitos++;
      }
      std::string numero = palabra.substr(pos, digitos - pos);
      int cant = stoi(numero);
      for (int j = 1; j < cant; j++)
      {
        descomprimida += anterior;
      }
      if (digitos > 1)
      {
        i += digitos - pos - 1;
      }
    }
    else
    {
      descomprimida += caracter;
    }
    anterior = caracter;
  }

  return descomprimida;
}

int main()
{

  char opcion;
  std::string palabra;

  do
  {
    std::cout << "¿Quieres comprimir(c) o descomprimir(d)? ";
    std::cin >> opcion;
    if (opcion == 'c')
    {
      std::cout << "Palabra a comprimir: ";
      std::cin >> palabra;
      std::cout << comprimir(palabra) << std::endl;
    }
    else if (opcion == 'd')
    {
      std::cout << "Palabra a descomprimir: ";
      std::cin >> palabra;
      std::cout << descomprimir(palabra) << std::endl;
    }
    else
    {
      std::cout << "Opcion no valida" << std::endl;
    }
  } while (opcion != 'c' && opcion != 'd');

  return 0;
}
