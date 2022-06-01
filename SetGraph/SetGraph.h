#ifndef INC_1_SETGRAPH_H
#define INC_1_SETGRAPH_H

#include <cassert>
#include <queue>
#include <unordered_set>
#include "../IGraph/IGraph.h"

using std::unordered_set;
using std::vector;
using std::queue;

class SetGraph : public IGraph {
public:
    explicit SetGraph(int count);

    explicit SetGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<unordered_set<int>> adjSet;
};

#endif //INC_1_SETGRAPH_H
