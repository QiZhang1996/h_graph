//
// Created by Rose on 2018/8/21.
//

#ifndef HGRAPH2_SUBLIST_H
#define HGRAPH2_SUBLIST_H
#include<iostream>

using namespace std;

class HNode{
public:

    int ppoint;
    int lpoint;
    int npoint;
};

class SubNode{
public:

    int ppoint;
    int lpoint;
    int npoint;

    SubNode * pNext;
    SubNode * pLast;
};

class SubList
{
public:
    SubNode * pHead;
    SubNode * pTail;
    int length;
public:
    SubList(){

        this->length = 0;
        pHead=new SubNode();
        pHead->pLast=NULL;
        pTail=pHead;

    }
    SubList(int ip, int il, int in)
    {
        this->length++;
        pHead=new SubNode();
        pHead->pLast=NULL;
        pTail=pHead;

        SubNode * temp=new SubNode();

        temp->ppoint = ip;
        temp->lpoint = il;
        temp->npoint = in;

        temp->pNext=NULL;
        temp->pLast=pTail;
        pTail->pNext=temp;
        pTail=temp;

    }

    ~SubList()
    {
        SubNode * q;
        SubNode * p=pHead->pNext;
        while(p!=NULL)
        {
            q=p;
            p=p->pNext;
            delete q;
        }
        p=NULL;
        q=NULL;
    }
    void traverseList(); //正向遍历
    void traverseListReturn(); //逆向遍历
    void clearList();//清空
    void deleteList(int position);
    HNode getNodeInList(int position);
    void insertNode(HNode hNode);
    void changeList(int position, int flag);
    void changeOneList(HNode hNode, int position);




};


#endif //HGRAPH2_SUBLIST_H
