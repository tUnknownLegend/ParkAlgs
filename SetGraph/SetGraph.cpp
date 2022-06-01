#include "SetGraph.h"
#include <algorithm>

SetGraph::SetGraph(int count) {
    adjSet.resize(count);
}

SetGraph::SetGraph(const IGraph &graph) : SetGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); ++i)
        for (auto &el: graph.GetNextVertices(i))
            adjSet[i].emplace(el);
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjSet.size());
    assert(to >= 0 && to < adjSet.size());
    adjSet[from].emplace(to);
}

int SetGraph::VerticesCount() const {
    return adjSet.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    vector<int> nextVerticies = {};
    //std::copy(adjSet[vertex].begin(), adjSet[vertex].end(), nextVerticies);
    for (auto &i: adjSet[vertex]) nextVerticies.emplace_back(i);
    return nextVerticies;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    vector<int> prevVerticies;
    for (int from = 0; from < adjSet.size(); ++from)
        if (std::find_if(adjSet[from].begin(), adjSet[from].end(),
                         [vertex](const auto &i) {
                             return i == vertex;
                         }) != adjSet[from].end())
            prevVerticies.push_back(from);
    return prevVerticies;
}