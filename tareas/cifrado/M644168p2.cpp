#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const int TAMANO_ALFABETO = 26;
const char TABLA_VIGENERE[TAMANO_ALFABETO][TAMANO_ALFABETO] = {
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'},
    {'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a'},
    {'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b'},
    {'d', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c'},
    {'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd'},
    {'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e'},
    {'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f'},
    {'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g'},
    {'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'},
    {'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'},
    {'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'},
    {'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'},
    {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
    {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'},
    {'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n'},
    {'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'},
    {'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'},
    {'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q'},
    {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
    {'t', 'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's'},
    {'u', 'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't'},
    {'v', 'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u'},
    {'w', 'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'},
    {'x', 'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w'},
    {'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
    {'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y'}
};

string prepararTexto(const string &texto) {
  string resultado;
  for (char c : texto) {
    if (isalpha(c)) {
      resultado += tolower(c);
    } else {
      resultado += c;
    }
  }
  return resultado;
}

string prepararClave(const string &clave, int longitud) {
  string clavePreparada;
  int claveLength = clave.length();

  for (int i = 0; i < longitud; i++) {
    clavePreparada += tolower(clave[i % claveLength]);
  }
  return clavePreparada;
}

int encontrarColumna(char letra) { return letra - 'a'; }

int encontrarFila(char claveChar, char textoCifradoChar) {
  for (int i = 0; i < TAMANO_ALFABETO; i++) {
    if (TABLA_VIGENERE[i][encontrarColumna(claveChar)] == textoCifradoChar) {
      return i;
    }
  }
  return -1;
}

string cifrar(const string &texto, const string &clave) {
  string textoPreparado = prepararTexto(texto);
  string clavePreparada = prepararClave(clave, textoPreparado.length());
  string resultado;

  for (int i = 0; i < textoPreparado.length(); i++) {
    if (isalpha(textoPreparado[i]))
    {
      int fila = encontrarColumna(clavePreparada[i]);
      int columna = encontrarColumna(textoPreparado[i]);
      resultado += TABLA_VIGENERE[fila][columna];
    }
    else
    {
      resultado += textoPreparado[i];
    }
  }

  return resultado;
}

// Decryption function
string descifrar(const string &textoCifrado, const string &clave) {
  string textoCifradoPreparado = prepararTexto(textoCifrado);
  string clavePreparada = prepararClave(clave, textoCifradoPreparado.length());
  string resultado;

  for (int i = 0; i < textoCifradoPreparado.length(); i++) {
    if (isalpha(textoCifradoPreparado[i]))
    {
      int fila = encontrarFila(clavePreparada[i], textoCifradoPreparado[i]);
      resultado += 'a' + fila;
    }
    else
    {
      resultado += textoCifradoPreparado[i];
    }
  }

  return resultado;
}

int main() {
  int opcion;
  string texto, clave, resultado;

  cout << "=== CIFRADO VIGENERE ===\n";

  do {
    cout << "\nMenu:\n";
    cout << "1. Encriptar texto\n";
    cout << "2. Desencriptar texto\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
    case 1: {
      cout << "Ingrese el texto a cifrar: ";
      getline(cin, texto);
      cout << "Ingrese la clave: ";
      getline(cin, clave);

      if (texto.empty() || clave.empty()) {
        cout << "Error: Texto y clave no pueden estar vacios.\n";
        break;
      }

      resultado = cifrar(texto, clave);
      cout << "Texto encriptado: " << resultado << endl;
      break;
    }

    case 2: {
      cout << "Ingrese el texto a descifrar: ";
      getline(cin, texto);
      cout << "Ingrese la clave: ";
      getline(cin, clave);

      if (texto.empty() || clave.empty()) {
        cout << "Error: Texto y clave no pueden estar vacios.\n";
        break;
      }

      resultado = descifrar(texto, clave);
      cout << "Texto desencriptado: " << resultado << endl;
      break;
    }

    case 3: {
      cout << "Saliendo del programa...\n";
      break;
    }

    default: {
      cout << "Opcion no valida. Intente nuevamente.\n";
      break;
    }
    }

  } while (opcion != 3);

  return 0;
}
