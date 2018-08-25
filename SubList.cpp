//
// Created by Rose on 2018/8/21.
//

#include "SubList.h"
void SubList::traverseList()
{
    SubNode * p=pHead->pNext;
    while(p!=NULL)
    {
        cout << "V" << p->npoint << "[p = " << p->ppoint << ", l = " << p->lpoint << ", n = " << p->npoint <<"]" << ", ";
        //cout<<"p: " << p->ppoint << ", l: " << p->lpoint <<  ", n: " << p->npoint <<endl;

        p=p->pNext;
    }
    cout << endl;
}

void SubList::traverseListReturn()//逆向遍历
{
    SubNode * p=pTail;
    while(p->pLast!=NULL)
    {
        cout<<"p: " << p->ppoint << ", l: " << p->lpoint <<  ", n: " << p->npoint <<endl;

        p=p->pLast;
    }
}


void SubList::clearList()//清空
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

void SubList::deleteList(int position)//删除指定位置的节点
{
    SubNode * p=pHead->pNext;
    if(position>length||position<=0)
    {
        cout<<"over stack----------- !"<<endl;
        return;
    }
    for(int i=0;i<position-1;i++)
    {
        p=p->pNext;
    }

    if(p->pNext != NULL){
        p->pLast->pNext=p->pNext;
        p->pNext->pLast=p->pLast;
        delete p;
        length--;

    }
    else{

        p->pLast->pNext=p->pNext;
        //p->pNext->pLast=p->pLast;
        p->pLast = pTail;
        delete p;
        length--;

    }



}

HNode SubList::getNodeInList(int position)//查找指定位置的节点
{
    SubNode * p=pHead->pNext;
    if(position>length||position<=0)
    {
        cout<<"over stack !"<<endl;
        //return NULL;
    }
    for(int i=0;i<position-1;i++)
    {
        p=p->pNext;
    }
    HNode node;
    node.ppoint = p->ppoint;
    node.lpoint = p->lpoint;
    node.npoint = p->npoint;
    return node;
}

void SubList::insertNode(HNode hNode) {

    SubNode *temp = new SubNode();
    temp->ppoint = hNode.ppoint;
    temp->lpoint = hNode.lpoint;
    temp->npoint = hNode.npoint;

    temp->pNext = NULL;
    temp->pLast = pTail;
    pTail->pNext = temp;
    pTail = temp;

    length++;


}
void SubList::changeList(int position, int flag) //修改链表中指定位置的节点
{
    if(flag == 0){

        SubNode * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack !"<<endl;
            return;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        while(p != NULL){

            p->lpoint = p->lpoint - 1;
            p = p->pNext;

        }

    }
    else if (flag == 1){

        SubNode * p=pHead->pNext;
        if(position>length||position<=0)
        {
            cout<<"over stack-------- !"<<endl;
            return;
        }
        for(int i=0;i<position-1;i++)
        {
            p=p->pNext;
        }
        while(p != NULL){

            p->ppoint = p->ppoint - 1;
            p = p->pNext;

        }
    }

}

void SubList::changeOneList(HNode hNode, int position){

    SubNode * p=pHead->pNext;
    if(position>length||position<=0)
    {
        cout<<"over stack !"<<endl;
        return;
    }
    for(int i=0;i<position-1;i++)
    {
        p=p->pNext;
    }

    p->ppoint = hNode.ppoint;
    p->lpoint = hNode.lpoint;
    p->npoint = hNode.npoint;

}