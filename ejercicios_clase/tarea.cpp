#include <iostream>
#include <cmath>

using namespace std;

string convertir_menor_1000(int n)
{
  string unidades[] = {"", "un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
  string especiales[] = {"diez", "once", "doce", "trece", "catorce", "quince", "dieciséis", "diecisiete", "dieciocho", "diecinueve"};
  string decenas[] = {"", "", "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"};
  string centenas[] = {"", "ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};
  string resultado;

  if (n == 0)
    return "";
  if (n == 100)
    return "cien";

  if (n >= 100)
  {
    resultado += centenas[n / 100];
    n %= 100;
    if (n > 0)
      resultado += " ";
  }

  if (n >= 20)
  {
    resultado += decenas[n / 10];
    n %= 10;
    if (n > 0)
      resultado += " y " + unidades[n];
  }
  else if (n >= 10)
  {
    resultado += especiales[n - 10];
  }
  else if (n > 0)
  {
    resultado += unidades[n];
  }

  return resultado;
}

string numero_en_palabras(long n)
{
  if (n == 0)
    return "cero";

  string resultado;
  string miles[] = {"", "mil", "millón"};

  int indice = 0;
  while (n > 0)
  {
    int parte = n % 1000;
    if (parte > 0)
    {
      if (indice == 1 && parte == 1)
      {
        resultado = miles[indice] + " " + resultado;
      }
      else
      {
        string texto = convertir_menor_1000(parte);
        if (indice == 2 && parte > 1)
        {
          resultado = texto + " millones" + " " + resultado;
        }
        else if (indice > 0)
        {
          resultado = texto + " " + miles[indice] + " " + resultado;
        }
        else
        {
          resultado = texto + " " + resultado;
        }
      }
    }
    n /= 1000;
    indice++;
  }

  return resultado;
}

int main()
{
  double numero;
  cout << "Ingrese un monto en pesos: ";
  cin >> numero;

  long parteEntera = (long)numero;
  int centavos = (int)round((numero - parteEntera) * 100);

  cout << numero_en_palabras(parteEntera) << (parteEntera == 1 ? "peso " : "pesos ") << centavos << "/100" << endl;

  return 0;
}