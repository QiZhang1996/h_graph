//
// Created by Rose on 2018/8/21.
//

#ifndef HGRAPH2_LIST_H
#define HGRAPH2_LIST_H

#include "SubList.h"

class ListNode {

public:
    int NDeg;

    SubList *subList;

    ListNode * pNext;
    ListNode * pLast;
};

class List{
public:
    ListNode * pHead;
    ListNode * pTail;
    int length;
public:
    List()
    {
        this->length=0;
        pHead=new ListNode();
        pHead->pLast=NULL;
        pTail=pHead;

//        for(int i=0;i<length;i++)
//        {
//            SubNode * temp=new SubNode();
//            cout<<"please enter the no"<<i+1<<" Node's data:";
//            cin>>temp->data;
//            temp->pNext=NULL;
//            temp->pLast=pTail;
//            pTail->pNext=temp;
//            pTail=temp;
//        }
    }

    ~List()
    {
        ListNode * q;
        ListNode * p=pHead->pNext;
        while(p!=NULL)
        {
            q=p;
            p=p->pNext;
            delete q;
        }
        p=NULL;
        q=NULL;
    }

    int traverseList(); //正向遍历
    void traverseListReturn(); //逆向遍历
    void changeList(int pos, int position, int flag);//修改链表中指定位置的节点
    void insertList(int ndeg, SubList* s, int position);//插入数据
    void clearList();//清空
    void deleteList(int position);
    HNode getItemInList(int pos, int position);
    void insert(ListNode *ls);
    int findNsub(int deg);
    int deleteSubList(int pos, int position);
    int insertSubList(HNode hNode, int pos);
    HNode getHNode(int pos, int position);
    int getSubListLength(int pos);
    void changeOneList(int pos, int position, HNode hNode);






};


#endif //HGRAPH2_LIST_H
