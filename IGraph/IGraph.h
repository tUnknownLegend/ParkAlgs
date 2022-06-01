#ifndef INC_1_IGRAPH_H
#define INC_1_IGRAPH_H

#include <iostream>
#include <vector>

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

void BFS(const IGraph &graph, int vertex, void (*visit)(int));

bool testGetNext(const std::vector<IGraph *> &vec);

bool testGetPrev(const std::vector<IGraph *> &vec);

bool testCount(const std::vector<IGraph *> &vec);

#endif //INC_1_IGRAPH_H
