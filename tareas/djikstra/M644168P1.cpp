// Alejandro Longoria Gonzalez
// Matricula: 644168
// Doy mi palabra que he realizado esta actividad con integridad academica.

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

bool DEBUG = true;

struct Arista {
  string destino;
  int peso;
};

void dijkstra(const unordered_map<string, vector<Arista>> &grafo,
              const string &inicio, const string &fin) {
  if (!grafo.count(inicio) || !grafo.count(fin))
    throw invalid_argument("Uno o ambos nodos no existen en el grafo.");

  unordered_map<string, int> distancia;
  unordered_map<string, string> previo;
  for (const auto &nodo : grafo)
    distancia[nodo.first] = INT_MAX;

  distancia[inicio] = 0;

  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
  pq.push({0, inicio});

  if (DEBUG)
    cout << "[DEBUG] Iniciando Dijkstra desde " << inicio << " hacia " << fin
         << endl;

  while (!pq.empty()) {
    auto [distActual, nodo] = pq.top();
    pq.pop();

    if (distActual > distancia[nodo])
      continue;

    if (DEBUG)
      cout << "[DEBUG] Visitando nodo: " << nodo << " con distancia "
           << distActual << endl;

    for (const auto &arista : grafo.at(nodo)) {
      int nuevaDist = distActual + arista.peso;
      if (nuevaDist < distancia[arista.destino]) {
        distancia[arista.destino] = nuevaDist;
        previo[arista.destino] = nodo;
        pq.push({nuevaDist, arista.destino});
        if (DEBUG)
          cout << "  [DEBUG] Actualizando " << arista.destino
               << " con nueva distancia " << nuevaDist << endl;
      }
    }
  }

  if (distancia[fin] == INT_MAX) {
    cout << "No hay camino entre " << inicio << " y " << fin << endl;
    return;
  }

  cout << "\nDistancia mínima entre " << inicio << " y " << fin << ": "
       << distancia[fin] << endl;

  vector<string> camino;
  for (string at = fin; !at.empty(); at = previo[at])
    camino.push_back(at);
  reverse(camino.begin(), camino.end());

  cout << "Camino más corto: ";
  for (size_t i = 0; i < camino.size(); ++i) {
    cout << camino[i];
    if (i < camino.size() - 1)
      cout << " -> ";
  }
  cout << endl;
}

int main() {
  try {
    unordered_map<string, vector<Arista>> grafo = {
        {"s", {{"b", 4}, {"c", 2}}},
        {"b", {{"s", 4}, {"c", 1}, {"d", 5}}},
        {"c", {{"s", 2}, {"b", 1}, {"d", 8}, {"e", 10}}},
        {"d", {{"b", 5}, {"c", 8}, {"e", 2}, {"t", 6}}},
        {"e", {{"c", 10}, {"d", 2}, {"t", 2}}},
        {"t", {{"d", 6}, {"e", 2}}}};

    string inicio, fin;
    cout << "Ingrese el nodo inicial: ";
    cin >> inicio;
    cout << "Ingrese el nodo final: ";
    cin >> fin;

    dijkstra(grafo, inicio, fin);

  } catch (const exception &e) {
    cout << "[ERROR] Excepción: " << e.what() << endl;
  }

  return 0;
}
