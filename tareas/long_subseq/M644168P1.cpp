// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const bool DEBUG = false;

void lcs(std::string &frase1, std::string &frase2) {
  int len1 = frase1.length() + 1;
  int len2 = frase2.length() + 1;

  std::vector<std::vector<std::pair<int, int>>> vec(
      len1, std::vector<std::pair<int, int>>(len2, {0, 0}));

  const int DIAGONAL = 1;
  const int IZQUIERDA = 2;
  const int ARRIBA = 3;

  std::cout << len1 << " " << len2 << std::endl;

  for (int i = 1; i < len1; i++) {
    for (int j = 1; j < len2; j++) {
      if (frase1[i - 1] == frase2[j - 1]) {
        vec[i][j].first = vec[i - 1][j - 1].first + 1;
        vec[i][j].second = DIAGONAL;
      } else {
        if (vec[i][j - 1].first > vec[i - 1][j].first) {
          vec[i][j].first = vec[i][j - 1].first;
          vec[i][j].second = IZQUIERDA;
        } else {
          vec[i][j].first = vec[i - 1][j].first;
          vec[i][j].second = ARRIBA;
        }
      }
      if (DEBUG) {
        std::cout << i << " " << j << " vec: " << vec[i][j].first << " "
                  << (vec[i][j].second == DIAGONAL
                          ? "DIAGONAL "
                          : (vec[i][j].second == ARRIBA ? "ARRIBA "
                                                        : "IZQUIERDA "))
                  << "frases: " << frase1[i - 1] << " " << frase2[j - 1]
                  << std::endl;
      }
    }
  }

  std::string resultado = "";
  int i = len1 - 1;
  int j = len2 - 1;
  while (i > 0 && j > 0) {
    if (vec[i][j].second == DIAGONAL) {
      resultado.append(1, frase1[i - 1]);
      i--;
      j--;
    } else if (vec[i][j].second == ARRIBA) {
      i--;
    } else if (vec[i][j].second == IZQUIERDA) {
      j--;
    }
    if (DEBUG) {
      std::cout << "res: " << resultado << std::endl;
    }
  }
  std::reverse(resultado.begin(), resultado.end());
  std::cout << "Resultado: " << resultado << std::endl;
}

int main() {
  bool continuar = true;

  while (continuar) {
    std::string frase1, frase2;

    std::cout << "Frases(sin espacios, solo minusculas): ";
    std::cin >> frase1 >> frase2;

    lcs(frase1, frase2);

    char continuar_char = '\0';
    while (continuar_char != 'y' && continuar_char != 'n') {
      std::cout << "Quieres hacer otro?(Y/n) ";
      std::cin >> continuar_char;
      continuar_char = std::tolower(continuar_char);
      if (continuar_char == 'n')
        continuar = false;
    }
  }
}
