/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    if(t==":="){
        type="EQUALTO";
        id="";
        left=NULL;
        right=NULL;
    }
    else if(t=="del"){
        type="DEL";
        id="";
        left=NULL;
        right=NULL;
    }
    else if(t=="ret"){
        type="RET";
        id="";
        left=NULL;
        right=NULL;
    }
    else if(t=="+"){
        type="ADD";
        id="";
        left=NULL;
        right=NULL;
    }
    else if(t=="-"){
        type="SUB";
        id="";
        left=NULL;
        right=NULL; 
    }
    else if(t=="*"){
        type="MUL";
        id="";
        left=NULL;
        right=NULL;
    }
    else if(t=="/"){
        type="DIV";
        id="";
        left=NULL;
        right=NULL;
    }
    else{
        bool flag=true;
        for(char c:t){
            if(c=='-'){
                continue;
            }
            else if(std::isdigit(c)==false){
                flag=false;
                break;
            }
        }
        
        if(flag==true){//matlab ek number hai apun
            type="VAL";
            num=v;
            id="";
            left=NULL;
            right=NULL;
        }
        else if(flag==false){//apun ek variable hai bc
            type="VAR";
            id=t;
            left=NULL;
            right=NULL;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    type="";
    id="";
    left=NULL;
    right=NULL;
}

