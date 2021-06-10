#pragma once
#include <vector>
#include <climits>
#include <iostream>

namespace NGraph {
    const long long INF = LLONG_MAX;

    struct TEdge {
        size_t from, to;
        long long cost;
    };
    std::istream& operator>> (std::istream& is, TEdge& edge);

    class TGraph {
    public:
        using TVertex = std::vector< std::pair<size_t, long long> >; // stores connected vertexes and dist to them
        using TAdjacencyList = std::vector< TVertex >;

        TGraph(const std::vector<TEdge>& graphEdges, const size_t vertexesCount); // for unit tests
        TGraph(const size_t vertexesCount, const size_t edgesCount);

        std::vector<long long> FordBellman(const size_t target); // O(m * n)
        std::vector<long long> Dijkstra(const size_t target); // O(m * log n)
        std::vector< std::vector<long long> > Jonshon();

        friend std::istream& operator>> (std::istream& is, TGraph& graph);
    private:
        size_t vertexCount;
        std::vector<TEdge> edges;
        TAdjacencyList adjList;
    };

    /*
     * target  = [0 ... vertexCount]
     * from/to = [0 ... vertexCount]
     */

} // namespace NMyGraph
