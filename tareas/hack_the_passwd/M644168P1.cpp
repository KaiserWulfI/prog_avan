// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

const bool DEBUG = false;

void print_vector(std::vector<std::string> &vec) {
  for (std::string elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

int min_abs_dist(std::string &str) {
  if (str.size() <= 1) {
    return 0;
  }

  int min = INT_MAX;
  for (int i = 0; i + 1 < str.size(); i++) {
    min = std::min(min, abs(str[i] - str[i + 1]));
  }
  return min;
}

std::string find_password(std::string &usuario) {

  std::vector<std::string> lex_perms;
  std::string s = usuario;
  {
    std::string tmp = s;
    std::vector<std::string> prev;
    for (int i = 0; i < 10; i++) {
      if (!std::prev_permutation(tmp.begin(), tmp.end())) {
        std::prev_permutation(tmp.begin(), tmp.end());
      }
      prev.push_back(tmp);
    }
    std::reverse(prev.begin(), prev.end());

    lex_perms.insert(lex_perms.end(), prev.begin(), prev.end());

    lex_perms.push_back(s);

    tmp = s;
    for (int i = 0; i < 10; i++) {
      if (!std::next_permutation(tmp.begin(), tmp.end())) {
        std::next_permutation(tmp.begin(), tmp.end());
      }
      lex_perms.push_back(tmp);
    }
  }

  if (DEBUG) {
    std::cout << "Full lexicographical\n";
    print_vector(lex_perms);
  }
  int best_min = -1;
  std::string best_perm;
  for (std::string str : lex_perms) {
    int min = min_abs_dist(str);
    if (min > best_min ||
        (min == best_min && (best_perm.empty() || str < best_perm))) {
      best_min = min;
      best_perm = str;
    }
  }

  return best_perm + std::to_string(best_min);
}

int main() {

  std::ifstream archivo("usuarios.txt");
  if (archivo.is_open()) {
    std::string usuario;
    while (std::getline(archivo, usuario)) {
      std::cout << find_password(usuario) << std::endl;
    }
  } else {
    std::cout << "Archivo no usuarios.txt no existe";
    return 1;
  }
  return 0;
}
