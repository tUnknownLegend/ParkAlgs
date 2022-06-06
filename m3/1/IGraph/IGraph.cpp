#include "IGraph.h"
#include <queue>

using std::vector;
using std::queue;

void BFS(const IGraph &graph, int vertex, void (*visit)(int)) {
    vector<bool> visited(graph.VerticesCount(), false);
    queue<int> bfsQueue;
    bfsQueue.push(vertex);
    visited[vertex] = true;
    while (bfsQueue.size() > 0) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        visit(current);
        vector<int> adjList = graph.GetNextVertices(current);
        for (int i = 0; i < adjList.size(); ++i) {
            if (!visited[adjList[i]]) {
                bfsQueue.push(adjList[i]);
                visited[adjList[i]] = true;
            }
        }
    }
}

bool testGetNext(const vector<IGraph *> &vec) {
    for (auto &i: vec) {
        for (int j = 0; j < vec[0]->VerticesCount(); ++j) {
            if (i->GetNextVertices(j).size() != vec[0]->GetNextVertices(j).size())
                return false;
        }
    }

    return true;
};

bool testGetPrev(const vector<IGraph *> &vec) {
    for (auto &i: vec) {
        for (int j = 0; j < vec[0]->VerticesCount(); ++j) {
            if (i->GetPrevVertices(j).size() != vec[0]->GetPrevVertices(j).size())
                return false;
        }
    }

    return true;
};

bool testCount(const vector<IGraph *> &vec) {
    for (auto &i: vec) {
        if (i->VerticesCount() != vec[0]->VerticesCount())
            return false;
    }
    return true;
}