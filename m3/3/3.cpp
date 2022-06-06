/*
 * Задача 3. «Города» (4 балла) *
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <set>

using std::vector;
using std::queue;
using std::pair;
using std::set;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual vector<pair<int, int>> GetNextVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    ListGraph(int count);

    explicit ListGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to, int weight) override;

    virtual int VerticesCount() const override;

    virtual vector<pair<int, int>> GetNextVertices(int vertex) const override;

private:
    vector<vector<pair<int, int> >> adjList = {};
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

void ListGraph::AddEdge(int from, int to, int weight) {
    assert(from >= 0 && from < adjList.size());
    assert(to >= 0 && to < adjList.size());
    adjList[from].emplace_back(weight, to);
    adjList[to].emplace_back(weight, from);
}

int ListGraph::VerticesCount() const {
    return adjList.size();
}

vector<std::pair<int, int>> ListGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjList.size());
    return adjList[vertex];
}

bool Relax(vector<int> &vecWeight, const int &from, pair<int, int> &currentWeight) {
    return (vecWeight[currentWeight.second] > vecWeight[from] + currentWeight.first);
}

void swapAndEmplace(vector<int> &vecWeight, set<pair<int, int>> &length, pair<int, int> &currentWeight) {
    std::swap(vecWeight[currentWeight.second], currentWeight.first);
    vecWeight[currentWeight.second] += vecWeight[length.begin()->second];
    length.emplace(vecWeight[currentWeight.second], currentWeight.second);
}

int GetLengthOfFastestRoute(const IGraph &graph, const int &from, const int &to) {
    vector<int> vecWeight(graph.VerticesCount(), INT_MAX);
    vecWeight[from] = 0;

    set<pair<int, int>> length{std::make_pair(vecWeight[from], from)};

    while (!length.empty()) {
        vector<pair<int, int> > nextVertex = graph.GetNextVertices(length.begin()->second);

        for (auto &i: nextVertex) {
            if (vecWeight[i.second] == INT_MAX)
                swapAndEmplace(vecWeight, length, i);
            else if (Relax(vecWeight, length.begin()->second, i)) {
                length.erase(i);
                swapAndEmplace(vecWeight, length, i);
            }
        }
        length.erase(length.begin());
    }
    return vecWeight[to];
}

int main() {
    int amtOfCites = 0;
    std::cin >> amtOfCites;
    IGraph *g = new ListGraph(amtOfCites);

    int amtOfRoads = 0;
    std::cin >> amtOfRoads;
    int from = 0;
    int to = 0;
    int weight = 0;

    for (int i = 0; i < amtOfRoads; ++i) {
        std::cin >> from >> to >> weight;
        g->AddEdge(from, to, weight);
    }

    std::cin >> from >> to;
    std::cout << GetLengthOfFastestRoute(*g, from, to);
    delete g;
}
