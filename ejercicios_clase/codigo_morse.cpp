#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<char, string> diccionario_mapa{
	{'a', ".-"},
	{'b', "-..."},
	{'c', "-.-."},
};
bool debug = false;

string convertirMorse(string f)
{
	string respuesta = "";
	for (int i = 0; i < f.length(); i++)
	{
		try
		{
			if (f[i] != ' ')
			{
				if (diccionario_mapa.find(f[i]) != diccionario_mapa.end())
				{
					respuesta += diccionario_mapa[f[i]];
				}
			}
		}
		catch (const exception &e)
		{
			cout << "Valor invalido" << endl;
		}
	}
	return respuesta;
}

string convertirTexto()
{
	return "";
}

int main(int argc, char *args[])
{
	int op;
	string frase;

	cout << "Ingrese 1 para convertir a morse" << endl;
	cout << "Ingrese 2 para convertir a texto" << endl;
  cout << ">> ";
	cin >> op;

	cout << "Ingrese la palabra a procesar" << endl;
  cin.ignore();
	getline(cin, frase);

	if (debug)
	{
		cout << "El usuario slecciono la opcion" << op;
	}

	switch (op)
	{
    case 1:
      cout << convertirMorse(frase) << endl;
      break;
    case 2:
      cout << convertirTexto() << endl;
      break;
	}
}
