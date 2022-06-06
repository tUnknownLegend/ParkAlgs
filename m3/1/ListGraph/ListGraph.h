#ifndef INC_1_LISTGRAPH_H
#define INC_1_LISTGRAPH_H

#include <cassert>
#include <queue>
#include "../IGraph/IGraph.h"

using std::vector;
using std::queue;

class ListGraph : public IGraph {
public:
    explicit ListGraph(int count);

    explicit ListGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjList;
};

#endif //INC_1_LISTGRAPH_H
