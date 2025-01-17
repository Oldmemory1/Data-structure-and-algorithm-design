/*程序输入一个字符串（只包含小写字母），请按照字符的输入顺序建立平衡二叉排序树，并分别输出二叉树的先序序列、中序序列和后序序列，最后输出该二叉树向左旋转 90 度后的结构。
例如：向左旋转 90 度后，以每层向里缩进 4 个空格的方式输出，输出结果为：

        i
    g
        f
a
        d
    c
        b

输入：agxnzyimk

输出：
Preorder: xigamknzy
Inorder: agikmnxyz
Postorder: agknmiyzx
Tree:
    z
        y
x
            n
        m
            k
    i
        g
            a*/

#include <bits/stdc++.h>
typedef struct BiTNode{
    char data;
    struct BiTNode *LeftChild,*RightChild;
}BiTNode,*BiTree;

void PreOrder(BiTree T){  //DLR 先序输出
    if(T){
        printf("%c",T->data);
        PreOrder(T->LeftChild);
        PreOrder(T->RightChild);
    }
}

void InOrder(BiTree T){   //LDR 中序输出
    if(T){
        InOrder(T->LeftChild);
        printf("%c",T->data);
        InOrder(T->RightChild);
    }
}

void PostOrder(BiTree T){   //LRD 后序输出
    if(T){
        PostOrder(T->LeftChild);
        PostOrder(T->RightChild);
        printf("%c",T->data);
    }
}

int height(BiTree T){       //返回左右子树中 高度较大的高度
    int leftheight,rightheight;
    if(T==NULL)return 0;
    else{
        leftheight=height(T->LeftChild);
        rightheight=height(T->RightChild);
        return (leftheight>rightheight?leftheight+1:rightheight+1);
    }
}

BiTree singleRotationLL(BiTree T){  //LL 向右转
    BiTree A=T->LeftChild;  //根=左
    T->LeftChild=A->RightChild;
    A->RightChild=T;
    return A;
}

BiTree singleRotationRR(BiTree T){  //RR 向左转
    BiTree A=T->RightChild;
    T->RightChild=A->LeftChild;
    A->LeftChild=T;
    return A;
}

BiTree doubleRotationLR(BiTree T3){  //LR 孩子左转、右转
    BiTree T2,T1;
    T1=T3->LeftChild;
    T2=T1->RightChild;
    T1->RightChild=T2->LeftChild;
    T3->LeftChild=T2->RightChild;
    T2->LeftChild=T1;
    T2->RightChild=T3;
    return T2;
}

BiTree doubleRotationRL(BiTree T1){   //RL 孩子右转、左转
    BiTree T2,T3;
    T3=T1->RightChild;
    T2=T3->LeftChild;
    T1->RightChild=T2->LeftChild;
    T3->LeftChild=T2->RightChild;
    T2->LeftChild=T1;
    T2->RightChild=T3;
    return T2;
}

BiTree insert(char c,BiTree T){
    if(T==NULL){
        T=(BiTree)malloc(sizeof(BiTNode));
        T->data=c;
        T->LeftChild=T->RightChild=NULL;
    }
    else{
        if(c<T->data){
            T->LeftChild=insert(c,T->LeftChild);
            if(height(T->LeftChild)-height(T->RightChild)==2){
                if(c<T->LeftChild->data)T=singleRotationLL(T);
                else T=doubleRotationLR(T);
            }
        }
        else if(c>T->data){
            T->RightChild=insert(c,T->RightChild);
            if(height(T->RightChild)-height(T->LeftChild)==2){
                if(c>T->RightChild->data)T=singleRotationRR(T);
                else T=doubleRotationRL(T);
            }
        }
    }
    return T;
}

void turnTree90DegreeLeft(BiTree T,int depth){    //右根左
    if(T->RightChild)turnTree90DegreeLeft(T->RightChild,depth+1);  
    for(int i=1;i<depth;i++)printf("    ");
    printf("%c\n",T->data);
    if(T->LeftChild)turnTree90DegreeLeft(T->LeftChild,depth+1);
}

BiTree root=NULL;

int main(){
    char ch;
    while(scanf("%c",&ch)&&ch!='\n')root=insert(ch,root);  //按平衡原则插入
    printf("Preorder: "); PreOrder(root); printf("\n");
    printf("Inorder: "); InOrder(root); printf("\n");
    printf("Postorder: "); PostOrder(root); printf("\n");
    printf("Tree:\n"); turnTree90DegreeLeft(root,1);
    return 0;
}
