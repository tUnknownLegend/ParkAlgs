#ifndef INC_1_MATRIXGRAPH_H
#define INC_1_MATRIXGRAPH_H

#include <cassert>
#include <queue>
#include "../IGraph/IGraph.h"

using std::vector;
using std::queue;

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int count);

    explicit MatrixGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    vector<vector<int>> adjMatrix;
};

#endif //INC_1_MATRIXGRAPH_H
