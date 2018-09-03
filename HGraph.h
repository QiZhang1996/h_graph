//
// Created by Rose on 2018/8/21.
//

#ifndef HGRAPH2_HGRAPH_H
#define HGRAPH2_HGRAPH_H
#define MAX_VERTEX 160000

#include <iostream>
#include <vector>
#include "List.h"
#include "tool.h"
#include <cstring>
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
    void printGraph();
    void printVertex(int i);

    int addEdgeSub(int x, int y);
    int addEdge(int x, int y);
    void moveNeighbor(int x);


    int removeEdge(int x, int y);
    int removeEdgeSub(int x, int y);
    void moveNeighborRe(int x);

    bool queryAdj(int x, int y);

    int findEdgeNeigh(int x);




};


#endif //HGRAPH2_HGRAPH_H
