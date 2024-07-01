/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){
    size=0;
    root=NULL;
}
pair<HeapNode* , int>  insertingfindLastnode(HeapNode* node, int size,int i, int lvl, int nodeslastlvl) {//this function gives the place we need to insert the node

    if(node==NULL){
        return make_pair(nullptr,-1);
    }
    if(size<4){
        if(size==1){
            return make_pair(node,-1);
        }
        if(size==2){
            return make_pair(node,0);
        }
        else if(size==3){
            return make_pair(node,1);
        }
    }
    //all base cases done

    // int i=2;
    // int lvl=1;
    // while(i-1 <= size){
    //     i=i*2;
    //     lvl++;
    // }

    //now lvl represents the last lvl filled
    //i=2^lvl;

    if((i/2)-1 == size){
        lvl--;
        i=(i/2);
        nodeslastlvl=nodeslastlvl/2;
    }
    
    // int nodesinlastlvl=1;
    // for(int j=1;j<=lvl-1;j++){
    //     nodesinlastlvl=nodesinlastlvl*2;
    // }
    int actualnodesinlastlvl=size-((i/2)-1);

    if(actualnodesinlastlvl <= nodeslastlvl/2){
        //we need to go left
        size-=((((i/2)-1)/2)+1);
        lvl--;
        i=i/2;
        nodeslastlvl=nodeslastlvl/2;
        pair<HeapNode* , int> p =insertingfindLastnode(node->left,size,i,lvl,nodeslastlvl);
        if(p.second==0){
            return make_pair(p.first,0);
        }
        return make_pair(p.first,1);
        // return make_pair(leftside,0);//return statement
    }
    
    size-=((i-1)/2) + 1;
    lvl--;
    i=i/2;
    nodeslastlvl=nodeslastlvl/2;
    // HeapNode* rightside=findLastnode(node->right,size).first;
    pair<HeapNode* , int> p =insertingfindLastnode(node->right,size,i, lvl ,nodeslastlvl);
    if(p.second==0){
        return make_pair(p.first,0);
    }
    return make_pair(p.first,1);
    
}

pair<HeapNode* , int>  findLastnode(HeapNode* node, int size,int i,int lvl,int nodeslastlvl) {//this function gives the place we need to insert the node
    
    if(node==NULL){
        return make_pair(nullptr,-1);
    }
    if(size<4){
        if(size==1){
            return make_pair(node,-1);
        }
        if(size==2){
            return make_pair(node->left,0);;
        }
        else if(size==3){
            return make_pair(node->right,1);
        }
    }
    //all base cases done

    // int i=2;
    // int lvl=1;
    // while(i-1 <= size){
    //     i=i*2;
    //     lvl++;
    // }
    if((i/2)-1 == size){
        lvl--;
        i=(i/2);
        nodeslastlvl=nodeslastlvl/2;
    }
    //now lvl represents the last lvl filled
    //i=2^lvl;
    // int nodesinlastlvl=1;
    // for(int j=1;j<=lvl-1;j++){
    //     nodesinlastlvl=nodesinlastlvl*2;
    // }
    int actualnodesinlastlvl=size-((i/2)-1);

    if(actualnodesinlastlvl <= nodeslastlvl/2){
        //we need to go left
        size-=((((i/2)-1)/2)+1);
        lvl--;
        i=i/2;
        nodeslastlvl=nodeslastlvl/2;
        pair<HeapNode* , int> p =findLastnode(node->left,size,i,lvl,nodeslastlvl);
        if(p.second==0){
            return make_pair(p.first,0);
        }
        return make_pair(p.first,1);
        // return make_pair(leftside,0);//return statement
    }
    
    size-=((i-1)/2) + 1;
    lvl--;
    i=i/2;
    nodeslastlvl=nodeslastlvl/2;
    // HeapNode* rightside=findLastnode(node->right,size).first;
    pair<HeapNode* , int> p =findLastnode(node->right,size,i,lvl,nodeslastlvl);
    if(p.second==0){
        return make_pair(p.first,0);
    }
    return make_pair(p.first,1);
    
}

void heapifyUp(HeapNode* node){
    while((node->par!=NULL) && (node->val < node->par->val)){
        std::swap(node->val,node->par->val);
        node=node->par;
    }
}

void heapifyDown(HeapNode* root){

    if(root->left==NULL){
        return;
    }

    HeapNode* minNode= root;

    if(minNode->val > root->left->val){
        minNode=root->left;
    }

    if((root->right!=NULL) && (minNode->val > root->right->val)){
        minNode=root->right;
    }

    if(minNode != root){
        std::swap(minNode->val,root->val);
        heapifyDown(minNode);
    }

}

void MinHeap::push_heap(int num){
    if(root==NULL){
        root=new HeapNode(num);
        size++;
        return;
    }
    int i=2;
    int lvl=1;
    while(i-1 <= size+1){
        i=i*2;
        lvl++;
    }
     //now lvl represents the last lvl filled
    //i=2^lvl;

    int nodesinlastlvl=1;
    for(int j=1;j<=lvl-1;j++){
        nodesinlastlvl=nodesinlastlvl*2;
    }
    pair<HeapNode*,int> lastnodepair=insertingfindLastnode(root,size+1,i,lvl,nodesinlastlvl);
    // cout<<"lastnode "<<lastnodepair.first->val<<endl;
    if(lastnodepair.second==0){
        HeapNode* temp= new HeapNode(num);
        lastnodepair.first->left=temp;
        temp->par=lastnodepair.first;
        heapifyUp(temp);
        size++;
        return;
    }
    if(lastnodepair.second==1){
        HeapNode* temp= new HeapNode(num);
        lastnodepair.first->right=temp;
        temp->par=lastnodepair.first;
        heapifyUp(temp);
        size++;
        return;
    }

}



int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    if(root==NULL){
        return;
    }
    else if(size==1){
        delete root;
        size--;
        root=NULL;
    }
    else{
        int i=2;
        int lvl=1;
        while(i-1 <= size){
            i=i*2;
            lvl++;
        }
        int nodesinlastlvl=1;
        for(int j=1;j<=lvl-1;j++){
            nodesinlastlvl=nodesinlastlvl*2;
        }
        HeapNode* lastnode=findLastnode(root,size,i,lvl,nodesinlastlvl).first;
        std::swap(lastnode->val,root->val);
        HeapNode* parentoflastnode=lastnode->par;
        bool flag=true;
        if(parentoflastnode->right==lastnode){
            flag=false;
        }
        delete lastnode;
        size--;
        if(flag==true){
            //was a left child
            parentoflastnode->left=NULL;
            heapifyDown(root);
            return;

        }
        //was a right child
        parentoflastnode->right=NULL;
        heapifyDown(root);
        return;
    }
}

void destroyMinHeap(HeapNode* &node){

    if(node){
        destroyMinHeap(node->left);
        destroyMinHeap(node->right);
        delete node;
        node=NULL;
    }

}

MinHeap::~MinHeap(){
    size=0;
    destroyMinHeap(root);

}

