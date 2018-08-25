#include <iostream>
#include "List.h"
#include "HGraph.h"
using namespace std;

int main() {


//    List l;
//    SubList *sl = new SubList();
//    HNode node;
//    node.ppoint = 1;
//    node.lpoint = 2;
//    node.npoint = 3;
//    sl->insertNode(node);
//
//    HNode node2;
//    node2.ppoint = 4;
//    node2.lpoint = 5;
//    node2.npoint = 6;
//    sl->insertNode(node2);
//
//    HNode node3;
//    node3.ppoint = 7;
//    node3.lpoint = 8;
//    node3.npoint = 9;
//    sl->insertNode(node3);
//
//    HNode node4;
//    node4.ppoint = 10;
//    node4.lpoint = 12;
//    node4.npoint = 13;
//    sl->insertNode(node4);
//
//    sl->traverseList();
//
//    ListNode * p = new ListNode();
//    p->subList = sl;
//    p->NDeg = 666;
//
//    ListNode * p2 = new ListNode();
//    p2->subList = sl;
//    p2->NDeg = 888;
//
//    ListNode * p3 = new ListNode();
//    p3->subList = sl;
//    p3->NDeg = 777;
//
//    l.insert(p);
//    l.insert(p2);
//    l.insert(p3);
//    l.traverseList();
//
//    HNode hh = l.getHNode(1,3);
//    cout << hh.ppoint << endl;
//    cout << hh.lpoint << endl;
//    cout << hh.npoint << endl;
//
//    cout <<  l.findNsub(888) << endl;
//    cout << l.length << endl;



    HGraph hGraph(6,7);
    hGraph.addEdage(1,2);
    //hGraph.printGraph();
    hGraph.addEdage(2,3);
    //hGraph.printGraph();
    hGraph.addEdage(2,4);
    //hGraph.printGraph();
    hGraph.addEdage(2,5);
    //hGraph.printGraph();
    hGraph.addEdage(3,5);
    hGraph.printGraph();
    hGraph.addEdage(4,5);
    hGraph.printGraph();
    hGraph.addEdage(5,6);
    hGraph.printGraph();



    return 0;
}