#include <iostream>
#include "List.h"
#include "HGraph.h"
using namespace std;

int main() {

    HGraph hGraph(12,18);

    hGraph.addEdge(1,2);
    //hGraph.printGraph();
    hGraph.addEdge(2,3);
    //hGraph.printGraph();
    hGraph.addEdge(2,4);
    //hGraph.printGraph();
    hGraph.addEdge(2,7);
    //hGraph.printGraph();
    hGraph.addEdge(2,12);
    //hGraph.printGraph();

    hGraph.addEdge(3,4);
    //hGraph.printGraph();
    hGraph.addEdge(3,5);
    //hGraph.printGraph();

    hGraph.addEdge(3,6);
    //hGraph.printGraph();
    hGraph.addEdge(3,7);
    //hGraph.printGraph();
    hGraph.addEdge(6,7);
    //hGraph.printGraph();

    hGraph.addEdge(6,8);
    //hGraph.printGraph();
    hGraph.addEdge(6,11);
    //hGraph.printGraph();
    hGraph.addEdge(8,9);
    //hGraph.printGraph();
    hGraph.addEdge(8,10);
    //hGraph.printGraph();
    hGraph.addEdge(8,12);
    //hGraph.printGraph();

    hGraph.addEdge(9,10);
    //hGraph.printGraph();
    hGraph.addEdge(9,11);
    //hGraph.printGraph();
    hGraph.addEdge(10,12);
    hGraph.printGraph();

    hGraph.addEdge(9, 12);
    hGraph.printGraph();

    //hGraph.removeEdge(9,10);
    //hGraph.printGraph();

    int total = 0;
    for(int i = 1; i<=12; i++){

        cout << "i = " << i << ": ";

        total = total + hGraph.findEdgeNeigh(i);
    }

    cout << "triangle number: " << total/3 << endl;

    return 0;
}