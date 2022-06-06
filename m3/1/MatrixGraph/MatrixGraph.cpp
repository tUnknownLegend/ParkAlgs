#include "MatrixGraph.h"
#include <algorithm>

MatrixGraph::MatrixGraph(int count) {
    adjMatrix.resize(count);
    for (auto &l: adjMatrix)
        l.resize(count);
}

MatrixGraph::MatrixGraph(const IGraph &graph) : MatrixGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i)
        for (auto &el: graph.GetNextVertices(i))
            adjMatrix[i][el] = 1;
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjMatrix.size());
    assert(to >= 0 && to < adjMatrix.size());
    adjMatrix[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return adjMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    vector<int> nextVerticies = {};

    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[vertex][i] != 0)
            nextVerticies.push_back(i);
    }
    return nextVerticies;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    vector<int> prevVerticies = {};

    for (int from = 0; from < adjMatrix.size(); ++from) {
        if (adjMatrix[from][vertex] != 0)
            prevVerticies.push_back(from);
    }

    return prevVerticies;
}