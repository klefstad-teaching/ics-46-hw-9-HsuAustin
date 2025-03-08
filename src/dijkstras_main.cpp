#include "dijkstras.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Try again" << endl;
        return 1;
    }
    string filename = argv[1];
    Graph G;
    try {file_to_graph(filename, G);} 
    catch (exception& e) {
        cerr << "Error message: " << e.what() << endl;
        return 1;
    }
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int v = 0; v < G.numVertices; v++) {
        vector<int> path = extract_shortest_path(distances, previous, v);
        print_path(path, (distances[v] == INF) ? -1 : distances[v]);
    }
    return 0;
}
