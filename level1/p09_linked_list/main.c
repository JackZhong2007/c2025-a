#include<stdio.h>
#include<stdlib.h>
typedef struct SLlist{
    int data;
    struct SLlist*point;
}SLlist;
SLlist*create_SinglyLinkedList(){
    SLlist*headnode=(SLlist*)malloc(sizeof(SLlist));
    headnode->point=NULL;
    return headnode;
}
SLlist*create_node(int data){
    SLlist*new_node=(SLlist*)malloc(sizeof(SLlist));
    new_node->data=data;
    new_node->point=NULL;
    return new_node;
}
void insert(SLlist*headnode,int data){//从单向链表首节点后插入一个节点并赋值
    SLlist*newnode=create_node(data);
    newnode->point=headnode->point;
    headnode->point=newnode;
}
void delete(SLlist*headnode,int data){//删除链表中指定数据对应的节点
    SLlist*nownode=headnode->point;
    SLlist*lastnode=headnode;
    if(headnode->point==NULL){
        printf("There is no more node\n");
        return ;
    }else{
        while(nownode->data!=data){
            if(nownode->point==NULL){//此处可能有问题，if与赋值的顺序问题有待商议
                printf("There is not a node had record this data\n");
                return ;
            }
            lastnode=nownode;
            nownode=nownode->point;
        }
        lastnode->point=nownode->point;
        free(nownode);
    }
}
void print_sllist(SLlist*headnode){
    if(headnode->point==NULL){
        printf("There is no more node\n");
        return ;
    }
    SLlist*nextnode=headnode->point;
    SLlist*nownode=headnode;
    while(nextnode!=NULL){
        printf("%d\n",nextnode->data);
        nownode=nextnode;
        nextnode=nextnode->point;
    }
}
int main(){
    SLlist*headnode=create_SinglyLinkedList();
    insert(headnode,1);
    insert(headnode,2);
    insert(headnode,3);
    print_sllist(headnode);
    delete(headnode,2);
    print_sllist(headnode);
    return 0;
}