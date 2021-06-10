#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include <cmath>

#include "graph.h"

std::vector< std::vector< NGraph::TEdge > > graphsEdges {
        {   // 0
            {1, 2, 1}
        },
        {   // 1
            {1, 2, 1},
            {1, 3, 5},
            {2, 3, 2},
            {3, 1, 2}
        },
        {   // 2
            {2, 1, 1},
            {3, 2, -2},
            {3, 1, 2},
            {4, 3, -1},
            {4, 1, -4},
            {5, 4, 1},
            {6, 5, 8},
            {6, 1, 10}
        }
};
// vertex Count, edges Count
std::vector< size_t > graphsVertexCount {
        2,     // 0
        3,     // 1
        6,     // 2
};

//// Negative cycles graphs for Ford Bellman algo
std::vector< std::vector< NGraph::TEdge > > negGraphsEdges {
        {   // 0
                {1, 2, 1},

                {2, 1, -2}
        },
        {   // 1
                {1, 2, 1},
                {1, 3, 5},
                {2, 3, 2},
                {3, 1, 2},

                {2, 1, -2}
        },
        {   // 2
                {2, 1, 1},
                {3, 2, -2},
                {3, 1, 2},
                {4, 3, -1},
                {4, 1, -4},
                {5, 4, 1},
                {6, 5, 8},
                {6, 1, 10},

                {1, 3, -7}
        }
};

//// FordBellmanSuite

TEST(FordBellmanSuite, FordBellmanAnswerTest) {
    // graph idx, target vertex
    std::vector< std::pair< size_t, size_t > > tests {
            {0, 1},         // 1
            {0, 2},         // 2
            {1, 1},         // 3
            {2, 6}          // 4
    };
    std::vector< std::vector< long long > > expectedResults {
            {0, 1},                 // 1
            {NGraph::INF, 0},       // 2
            {0, 1, 3},              // 3
            {5, 6, 8, 9, 8, 0}      // 4
    };

    for (size_t testIdx = 0; testIdx < tests.size(); ++testIdx) {
        const size_t graphIdx = tests[testIdx].first;
        const size_t target = tests[testIdx].second - 1;
        std::vector<NGraph::TEdge> edges = graphsEdges[graphIdx];
        for (auto& edge : edges) {
            --edge.from;
            --edge.to;
        }
        const size_t vertexCount = graphsVertexCount[graphIdx];
        NGraph::TGraph graph(edges, vertexCount);

        std::vector<long long> expected = expectedResults[testIdx];
        std::vector<long long> result = graph.FordBellman(target);

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

TEST(FordBellmanSuite, FordBellmanNegativeCycleTest) {

    for (size_t graphIdx = 0; graphIdx < negGraphsEdges.size(); ++graphIdx) {
        std::vector<NGraph::TEdge> edges = negGraphsEdges[graphIdx];
        for (auto& edge : edges) {
            --edge.from;
            --edge.to;
        }

        const size_t vertexCount = graphsVertexCount[graphIdx];
        NGraph::TGraph graph(edges, vertexCount);
        for (size_t target = 0; target < vertexCount; ++target) {
            ASSERT_THROW(graph.FordBellman(target), std::runtime_error) <<  "FAILED graph #" << graphIdx + 1;
        }
    }
}

//// DijkstraSuite

TEST(DijkstraSuite, DijkstraAnswerTest) {
    // graph idx, target vertex
    std::vector< std::pair< size_t, size_t > > tests {
            {0, 1},         // 1
            {0, 2},         // 2
            {1, 1}          // 3
    };
    std::vector< std::vector< long long > > expectedResults {
            {0, 1},                 // 1
            {NGraph::INF, 0},       // 2
            {0, 1, 3}               // 3
    };

    for (size_t testIdx = 0; testIdx < tests.size(); ++testIdx) {
        const size_t graphIdx = tests[testIdx].first;
        const size_t target = tests[testIdx].second - 1;
        std::vector<NGraph::TEdge> edges = graphsEdges[graphIdx];
        for (auto& edge : edges) {
            --edge.from;
            --edge.to;
        }
        const size_t vertexCount = graphsVertexCount[graphIdx];
        NGraph::TGraph graph(edges, vertexCount);

        std::vector<long long> expected = expectedResults[testIdx];
        std::vector<long long> result = graph.Dijkstra(target);

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

//// JonshonSuite

TEST(JonshonSuite, JonshonAnswerTest) {
    std::vector<size_t> tests {
        0,
        1
    };

    std::vector< std::vector< std::vector< long long > > > expectedResults {
            { // 1
                    {0, 1},
                    {NGraph::INF, 0}
            },
            { // 2
                    {0, 1, 3},
                    {4, 0, 2},
                    {2, 3, 0}
            }
    };

    for (size_t testIdx = 0; testIdx < tests.size(); ++testIdx) {
        const size_t graphIdx = tests[testIdx];
        std::vector<NGraph::TEdge> edges = graphsEdges[graphIdx];
        for (auto& edge : edges) {
            --edge.from;
            --edge.to;
        }
        const size_t vertexCount = graphsVertexCount[graphIdx];
        NGraph::TGraph graph(edges, vertexCount);

        std::vector< std::vector<long long> > expected = expectedResults[testIdx];
        std::vector< std::vector<long long> > result = graph.Jonshon();

        ASSERT_EQ(expected, result) << "FAILED test #" << testIdx + 1;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
