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

bool BFS(const IGraph &graph, int vertex) {
    vector<int> visited(graph.VerticesCount(), 0);
    vector<int> Visited(graph.VerticesCount(), false);
    queue<int> bfsQueue;
    bfsQueue.push(vertex);
    Visited[vertex] = true;
    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();
        vector<int> adjList = graph.GetNextVertices(current);
        for (int &i: adjList) {
            if (!Visited[i]) {
                bfsQueue.push(i);
                Visited[i] = true;
            }

            if (visited[i] < 2)
                visited[i] += 1;
            else
                return false;
        }
    }
    return true;
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

    int amtOfVisited = BFS(*g, 1);

    std::cout << amtOfVisited;
    delete g;
}