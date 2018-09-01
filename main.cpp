#include <iostream>
#include "List.h"
#include "HGraph.h"
using namespace std;

int main() {

    //HGraph hGraph(12,18);

//    hGraph.addEdge(1,2);
//    //hGraph.printGraph();
//    hGraph.addEdge(2,3);
//    //hGraph.printGraph();
//    hGraph.addEdge(2,4);
//    //hGraph.printGraph();
//    hGraph.addEdge(2,7);
//    //hGraph.printGraph();
//    hGraph.addEdge(2,12);
//    //hGraph.printGraph();
//
//    hGraph.addEdge(3,4);
//    //hGraph.printGraph();
//    hGraph.addEdge(3,5);
//    //hGraph.printGraph();
//
//    hGraph.addEdge(3,6);
//    //hGraph.printGraph();
//    hGraph.addEdge(3,7);
//    //hGraph.printGraph();
//    hGraph.addEdge(6,7);
//    //hGraph.printGraph();
//
//    hGraph.addEdge(6,8);
//    //hGraph.printGraph();
//    hGraph.addEdge(6,11);
//    //hGraph.printGraph();
//    hGraph.addEdge(8,9);
//    //hGraph.printGraph();
//    hGraph.addEdge(8,10);
//    //hGraph.printGraph();
//    hGraph.addEdge(8,12);
//    //hGraph.printGraph();
//
//    hGraph.addEdge(9,10);
//    //hGraph.printGraph();
//    hGraph.addEdge(9,11);
//    //hGraph.printGraph();
//    hGraph.addEdge(10,12);
//    hGraph.printGraph();
//
//    hGraph.addEdge(9, 12);
//    hGraph.printGraph();
//
//    //hGraph.removeEdge(9,10);
//    //hGraph.printGraph();
//
//    int total = 0;
//    for(int i = 1; i<=12; i++){
//
//        cout << "i = " << i << ": ";
//
//        total = total + hGraph.findEdgeNeigh(i);
//    }
//
//    cout << "triangle number: " << total/3 << endl;

    FILE *in = fopen("../dolphins.txt", "r");
    if(in == NULL){

        cout << "files not exist" << endl;
        exit(1);

    }

    int V = 0, E = 0;
    fscanf(in ,"%d %d", &V, &E);
    HGraph hGraph(V, E);

    hGraph.graph.reserve(V+1);

    int x = 0, y = 0;

    while(fscanf(in, "%d %d", &x, &y) != EOF){

        hGraph.addEdge(x+1, y+1);

    }

    fclose(in);

    int total = 0;
    for(int i = 1; i<=V; i++){

        cout << "i = " << i << ": ";

        total = total + hGraph.findEdgeNeigh(i);
    }

    cout << "triangle number: " << total/3 << endl;





    return 0;
}