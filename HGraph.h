//
// Created by Rose on 2018/8/21.
//

#ifndef HGRAPH2_HGRAPH_H
#define HGRAPH2_HGRAPH_H
#define MAX_VERTEX 1000

#include <iostream>
#include <vector>
#include "List.h"

using namespace std;
class Vertex{

public:
    int deg = 0;
    List NSet;
    vector<HNode> HSet;


};


class HGraph {

public:

    int V, E;

    vector<Vertex> graph;

    HGraph(int v, int e){
        V = v;
        E = e;
        graph.resize(V+1);



    }

public:
    int addEdgeSub(int x, int y);
    int addEdage(int x, int y);
    void moveNeighbor(int v);

    void printGraph();


};


#endif //HGRAPH2_HGRAPH_H
