#include <iostream>
#include "graph.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    size_t vertexCount, edgesCount;
    std::cin >> vertexCount >> edgesCount;
    NGraph::TGraph graph(vertexCount, edgesCount);

    std::cin >> graph;

    try {
        std::vector< std::vector<long long> > result = graph.Jonshon();

        for (size_t i = 0; i < result.size(); ++i) {
            for (size_t j = 0; j < result[i].size(); ++j) {
                long long & cost = result[i][j];
                if (cost == NGraph::INF) {
                    std::cout << "inf";
                } else {
                    std::cout << cost;
                }
                if (j != result[i].size() - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    } catch (std::exception & ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
