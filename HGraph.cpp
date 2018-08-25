//
// Created by Rose on 2018/8/21.
//

#include "HGraph.h"

void HGraph::printGraph(){

    for(int i = 1; i <= V; i++){
        cout << "##############################" << endl;
        cout << "V" << i <<  ": d = " << graph[i].deg << endl;
        if(graph[i].NSet.traverseList()==0){

            cout << "N: NULL" << endl;

        }

        cout << "H: ";
        vector<HNode>::iterator it;
        if(graph[i].HSet.empty()){

            cout << "NULL" << endl;
        } else{

            for(it = graph[i].HSet.begin(); it != graph[i].HSet.end(); it++){



                cout << "V" << it->npoint << "[p = " << it->ppoint << ", l = " << it->lpoint << ", n = " << it->npoint <<"]" << ", ";

            }

            cout << endl;

        }

    }

}

void HGraph::moveNeighbor(int x) {

    cout << "x = " << x << endl;
    if(graph[x].deg == 0 || graph[x].HSet.size() == 0){

        return;
    }

    for(vector<HNode>::iterator it = graph[x].HSet.begin(); it != graph[x].HSet.end();){

        if(graph[x].deg+1 < graph[it->npoint].deg){

            HNode node = graph[it->npoint].NSet.getHNode(it->lpoint, it->ppoint);

            graph[it->npoint].NSet.deleteSubList(it->lpoint, it->ppoint);

            if(graph[it->npoint].NSet.getSubListLength(graph[x].deg) == 0){

                graph[it->npoint].NSet.deleteList(it->lpoint);
                //change number l;
                if(graph[it->npoint].NSet.length >= it->lpoint){

                    graph[it->npoint].NSet.changeList(it->lpoint, it->ppoint, 1);
                }

            }

            //改H
            int pos = graph[it->npoint].NSet.findNsub(graph[x].deg);
            for(int i = it->ppoint; i <= graph[it->npoint].NSet.getSubListLength(pos); i++) {

                HNode index = graph[it->npoint].NSet.getItemInList(pos, i);
                graph[index.npoint].HSet[index.ppoint - 1].ppoint--;
            }


            if(graph[it->npoint].NSet.findNsub(graph[x].deg + 1) == 0){

                ListNode *ls = new ListNode();
                SubList *sl = new SubList();
                ls->subList = sl;
                ls->NDeg = graph[x].deg+1;
                graph[it->npoint].NSet.insert(ls);

            }
            int i = graph[it->npoint].NSet.findNsub(graph[x].deg+1);
            graph[it->npoint].NSet.insertSubList(node, i);

            HNode hh;
            hh.ppoint = graph[it->npoint].NSet.getSubListLength(i);
            hh.lpoint = i;
            hh.npoint = it->npoint;
            graph[x].HSet[node.ppoint-1] = hh;

            it++;

        }else if(graph[x].deg+1 == graph[it->npoint].deg){

            HNode node = graph[it->npoint].NSet.getHNode(it->lpoint, it->ppoint);

            graph[it->npoint].NSet.deleteSubList(it->lpoint, it->ppoint);

            if(graph[it->npoint].NSet.getSubListLength(graph[x].deg) == 0){

                graph[it->npoint].NSet.deleteList(it->lpoint);
                //change number l;
                if(graph[it->npoint].NSet.length >= it->lpoint){

                    graph[it->npoint].NSet.changeList(it->lpoint, it->ppoint, 1);
                }

            }
            graph[it->npoint].HSet.emplace_back(node);

            graph[x].HSet[it->ppoint-1].ppoint = graph[x].HSet.size();
            graph[x].HSet[it->ppoint-1].lpoint = -1;
            graph[x].HSet[it->ppoint-1].npoint = it->npoint;

            it++;


        }else if(graph[x].deg == graph[it->npoint].deg && graph[x].deg != 0){

            if(graph[x].NSet.findNsub(graph[x].deg) == 0){

                ListNode *ls = new ListNode();
                SubList *sl = new SubList();
                ls->subList = sl;
                ls->NDeg = graph[x].deg;
                graph[x].NSet.insert(ls);

            }

            HNode hnode = *it;
            int i = graph[x].NSet.findNsub(graph[x].deg);
            graph[x].NSet.insertSubList(hnode, i);

            HNode hh;
            hh.ppoint = graph[x].NSet.getSubListLength(i);
            hh.lpoint = i;
            hh.npoint = x;
            graph[it->npoint].HSet[it->ppoint-1] = hh;

            it = graph[x].HSet.erase(it);

            //update H
            vector<HNode>::iterator iter = it;
            for(; iter != graph[x].HSet.end(); iter++){

                if(iter->lpoint == -1){
                    //说明下一个互相在H中
                    graph[iter->npoint].HSet[iter->ppoint].ppoint--;

                } else{
                    HNode hNode;
                    hNode.ppoint = iter->ppoint - 1;
                    hNode.lpoint = iter->lpoint;
                    hNode.npoint = iter->npoint;
                    graph[iter->npoint].NSet.changeOneList(iter->lpoint, iter->ppoint, hNode);

                }

            }

        }else
        {
            it++;

        }

    }

}

int HGraph::addEdgeSub(int x, int y){

    //x deg > y deg
    HNode nodex, nodey;

    if(graph[x].NSet.findNsub(graph[y].deg) == 0){

        ListNode *ls = new ListNode();
        SubList *sl = new SubList();
        ls->subList = sl;
        ls->NDeg = graph[y].deg;
        graph[x].NSet.insert(ls);

    }

    nodey.npoint = y;
    nodey.ppoint = graph[y].HSet.size() + 1;
    nodey.lpoint = -1;

    int i = graph[x].NSet.findNsub(graph[y].deg);
    graph[x].NSet.insertSubList(nodey, i);

    nodex.npoint = x;
    nodex.ppoint = graph[x].NSet.getSubListLength(i);
    nodex.lpoint = graph[x].NSet.findNsub(graph[y].deg);

    graph[y].HSet.emplace_back(nodex);


}

int HGraph::addEdage(int x, int y){

    cout << "----------------------------------------------------------------" << endl;
    cout << "insert V" << x << " and V" << y <<endl;
    cout << "V" << x << "(deg) = " << graph[x].deg << ", V" << y << "(deg) = " << graph[y].deg << endl;

    moveNeighbor(x);

    moveNeighbor(y);

    graph[x].deg++;
    graph[y].deg++;

    if(graph[x].deg > graph[y].deg){

        addEdgeSub(x, y);


    } else if(graph[x].deg == graph[y].deg){

        HNode hx, hy;

        hx.lpoint = -1;
        hx.npoint = y;
        hx.ppoint = graph[y].HSet.size()+1;

        hy.lpoint = -1;
        hy.npoint = x;
        hy.ppoint = graph[x].HSet.size()+1;

        graph[x].HSet.emplace_back(hx);
        graph[y].HSet.emplace_back(hy);


    }else{

        addEdgeSub(y, x);

    }
}