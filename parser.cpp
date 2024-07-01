/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable=new SymbolTable;
    last_deleted=-4;
}
bool numberchecker(string input){
    bool check=true;
    for(char c:input){
        if(c=='-'){
            continue;
        }
        else if(std::isdigit(c)==false){
            check=false;
            break;
        }
    }
    return check;
}

int numberconverter(string a){
    int k=0;
    if(a[0]=='-'){
        k=1;
    }
    int j=1;
    int num=0;
    for(int i=a.size()-1;i>=k;i--){
        int digit = a[i]-'0';
        num += j*digit;
        j*=10;
    }
    if(k==1){
        return num*(-1);
    }
    
    return num;

}
void Parser::parse(vector<string> expression){
    vector <ExprTreeNode*> stack;
    ExprTreeNode* first= new ExprTreeNode(expression[0],0);
    ExprTreeNode* second=new ExprTreeNode(expression[1],0);

    for(int i=2;i<expression.size();i++){
        if(expression[i]==")"){
            ExprTreeNode* rightnode= stack.back();
            stack.pop_back();
            ExprTreeNode* middlenode=stack.back();
            stack.pop_back();
            ExprTreeNode* leftnode=stack.back();
            stack.pop_back();

            //no evaluation here

            middlenode->right=rightnode;
            middlenode->left=leftnode;
            stack.push_back(middlenode);
        }
        else if(expression[i]!=")" && expression[i]!="("){
            if(numberchecker(expression[i])==true){
                int num= numberconverter(expression[i]);
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],num);
                stack.push_back(toinsert);
            }
            else if(expression[i]=="+"){
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],0);
                stack.push_back(toinsert);
            }
            else if(expression[i]=="-"){
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],0);
                stack.push_back(toinsert);
            }
            else if(expression[i]=="*"){
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],0);
                stack.push_back(toinsert);
            }
            else if(expression[i]=="/"){
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],0);
                stack.push_back(toinsert);
            }
            else{//bc hum variable hai
                // int variable_value=symtable->search(expression[i]);//sorry its wrong
                ExprTreeNode* toinsert= new ExprTreeNode(expression[i],0);
                stack.push_back(toinsert);
            }

        }
    }

    ExprTreeNode* finalright=stack.back();
    stack.pop_back();
    second->right=finalright;
    second->left=first;
    expr_trees.push_back(second);
    if(first->type=="VAR"){
        symtable->insert(first->id);//inserted the variable
    }
    else if(first->type=="DEL"){
        
        last_deleted=symtable->search(finalright -> id);
        symtable->remove(finalright->id);//removed the variable
        
    }
    return;
   
}

void destroyexprtreenodes(ExprTreeNode* &node){
    if(node){
        destroyexprtreenodes(node->left);
        destroyexprtreenodes(node->right);
        delete node;
        node=NULL;
    }
}

Parser::~Parser(){
    delete symtable;
    for(int i=0;i<expr_trees.size();i++){
        destroyexprtreenodes(expr_trees[i]);
    }
}