/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    address=-1;
    height=0;
    par=NULL;
    left=NULL;
    right=NULL;
}

SymNode::SymNode(string k){
    key=k;
    address=-1;
    height=1;
    par=NULL;
    left=NULL;
    right=NULL;
}

int get_height(SymNode* node){
    if(node==NULL){
        return 0;
    }
    return node->height;
}


void HeightUpdationNode(SymNode* node){
    if(node==NULL){
        return;
    }
    node->height= 1 + std::max(get_height(node->left),get_height(node->right));
}


SymNode* LeftRotation(SymNode* node){
    SymNode* a = node->right;
    SymNode* b= a->left;

    //now rotating
    a->left=node;
    node->right=b;

    //updating parents
    if(node!=NULL){
        node->par=a;
    }
    if(b!=NULL){
        b->par=node;
    }
    

    HeightUpdationNode(node);
    HeightUpdationNode(a);

    return a;
}

SymNode* RightRotation(SymNode* node){
    SymNode* a=node->left;
    SymNode* b=a->right;

    //now rotating

    a->right=node;
    node->left=b;
    
    //updating parents
    
    if(node!=NULL){
        node->par=a;
    }
    if(b!=NULL){
        b->par=node;
    }

    HeightUpdationNode(node);
    HeightUpdationNode(a);

    return a;

}


SymNode* SymNode::LeftLeftRotation(){
    return RightRotation(this);
}

SymNode* SymNode::RightRightRotation(){
    return LeftRotation(this);
}

SymNode* SymNode::LeftRightRotation(){
    this->left=LeftRotation(this->left);
    return RightRotation(this);
}

SymNode* SymNode::RightLeftRotation(){
    this->right=RightRotation(this->right);
    return LeftRotation(this);
}

SymNode::~SymNode(){
    key="";
    address=-1;
    par=NULL;
    left=NULL;
    right=NULL;
    height=0;
}