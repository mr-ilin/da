#include "graph.h"
#include <queue>

namespace NGraph {

    std::istream& operator>> (std::istream& is, TEdge& edge) {
        size_t from, to;
        is >> from >> to >> edge.cost;
        edge.from = from - 1;
        edge.to = to - 1;
        return is;
    }

    TGraph::TGraph(const std::vector<TEdge>& graphEdges, const size_t vertexesCount)
        : vertexCount(vertexesCount),
        edges(graphEdges)

    {
        TAdjacencyList tmpAdjList(vertexCount,
                TVertex(0));
        for (size_t i = 0; i < edges.size(); ++i) {
            const TEdge& currEdge = edges[i];
            tmpAdjList[currEdge.from].push_back(std::make_pair(currEdge.to, currEdge.cost));
        }
        adjList = std::move(tmpAdjList);
    }

    TGraph::TGraph(const size_t vertexesCount, const size_t edgesCount)
        : vertexCount(vertexesCount),
        edges(edgesCount),
        adjList(vertexesCount,TVertex(0))
    {}

    std::istream& operator>> (std::istream& is, TGraph& graph) {
        for (size_t i = 0; i < graph.edges.size(); ++i) {
            TEdge& edge = graph.edges[i];
            is >> edge;
            graph.adjList[edge.from].push_back(std::make_pair(edge.to, edge.cost));
        }
        return is;
    }

    std::vector<long long> TGraph::FordBellman(const size_t target) {
        std::vector<long long> distances (vertexCount, INF);
        distances[target] = 0;
        for (size_t i = 0; i <= vertexCount; ++i) {
            bool changed = false;
            for (size_t j = 0; j < edges.size(); ++j) {
                const size_t & from = edges[j].from ;
                const size_t & to = edges[j].to;
                const long long cost = edges[j].cost;
                if (distances[from] < INF && distances[to] > distances[from] + cost) {
                    changed = true;
                    distances[to] = std::max(
                            -INF,
                            distances[from] + cost
                    );
                }
            }
            if (!changed) {
                break;
            } else if (i == vertexCount) {
                throw std::runtime_error("Negative cycle");
            }
        }
        return distances;
    }

    std::vector<long long> TGraph::Dijkstra(const size_t target) {
        std::vector<long long> distances (vertexCount, INF);
        distances[target] = 0;
        std::priority_queue< std::pair<long long, size_t> > q;
        q.push (std::make_pair (0, target));

        while (!q.empty()) {
            size_t vertex = q.top().second;
            long long curDistance = -q.top().first;
            q.pop();
            if (curDistance > distances[vertex]) {
                continue;
            }

            if (vertex < adjList.size()) {
                for (size_t j = 0; j < adjList[vertex].size(); ++j) {
                    size_t to = adjList[vertex][j].first;
                    long long cost = adjList[vertex][j].second;

                    if (distances[vertex] + cost < distances[to]) {
                        distances[to] = distances[vertex] + cost;
                        q.push(std::make_pair (-distances[to], to));
                    }
                }
            }
        }

        return distances;
    }

    /*
    * 1. Добавить фиктивную вершину S
    * 2. Запустить Форда-Беллмана
    * 3. Перевесить все ребра в графе
    * 4. Запустить Дейстру для каждой вершины
    */
    std::vector< std::vector<long long> > TGraph::Jonshon() {
        for (size_t i = 0; i < vertexCount; ++i) {
            edges.push_back( {vertexCount, i, 0} );
        }
        ++vertexCount;
        std::vector<long long> newCosts = FordBellman(vertexCount - 1);
        --vertexCount;

        for (size_t fromIdx = 0; fromIdx < vertexCount; ++fromIdx) {
            TVertex & from = adjList[fromIdx];
            for (size_t to = 0; to < from.size(); ++to) {
                from[to].second += (newCosts[fromIdx] - newCosts[from[to].first]);
            }
        }

        std::vector< std::vector<long long> > result (
                vertexCount,
                std::vector<long long> (vertexCount)
                );
        for (size_t from = 0; from < vertexCount; ++from) {
            result[from] = Dijkstra(from);
            for (size_t to = 0; to < result[from].size(); ++to) {
                if (result[from][to] != INF) {
                    result[from][to] += (newCosts[to] - newCosts[from]);
                }
            }
        }

        return result;
    }

} // namespace NMyGraph
