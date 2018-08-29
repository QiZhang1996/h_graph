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

    if(graph[x].deg == 0 || graph[x].HSet.size() == 0){

        return;
    }

    for(vector<HNode>::iterator it = graph[x].HSet.begin(); it != graph[x].HSet.end();){

        if(graph[x].deg+1 < graph[it->npoint].deg){

            HNode node = graph[it->npoint].NSet.getHNode(it->lpoint, it->ppoint);

            graph[it->npoint].NSet.deleteSubList(it->lpoint, it->ppoint);

            int pos = graph[it->npoint].NSet.findNsub(graph[x].deg);

            if(graph[it->npoint].NSet.getSubListLength(pos) == 0){

                graph[it->npoint].NSet.deleteList(it->lpoint);

                if(graph[it->npoint].NSet.length >= it->lpoint){

                    for(int i = it->lpoint; i <= graph[it->npoint].NSet.length; i++){

                        for(int j = 1; j <= graph[it->npoint].NSet.getSubListLength(i); j++){

                            HNode hnode = graph[it->npoint].NSet.getHNode(i, j);
                            graph[hnode.npoint].HSet[hnode.ppoint-1].lpoint--;

                        }
                    }
                }

            } else{

                for(int i = it->ppoint; i <= graph[it->npoint].NSet.getSubListLength(pos); i++) {

                    HNode index = graph[it->npoint].NSet.getItemInList(pos, i);
                    graph[index.npoint].HSet[index.ppoint - 1].ppoint--;
                }

            }

            if(graph[it->npoint].NSet.findNsub(graph[x].deg + 1) == 0){

                ListNode *ls = new ListNode();
                SubList *sl = new SubList();
                ls->subList = sl;
                ls->NDeg = graph[x].deg+1;
                graph[it->npoint].NSet.insert(ls);

            }

            int i = graph[it->npoint].NSet.findNsub(graph[x].deg + 1);
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

            int pos = graph[it->npoint].NSet.findNsub(graph[x].deg);

            if(graph[it->npoint].NSet.getSubListLength(pos) == 0){

                graph[it->npoint].NSet.deleteList(it->lpoint);

                if(graph[it->npoint].NSet.length >= it->lpoint){

                    for(int i = it->lpoint; i <= graph[it->npoint].NSet.length; i++){

                        for(int j = 1; j <= graph[it->npoint].NSet.getSubListLength(i); j++){

                            HNode hnode = graph[it->npoint].NSet.getHNode(i, j);
                            graph[hnode.npoint].HSet[hnode.ppoint-1].lpoint--;

                        }
                    }
                }
            }
            else{

                for(int i = it->ppoint; i <= graph[it->npoint].NSet.getSubListLength(pos); i++) {

                    HNode index = graph[it->npoint].NSet.getItemInList(pos, i);
                    graph[index.npoint].HSet[index.ppoint - 1].ppoint--;
                }

            }
            graph[it->npoint].HSet.emplace_back(node);

            it->ppoint = graph[it->npoint].HSet.size();
            it->lpoint = -1;
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
                    graph[iter->npoint].HSet[iter->ppoint-1].ppoint--;

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
    nodex.lpoint = i;

    graph[y].HSet.emplace_back(nodex);


}

int HGraph::addEdge(int x, int y){

    cout << "----------------------------------------------------------------" << endl;
    cout << "insert V" << x << " and V" << y <<endl;

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

void HGraph::moveNeighborRe(int x){

    cout << "x = " << x << endl;
    if(graph[x].deg == 0 || graph[x].HSet.size() == 0){

        return;
    }

    for(vector<HNode>::iterator it = graph[x].HSet.begin(); it != graph[x].HSet.end();){

        if(graph[x].deg+1 < graph[it->npoint].deg){

            HNode node = graph[it->npoint].NSet.getHNode(it->lpoint, it->ppoint);

            graph[it->npoint].NSet.deleteSubList(it->lpoint, it->ppoint);

            if(graph[it->npoint].NSet.getSubListLength(it->lpoint) == 0){

                graph[it->npoint].NSet.deleteList(it->lpoint);

                if(graph[it->npoint].NSet.length >= it->lpoint){

                    for(int i = it->lpoint; i <= graph[it->npoint].NSet.length; i++){

                        for(int j = 1; j <= graph[it->npoint].NSet.getSubListLength(i); j++){

                            HNode hnode = graph[it->npoint].NSet.getHNode(i, j);
                            graph[hnode.npoint].HSet[hnode.ppoint-1].lpoint--;

                        }
                    }
                }

            } else{

                for(int i = it->ppoint; i <= graph[it->npoint].NSet.getSubListLength(it->lpoint); i++){

                    HNode node = graph[it->npoint].NSet.getHNode(it->lpoint, i);
                    graph[node.npoint].HSet[node.ppoint-1].ppoint--;

                }

            }

            if(graph[it->npoint].NSet.findNsub(graph[x].deg) == 0){

                ListNode *ls = new ListNode();
                SubList *sl = new SubList();
                ls->subList = sl;
                ls->NDeg = graph[x].deg;
                graph[it->npoint].NSet.insert(ls);

            }
            int i = graph[it->npoint].NSet.findNsub(graph[x].deg);
            graph[it->npoint].NSet.insertSubList(node, i);

            it->lpoint = i;
            it->ppoint = graph[it->npoint].NSet.getSubListLength(i);

            it++;

        }else if(graph[x].deg+1 == graph[it->npoint].deg){

            HNode node = graph[it->npoint].HSet[it->ppoint-1];
            graph[it->npoint].HSet.erase(graph[it->npoint].HSet.begin()+it->ppoint-1);

            for(int i =  it->ppoint; i <= graph[it->npoint].HSet.size(); i++){

                HNode hNode = graph[it->npoint].HSet[i-1];
                if(hNode.lpoint == -1){

                    graph[hNode.npoint].HSet[hNode.ppoint-1].ppoint--;

                }
                else
                {
                    HNode hNode1 = graph[hNode.npoint].NSet.getHNode(hNode.lpoint, hNode.ppoint);
                    hNode1.ppoint--;
                    graph[hNode.npoint].NSet.changeOneList(hNode.lpoint,hNode.ppoint, hNode1);

                }
            }

            if(graph[it->npoint].NSet.findNsub(graph[x].deg) == 0){

                ListNode *ls = new ListNode();
                SubList *sl = new SubList();
                ls->subList = sl;
                ls->NDeg = graph[x].deg;
                graph[it->npoint].NSet.insert(ls);

            }
            int i = graph[it->npoint].NSet.findNsub(graph[x].deg);
            graph[it->npoint].NSet.insertSubList(node, i);

            it->ppoint = graph[it->npoint].NSet.getSubListLength(i);
            it->lpoint = i;

            it++;


        }

    }

    if(graph[x].NSet.findNsub(graph[x].deg != 0)){

        int pos = graph[x].NSet.findNsub(graph[x].deg);
        //
        for(int i = 1; i <= graph[x].NSet.getSubListLength(pos); i++){

            HNode node = graph[x].NSet.getHNode(pos, i);

            graph[x].HSet.emplace_back(node);

            graph[node.npoint].HSet[node.ppoint-1].lpoint = -1;
            graph[node.npoint].HSet[node.ppoint-1].ppoint = graph[x].HSet.size();

            graph[x].NSet.deleteSubList(pos, i);

            if(graph[x].NSet.getSubListLength(pos) == 0){

                graph[x].NSet.deleteList(pos);
                //change number l;
                if(graph[x].NSet.length >= pos){

                    for(int i = pos; i <= graph[x].NSet.length; i++){

                        for(int j = 1; j <= graph[x].NSet.getSubListLength(i); j++){

                            HNode hnode = graph[x].NSet.getHNode(i, j);
                            graph[hnode.npoint].HSet[hnode.ppoint-1].lpoint--;

                        }
                    }
                }

            } else{

                for(int j = i; j <= graph[x].NSet.getSubListLength(pos); j++){

                    HNode node = graph[x].NSet.getHNode(pos, j);
                    graph[node.npoint].HSet[node.ppoint-1].ppoint--;

                }

            }

        }

    }

}

int HGraph::removeEdgeSub(int x, int y){

    vector<HNode>::iterator it;
    HNode node;
    for(it = graph[y].HSet.begin(); it != graph[y].HSet.end(); ) {

        if (it->npoint == x) {

            node = *it;
            graph[y].HSet.erase(it);

            vector<HNode>::iterator iter = it;
            for(; iter != graph[y].HSet.end(); iter++){

                if(iter->lpoint == -1){
                    graph[iter->npoint].HSet[iter->ppoint-1].ppoint--;

                } else{
                    HNode hNode = graph[it->npoint].NSet.getHNode(iter->lpoint, iter->ppoint);
                    hNode.ppoint--;
                    graph[iter->npoint].NSet.changeOneList(iter->lpoint, iter->ppoint, hNode);
                }
            }

            break;

        } else {

            it++;
        }
    }

    graph[x].NSet.deleteSubList(node.lpoint, node.ppoint);
    if(graph[x].NSet.getSubListLength(node.lpoint) == 0){

        graph[x].NSet.deleteList(node.lpoint);

        if(graph[x].NSet.length >= node.lpoint){

            for(int i = node.lpoint; i <= graph[x].NSet.length; i++){

                for(int j = 1; j <= graph[x].NSet.getSubListLength(i); j++){

                    HNode hnode = graph[x].NSet.getHNode(i, j);
                    graph[hnode.npoint].HSet[hnode.ppoint-1].lpoint--;

                }
            }
        }


    }else{

        for(int i = node.ppoint; i <= graph[x].NSet.getSubListLength(node.lpoint); i++){

            int pos = node.lpoint;
            HNode node = graph[x].NSet.getHNode(pos, i);
            graph[node.npoint].HSet[node.ppoint-1].ppoint--;

        }
    }

}

int HGraph::removeEdge(int x, int y){


    cout << "----------------------------------------------------------------" << endl;
    cout << "remove V" << x << " and V" << y <<endl;
    cout << "V" << x << "(deg) = " << graph[x].deg << ", V" << y << "(deg) = " << graph[y].deg << endl;

    //remove x from
    if(graph[x].deg > graph[y].deg){

        removeEdgeSub(x, y);

    } else if(graph[x].deg == graph[y].deg){

        for(vector<HNode>::iterator it = graph[x].HSet.begin(); it != graph[x].HSet.end(); ){

            if(it->npoint == y){
                graph[x].HSet.erase(it);

                vector<HNode>::iterator iter = it;
                for(; iter != graph[x].HSet.end(); iter++){

                    if(iter->lpoint == -1){
                        graph[iter->npoint].HSet[iter->ppoint-1].ppoint--;

                    } else{
                        HNode hNode = graph[it->npoint].NSet.getHNode(iter->lpoint, iter->ppoint);
                        hNode.ppoint--;
                        graph[iter->npoint].NSet.changeOneList(iter->lpoint, iter->ppoint, hNode);
                    }
                }

                break;

            }
            else{

                it++;
            }

        }


        for(vector<HNode>::iterator it = graph[y].HSet.begin(); it != graph[y].HSet.end(); ){

            if(it->npoint == x){

                graph[y].HSet.erase(it);

                vector<HNode>::iterator iter = it;
                for(; iter != graph[y].HSet.end(); iter++){

                    if(iter->lpoint == -1){
                        graph[iter->npoint].HSet[iter->ppoint-1].ppoint--;

                    } else{
                        HNode hNode = graph[it->npoint].NSet.getHNode(iter->lpoint, iter->ppoint);
                        hNode.ppoint--;
                        graph[iter->npoint].NSet.changeOneList(iter->lpoint, iter->ppoint, hNode);
                    }
                }

                break;

            }
            else{

                it++;
            }

        }


    }else
    {

        removeEdgeSub(y, x);

    }

    graph[x].deg--;
    graph[y].deg--;

    printGraph();
    moveNeighborRe(x);
    moveNeighborRe(y);

}

bool HGraph::queryAdj(int x, int y){

    if(graph[x].deg <= graph[y].deg){

        vector<HNode>::iterator it;
        for(it = graph[x].HSet.begin(); it != graph[x].HSet.end(); it++){

            if(it->npoint == y){

                return true;

            }

        }

        return false;

    } else{

        vector<HNode>::iterator it;
        for(it = graph[y].HSet.begin(); it != graph[y].HSet.end(); it++){

            if(it->npoint == x){

                return true;

            }

        }

        return false;


    }


}

int HGraph::findEdgeNeigh(int x){

    vector<pair<int, int>> edge;
    int flag[MAX_VERTEX+1];
    memset(flag, 0, MAX_VERTEX+1);

    ListNode * p=graph[x].NSet.pHead->pNext;
    while(p!=NULL)
    {
        SubList *s = p->subList;

        SubNode * p2=s->pHead->pNext;
        while(p2!=NULL)
        {
            flag[p2->npoint] = 1;
            p2=p2->pNext;
        }

        p=p->pNext;

    }
    vector<HNode>::iterator it;
    for(it = graph[x].HSet.begin(); it != graph[x].HSet.end(); it++){

        flag[it->npoint] = 1;

    }


    p=graph[x].NSet.pHead->pNext;
    while(p!=NULL)
    {
        SubList *s = p->subList;
        SubNode * p2=s->pHead->pNext;
        while(p2!=NULL)
        {
            vector<HNode>::iterator it;
            for(it = graph[p2->npoint].HSet.begin(); it != graph[p2->npoint].HSet.end(); it++){

                if(graph[p2->npoint].deg == graph[it->npoint].deg && flag[it->npoint] == 1){

                    flag[p2->npoint] = 2;
                    edge.emplace_back(it->npoint, p2->npoint);



                }else if(flag[it->npoint] == 1){

                    edge.emplace_back(it->npoint, p2->npoint);

                }


            }
            p2=p2->pNext;
        }

        p=p->pNext;

    }

    vector<HNode>::iterator it1;
    for(it1 = graph[x].HSet.begin(); it1 != graph[x].HSet.end(); it1++){

        vector<HNode>::iterator it2;
        for(it2 = graph[it1->npoint].HSet.begin(); it2 != graph[it1->npoint].HSet.end(); it2++){

            if(graph[it1->npoint].deg == graph[it2->npoint].deg && flag[it2->npoint] == 1){

                flag[it1->npoint] = 2;
                edge.emplace_back(it2->npoint, it1->npoint);



            }else if(flag[it2->npoint] == 1){

                edge.emplace_back(it2->npoint, it1->npoint);

            }
        }


    }


    vector<pair<int, int>>::iterator edgeit;
    for(edgeit = edge.begin(); edgeit != edge.end(); edgeit++){

        cout << "(" << edgeit->first << ", " << edgeit->second << "), ";

    }

    cout << endl;
    return edge.size();




}
