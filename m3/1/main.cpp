#include <iostream>
#include <vector>

#include "ListGraph/ListGraph.h"
#include "MatrixGraph/MatrixGraph.h"
#include "SetGraph/SetGraph.h"
#include "ArcGraph/ArcGraph.h"

int main() {
    IGraph *listG = new ListGraph(9);
    listG->AddEdge(1, 3);
    listG->AddEdge(2, 1);
    listG->AddEdge(2, 3);
    listG->AddEdge(2, 4);
    listG->AddEdge(3, 4);
    listG->AddEdge(4, 5);
    listG->AddEdge(5, 3);
    listG->AddEdge(5, 4);
    listG->AddEdge(6, 1);
    listG->AddEdge(4, 6);
    listG->AddEdge(7, 5);
    listG->AddEdge(1, 7);

    IGraph *matrixG = new MatrixGraph(*listG);
    IGraph *setG = new SetGraph(*listG);
    IGraph *arcG = new ArcGraph(*listG);

    vector<IGraph *> graphs = {listG, matrixG, setG, arcG};

    for (auto &i: graphs) {
        BFS(*i, 2, [](int v) { std::cout << v << ", "; });
        std::cout << "\n";
    }

    std::cout << (testCount(graphs) ? "testCount - OK\n" : "testCount - FAIL\n");
    std::cout << (testGetPrev(graphs) ? "testGetPrev - OK\n" : "testGetPrev - FAIL\n");
    std::cout << (testGetNext(graphs) ? "testGetNext - OK\n" : "testGetNext - FAIL\n");


    delete listG;
    delete matrixG;
    delete setG;
    delete arcG;
}