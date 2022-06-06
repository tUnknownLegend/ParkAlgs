/*
 * Задача 2. Количество различных путей (3 балла) *
Обязательная задача
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
Требования: сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
*/
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

using std::vector;
using std::queue;

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int count);

    ListGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjList;
};

ListGraph::ListGraph(int count) {
    adjList.resize(count);
}

ListGraph::ListGraph(const IGraph &graph) {
    adjList.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        adjList[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].push_back(to);
    adjList[to].push_back(from);
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}


std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    vector<int> prevVerticies;

    for (int from = 0; from < adjList.size(); ++from)
        for (int i = 0; i < adjList[from].size(); ++i)
            if (adjList[from][i] == vertex)
                prevVerticies.push_back(from);
    return prevVerticies;
}

int BFS(const IGraph &graph, const int &from, const int &to) {
    vector<bool> visited(graph.VerticesCount(), false);
    queue<int> bfsQueue;
    bfsQueue.push(from);
    queue<int> subBFS;
    vector<int> length(graph.VerticesCount(), 0);

    visited[from] = true;
    length[from] = 1;
    while (!bfsQueue.empty()) {
        vector<bool> tempVisited(visited);
        while (!bfsQueue.empty()) {
            int current = bfsQueue.front();
            bfsQueue.pop();
            vector<int> adjList = graph.GetNextVertices(current);

            for (auto &i: adjList) {
                if (!tempVisited[i]) {
                    subBFS.push(i);
                    tempVisited[i] = true;
                }
                if (!visited[i]) {
                    length[i] += length[current];
                }
            }
        }

        while (!subBFS.empty()) {
            int current = subBFS.front();
            bfsQueue.push(current);
            subBFS.pop();
        }
        visited = std::move(tempVisited);
    }

    return length[to];
}

int main() {
    int amtOfVertices = 0;
    std::cin >> amtOfVertices;
    IGraph *g = new ListGraph(amtOfVertices);

    int amtOfEdges = 0;
    std::cin >> amtOfEdges;
    int pFirst = 0;
    int pSecond = 0;

    for (int i = 0; i < amtOfEdges; ++i) {
        std::cin >> pFirst >> pSecond;
        g->AddEdge(pFirst, pSecond);
    }

    std::cin >> pFirst >> pSecond;
    std::cout << BFS(*g, pFirst, pSecond);
    delete g;
}
