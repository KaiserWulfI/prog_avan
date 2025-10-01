// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <iostream>
#include <vector>

const int ALPH_LEN = 26;

int main() {

  std::string frase1, frase2;

  while (std::cin >> frase1 >> frase2) {

    std::vector<char> freq1(ALPH_LEN, 0), freq2(ALPH_LEN, 0);

    for (char c : frase1) {
      freq1[c - 'a']++;
    }

    for (char c : frase2) {
      freq2[c - 'a']++;
    }

    std::string resultado;

    for (int i = 0; i < ALPH_LEN; i++) {
      int val = std::min(freq1[i], freq2[i]);
      resultado.append(val, 'a' + i);
    }

    std::cout << resultado << std::endl;
  }

  return 0;
}
