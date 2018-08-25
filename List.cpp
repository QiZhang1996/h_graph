//
// Created by Rose on 2018/8/21.
//

#include "List.h"
int List::traverseList()
{
    ListNode * p=pHead->pNext;
    if(p == NULL){

        return 0;
    }
    while(p!=NULL)
    {
        cout<<"N(" << p->NDeg << "): ";
        SubList *s = p->subList;
        s->traverseList();
        p=p->pNext;
        //cout << endl;
    }
    return 1;

}

void List::traverseListReturn()//逆向遍历
{
    ListNode * p=pTail;
    while(p->pLast!=NULL)
    {

        cout<<"N(" << p->NDeg << "): " <<endl;
        SubList *s = p->subList;
        s->traverseList();
        p=p->pLast;
    }
}

void List::insertList(int ndeg, SubList* s, int position)//插入数据
{
    ListNode * p=pHead->pNext;
    if(position>length||position<=0)
    {
        cout<<"over stack !"<<endl;
        return;
    }
    for(int i=0;i<position-1;i++)
    {
        p=p->pNext;
    }
    ListNode * temp=new ListNode();
    temp->NDeg = ndeg;
    temp->subList = s;

    temp->pNext=p;
    temp->pLast=p->pLast;
//    p->pLast->pNext=temp;
    p->pLast=temp;
    length++;

}

void List::clearList()//清空
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

void List::deleteList(int position)//删除指定位置的节点
{
    ListNode * p=pHead->pNext;
    if(position>length||position<=0)
    {
        cout<<"over stack !"<<endl;
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

HNode List::getItemInList(int pos, int position)//查找指定位置的节点
{
    ListNode *p = pHead->pNext;
    if (pos > length || pos <= 0) {
        cout << "-----over stack !" << endl;
        //return ;
    }
    for (int i = 0; i < pos - 1; i++) {
        p = p->pNext;
    }
    HNode node = p->subList->getNodeInList(position);
    return node;
}
void List::insert(ListNode *ls){

    ListNode * temp = ls;
    temp->pNext=NULL;
    temp->pLast=pTail;
    pTail->pNext=temp;
    pTail=temp;
    length++;

}

int List::findNsub(int deg){

    ListNode * p=pHead->pNext;
    int i = 1;
    while(p!=NULL)
    {

        if(p->NDeg == deg){

            return i;
        }
        i++;
        p=p->pNext;
        if(p == NULL){

            return 0;

        }

    }

    return 0;

}

int List::deleteSubList(int pos, int position){

    //pos = pos+1;
    //position = position+1;
    ListNode * p=pHead->pNext;
    for(int i=0;i<pos-1;i++)
    {
        p=p->pNext;
    }
    p->subList->deleteList(position);

    return 1;

}

int List::insertSubList(HNode hNode, int pos){

    ListNode * p=pHead->pNext;
    for(int i=0;i<pos-1;i++)
    {
        p=p->pNext;
    }
    p->subList->insertNode(hNode);

    return 1;

}

HNode List::getHNode(int pos, int position){

    ListNode * p=pHead->pNext;
    for(int i=0;i<pos-1;i++)
    {
        p=p->pNext;
    }
    return p->subList->getNodeInList(position);


}

int List::getSubListLength(int pos){

    ListNode * p=pHead->pNext;
    for(int i=0;i<pos-1;i++)
    {
        p=p->pNext;
    }
    return p->subList->length;

}

void List::changeList(int pos, int position, int flag){


    if(flag == 0){

        ListNode * p=pHead->pNext;
        if(pos>length||pos<=0)
        {
            cout<<"over stack !"<<endl;
            return;
        }
        for(int i=0;i<pos-1;i++)
        {
            p=p->pNext;
        }
        while(p != NULL){

            p->subList->changeList(position, flag);
            p = p->pNext;

        }



    } else if(flag == 1){

        ListNode * p=pHead->pNext;
        if(pos>length||pos<=0)
        {
            cout<<"over stack out !"<<endl;
            return;
        }
        for(int i=0;i<pos-1;i++)
        {
            p=p->pNext;
        }


        p->subList->changeList(position, flag);


    }

}

void List::changeOneList(int pos, int position, HNode hNode){

    ListNode * p=pHead->pNext;
    if(pos>length||pos<=0)
    {
        cout<<"over stack out !"<<endl;
        return;
    }
    for(int i=0;i<pos-1;i++)
    {
        p=p->pNext;
    }
    p->subList->changeOneList(hNode, position);

}


