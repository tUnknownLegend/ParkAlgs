#ifndef INC_1_ARCGRAPH_H
#define INC_1_ARCGRAPH_H

#include <cassert>
#include <queue>
#include "../IGraph/IGraph.h"

using std::vector;
using std::queue;
using std::pair;

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int count);

    explicit ArcGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<pair<int, int>> adjArc;
    unsigned int amtOfVertices = 0;
};

#endif //INC_1_ARCGRAPH_H
