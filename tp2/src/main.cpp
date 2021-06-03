#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>

#include "types.h"
#include "solver.h"

using namespace std;

Grafo leerInstancia() {
    uint n, m;
    cin >> n >> m;

    // Como C es un vector de unsigned int, INF siendo -1 se interpreta como
    // MAX_INT.
    vector<vector<uint>> C(n+1, vector<uint>(n+1, INF));

    uint v, w, c;
    for (uint i = 0; i < m; ++i) {
        cin >> v >> w >> c;
        C[v][w] = c;
        C[w][v] = c;
    }

    Grafo G;
    G = {n, m, C};

    return G;
}

void imprimirInstancia(Grafo G) {
    cout << "N: " << G.vertices << ", " << "M: " << G.aristas << endl;

    uint n = G.vertices;

    for (uint i = 1 ; i < n+1; ++i) {
        for (uint j = 1; j < n+1; ++j) {
            if (i == j) continue;
            cout << '(' << i << ", " << j << ") : " << G.costos[i][j] << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    map<string, string> m_heuristicas_implementadas = {
		{"NN", "Nearest Neighbour"},
		{"FI", "Farthest Insertion"},
		{"AGM", "Árbol Generador Mínimo"},
	};

    if (argc < 2) {
		cerr << 
			"Los cantidad de parámetros ingresados es incorrecta.\n" <<
			"Uso correcto: ./TSP <heuristica> < <archivo_entrada>\n";
        
        return EXIT_FAILURE;
    }

    string s_input_heuristica = argv[1];
    if (m_heuristicas_implementadas.count(s_input_heuristica) == 0) {
        cerr << "Heurística no reconocida. Las opciones implementadas son:\n";

		for (auto& e : m_heuristicas_implementadas)
			cerr << "\t- " << e.first << ": " << e.second << '\n';

		return EXIT_FAILURE;
	}

    Grafo G = leerInstancia();
    
    // imprimirInstancia(G);

    Circuito H;

    auto start = chrono::steady_clock::now();
    
    if (s_input_heuristica.compare("NN") == 0) {
        H = nearestNeighbour(G);
    }
    // } else if (s_input_heuristica.compare("FI") == 0) {
    //     C = farthestInsertion(G);
    // } else if (s_input_heuristica.compare("AGM")== 0) {
    //     C = AGM(G); 
    // }

    auto end = chrono::steady_clock::now();
	double totalTime = chrono::duration<double, milli>(end - start).count();

	clog << totalTime << endl;
    cout << H.vertices.size() << ' ' << H.costo << endl;
	for (Vertice v : H.vertices) {
        cout << v << ' ';
    }
    cout << endl;
    return EXIT_SUCCESS;
}