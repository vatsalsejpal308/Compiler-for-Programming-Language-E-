/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
//Write your code below this line

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

void destroySymbolTable(SymNode* &node){
    if(node){
        destroySymbolTable(node->left);
        destroySymbolTable(node->right);
        delete node;
        node=NULL;
    }
}

int get_heightSym(SymNode* node){
    if(node==NULL){
        return 0;
    }

    return node->height;
}


int BF(SymNode* node){
    if(node==NULL){
        return 0;
    }
    return get_heightSym(node->left) - get_heightSym(node->right);
}

void HeightUpdation(SymNode* node){
    if(node==NULL){
        return;
    }
    node->height= 1 + std::max(get_heightSym(node->left),get_heightSym(node->right));
}



SymNode* owninsert(SymNode* node, string k){

    if (node==NULL){
        SymNode* temp=new SymNode(k);
        return temp;
    }
    if(k < node->key){
        SymNode* temp=owninsert(node->left,k);
        if(node!=NULL){
            node->left=temp;
        }
        if(temp!=NULL){
            temp->par=node;    
        }
        

    }
    else if(k> node->key){
        SymNode* temp=owninsert(node->right,k);
        if(node!=NULL){
            node->right=temp;
        }
        if(temp!=NULL){
            temp->par=node;    
        }
        
    }
    else{
        //might have to update here
        // node->key=k;
        return node;
    }
    //we update the fucking height mate
    HeightUpdation(node);

    int bf=BF(node);

    //first case= left-left case
    if(bf > 1 &&  k < node->left->key){
        node = node->SymNode::LeftLeftRotation();
    }
    //second case right right case
    else if(bf < -1 &&  k > node->right->key){
        node = node->SymNode::RightRightRotation();
    }

    //third case = left-right case
    else if(bf > 1 && k > node->left->key){
        node = node->SymNode::LeftRightRotation();
    }

    //last case = right left case
    else if(bf < -1 && k < node->right->key){
        node = node->SymNode::RightLeftRotation();
    }

    //if no rotation required
    return node;

}

SymNode* succ(SymNode* node){
    while(node->left!=NULL){
        node=node->left;
    }
    return node;
}


SymNode* ownremove(SymNode* root, string k){
    if(root==NULL){
        return root;
    }

    if(k<root->key){
        SymNode* temp=ownremove(root->left,k);
        if(root!=NULL){
            root->left=temp;
        }
        if(temp!=NULL){
            temp->par=root;    
        }
        // return root;
        

        int bf=BF(root);

        //first case= left-left case
        if(bf<-1 && (root->right->right==NULL)){
            root=root->SymNode::RightLeftRotation();
        }
        else if(bf<-1 && (root->right->left==NULL)){
            root=root->SymNode::RightRightRotation();
        }

        else if(bf<-1){
            if(root->right->right->height > root->right->left->height){
                root=root->SymNode::RightRightRotation();
            }
            else if(root->right->right->height < root->right->left->height){
                root=root->SymNode::RightLeftRotation();
            }

            else{
                root=root->SymNode::RightRightRotation();
            }
        }
        HeightUpdation(root);
        return root;
        
    }
    
    else if(k> root->key){
        SymNode* temp=ownremove(root->right,k);
        if(root!=NULL){
            root->right=temp;
        }
        if(temp!=NULL){
            temp->par=root;    
        }
        // return root;
        

        int bf=BF(root);

        if(bf>1 && (root->left->left==NULL)){
            root=root->SymNode::LeftRightRotation();
        }
        else if(bf>1 && (root->left->right==NULL)){
            root=root->SymNode::LeftLeftRotation();
        }
        else if(bf>1){
            if(root->left->left->height > root->left->right->height){
                root=root->SymNode::LeftLeftRotation();
            }
            else if(root->left->left->height < root->left->right->height){
                root=root->SymNode::LeftRightRotation();
            }
            else{
                root=root->SymNode::LeftLeftRotation();
            }
            
        }
        HeightUpdation(root);
        return root;
    }
    
    else{
        //we found the node to delete
        if(root->left==NULL){
            SymNode* temp=root->right;
            delete root;
            root=NULL;
            return temp;
        }
        else if(root->right==NULL){
            SymNode* temp=root->left;
            delete root;
            root=NULL;
            return temp;
        }
        else if(root->left!=NULL && root->right!=NULL){
            SymNode* temp=succ(root->right);

            root->key=temp->key;
            root->address=temp->address;
            root->height=root->height;
            
            root->right=ownremove(root->right,temp->key);
        }

        //now we need to update height
        

        int bf=BF(root);

        //first case= left-left case
        if(bf>1 &&  k < root->left->key){
            root=root->SymNode::LeftLeftRotation();
        }
        //second case right right case
        if(bf<-1 &&  k > root->right->key){
            root=root->SymNode::RightRightRotation();
        }

        //third case = left-right case
        if(bf > 1 && k > root->left->key){
            root=root->SymNode::LeftRightRotation();
        }

        //last case = right left case
        if(bf < -1 && k < root->right->key){
            root=root->SymNode::RightLeftRotation();
        }

        HeightUpdation(root);
        return root;
    }
    return root;

}

SymNode* ownsearch(SymNode* node, string &k){
    //base case if not found
    if(node==NULL){
        return NULL;
    }

    if(node->key==k){
        return node;
    }

    else if(k<node->key){
        SymNode* ans=ownsearch(node->left,k);
        return ans;
    }

    SymNode* ans=ownsearch(node->right,k);
    return ans;

}
int SymbolTable::search(string k){
    SymNode* ans=ownsearch(root,k);
    if(ans==NULL){//not found
        return -2;
    }
    return ans->address;
    

}


void SymbolTable::insert(string k){
    //normal insertion like in BST first
    if(ownsearch(root,k)==NULL){//does not exist
        root=owninsert(root,k);
        size++;
    }
    
    //inserted punk
}

void SymbolTable::remove(string k){
    if(ownsearch(root,k)!=NULL){//does exist
        root=ownremove(root,k);
        size--;
    }

}



void SymbolTable::assign_address(string k,int idx){
    SymNode* Temp=ownsearch(root,k);
    Temp->address=idx;
    return;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    size=0;
    destroySymbolTable(root);

}

