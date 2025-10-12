// Alejandro Longoria Gonzalez
// 644168
// Doy mi palabra que he realizado esta actividad con integridad academica

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool DEBUG = true;
const int N = 15; // tamaño de la sopa

char sopa[N][N] = {
    {'m', 'c', 'u', 'c', 'a', 'r', 'a', 'c', 'h', 'a', 'l', 'a', 'p', 'm', 'i'},
    {'o', 'f', 'r', 'a', 'i', 'l', 'e', 'c', 'i', 'l', 'l', 'o', 'p', 'o', 't'},
    {'s', 'a', 'm', 'a', 'l', 'l', 'i', 'n', 'i', 'h', 'c', 'o', 'c', 'n', 'p'},
    {'c', 'w', 'o', 'a', 'd', 'u', 'c', 'a', 'r', 'r', 'a', 'b', 'o', 'o', 'o'},
    {'a', 's', 'a', 'l', 't', 'a', 'm', 'o', 'n', 't', 'e', 's', 's', 'c', 'l'},
    {'o', 'r', 'i', 'n', 'o', 'c', 'e', 'r', 'o', 'n', 't', 'e', 'n', 'o', 'l'},
    {'j', 'e', 'd', 'e', 'l', 'e', 'f', 'a', 'n', 't', 'e', 'i', 'a', 'y', 'o'},
    {'a', 't', 'a', 'n', 'a', 'r', 'a', 'j', 'i', 't', 'r', 'a', 'g', 'a', 'l'},
    {'b', 'n', 'l', 'r', 'a', 'c', 'o', 'd', 'o', 'r', 'n', 'i', 'z', 'm', 'l'},
    {'a', 'e', 'l', 'm', 'a', 'm', 'u', 'l', 'o', 'i', 'o', 'r', 'c', 'a', 'i'},
    {'r', 'i', 'i', 'o', 'e', 'b', 'a', 't', 'l', 'r', 'a', 't', 'a', 'c', 'd'},
    {'a', 'p', 'l', 'r', 'u', 'h', 'i', 'l', 'e', 'c', 'h', 'u', 'z', 'a', 'a'},
    {'c', 'r', 'o', 's', 'c', 'n', 'a', 'p', 'a', 'r', 'e', 'n', 'o', 'u', 'm'},
    {'s', 'e', 'p', 'a', 'r', 'g', 'r', 'c', 'a', 's', 't', 'o', 'r', 'g', 'r'},
    {'e', 's', 'c', 'o', 'a', 'l', 'l', 'i', 'h', 'c', 'n', 'i', 'h', 'c', 'a'},
};

void imprimirSopa() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (sopa[i][j] < 91)
        printf("\x1b[0;31m%c ", sopa[i][j]);
      else
        printf("\x1b[0;39m%c ", sopa[i][j]);
    }
    cout << endl;
  }
}

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
bool buscarPalabra(string &palabra, int x, int y, int dir) {
  for (int i = 0; i < palabra.length(); i++) {
    int nx = x + i * dx[dir];
    int ny = y + i * dy[dir];
    if (nx < 0 || ny < 0 || nx >= N || ny >= N)
      return false;
    if (tolower(sopa[nx][ny]) != palabra[i])
      return false;
  }
  return true;
}

void marcarPalabra(string &palabra, int x, int y, int dir) {
  for (int i = 0; i < palabra.length(); i++) {
    int nx = x + i * dx[dir];
    int ny = y + i * dy[dir];
    sopa[nx][ny] = toupper(sopa[nx][ny]);
  }
}

bool buscar(const string &palabra) {
  if (DEBUG)
    cout << "[DEBUG] Buscando palabra: " << palabra << endl;
  for (int x = 0; x < N; x++) {
    for (int y = 0; y < N; y++) {
      if (tolower(sopa[x][y]) == palabra[0]) {
        for (int dir = 0; dir < 8; dir++) {
          if (buscarPalabra(palabra, x, y, dir)) {
            if (DEBUG)
              cout << "[DEBUG] Encontrada en (" << x << "," << y
                   << ") dirección " << dir << endl;
            marcarPalabra(palabra, x, y, dir);
            return true;
          }
        }
      }
    }
  }
  return false;
}

int main() {
  try {
    int num;
    cout << "Ingrese el número de palabras a buscar: ";
    cin >> num;
    if (num <= 0)
      throw invalid_argument("El número debe ser mayor a cero.");

    vector<string> palabras(num);
    cout << "Ingrese las palabras a buscar:" << endl;
    for (int i = 0; i < num; i++) {
      cin >> palabras[i];
    }

    for (string &p : palabras) {
      bool encontrada = buscar(p);
      if (DEBUG) {
        if (encontrada)
          cout << "Palabra '" << p << "' encontrada.\n";
        else
          cout << "Palabra '" << p << "' NO encontrada.\n";
      }
    }

    cout << "\n======= SOPA DE LETRAS ======\n";
    imprimirSopa();

  } catch (const exception &e) {
    cout << "ERROR: " << e.what() << endl;
  }

  return 0;
}
