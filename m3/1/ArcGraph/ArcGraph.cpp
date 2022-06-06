#include <algorithm>
#include "ArcGraph.h"

ArcGraph::ArcGraph(int count) : amtOfVertices(count) {}

ArcGraph::ArcGraph(const IGraph &graph) : ArcGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i)
        for (auto &el: graph.GetNextVertices(i))
            adjArc.emplace_back(i, el);
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjArc.size());
    assert(to >= 0 && to < adjArc.size());
    adjArc.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return amtOfVertices;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjArc.size());
    vector<int> nextVerticies = {};

    for (auto &i: adjArc) {
        if (i.first == vertex)
            nextVerticies.push_back(i.second);
    }
    return nextVerticies;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjArc.size());
    vector<int> prevVerticies = {};

    for (auto &i: adjArc) {
        if (i.second == vertex)
            prevVerticies.push_back(i.first);
    }
    return prevVerticies;
}