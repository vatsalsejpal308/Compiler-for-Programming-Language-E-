/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    //parser has the exprtree vector and symtable, where default memory address is -1
    // output_file="";
    memory_size=40;

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    for(int i=0; i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
    //now all memory addresses have been pushed;
    output_file=out_file;
}

void EPPCompiler::compile(vector<vector<string>> code){
    vector <string> ans1;
    for(vector <string> i:code){
        targ.parse(i);
        ExprTreeNode* temp= targ.expr_trees.back();
        // targ.expr_trees.pop_back();
        if(temp->left->type=="VAR"){
            int index=targ.symtable->search(temp->left->id);
            if(index==-1){
                index= least_mem_loc.get_min();
                least_mem_loc.pop();
            }
            targ.symtable->assign_address(temp->left->id,index);//address assigned
        }

        else if(temp->left->type=="DEL"){
            least_mem_loc.push_heap(targ.last_deleted);//inserted the deleted address
        }

        vector <string> ans=generate_targ_commands();
        // ans1.insert(ans1.end(),ans.begin(),ans.end());
        for(int i=ans.size()-1;i>=0;i--){
            ans1.push_back(ans[i]);
        }
        // write_to_file(ans1);
    }
    write_to_file(ans1);
    // cout<<"size of expr trees "<<targ.expr_trees.size()<<endl;
}


vector<string> EPPCompiler::generate_targ_commands(){
    vector <string> ans;
    ExprTreeNode* Node = targ.expr_trees.back();
    // targ.expr_trees.pop_back();
    
    
    if(Node->left->type=="DEL"){
        string targ_lang="DEL = mem[";
        targ_lang+=std::to_string(targ.last_deleted);
        string s="]";
        targ_lang+=s;
        ans.push_back(targ_lang);
        return ans;
    }
    else if(Node->left->type=="VAR"){
        int address_index= targ.symtable->search(Node->left->id);
        string targ_lang="mem[";
        targ_lang+=std::to_string(address_index);
        string s="] = POP";
        targ_lang+=s;
        // cout<<Node->left->id<<" address = "<<address_index<<endl; 
        ans.push_back(targ_lang);
    }
    else if(Node->left->type=="RET"){
        string targ_lang="RET = POP";
        ans.push_back(targ_lang);
    }
    ExprTreeNode* RealNode=Node->right;
    //iterative preorder traversal
    vector <ExprTreeNode*> stack;
    stack.push_back(RealNode);
    while(stack.empty()==false){
        ExprTreeNode* TopNode= stack.back();
        stack.pop_back();
        if(TopNode->type=="VAR"){
            //this is the variable already defined
            int address_index= targ.symtable->search(TopNode->id);
            string targ_lang="PUSH mem[";
            targ_lang+=std::to_string(address_index);
            string s="]";
            targ_lang+=s;
            ans.push_back(targ_lang);
        }

        if(TopNode->type=="ADD"){
            string targ_lang="ADD";
            ans.push_back(targ_lang);
        }
        if(TopNode->type=="SUB"){
            string targ_lang="SUB";
            ans.push_back(targ_lang);
        }
        if(TopNode->type=="DIV"){
            string targ_lang="DIV";
            ans.push_back(targ_lang);
        }
        if(TopNode->type=="MUL"){
            string targ_lang="MUL";
            ans.push_back(targ_lang);
        }
        if(TopNode->type=="VAL"){
            string targ_lang="PUSH ";
            targ_lang+=std::to_string(TopNode->num);
            ans.push_back(targ_lang);
        }
        if(TopNode->right){
            stack.push_back(TopNode->right);
        }
        if(TopNode->left){
            stack.push_back(TopNode->left);
        }
    }
    //we need to take care of return and delete
    return ans;
    

    
}

void EPPCompiler::write_to_file(vector<string> commands){
    std::ofstream outputFile(output_file);
    for(string j: commands){
        outputFile<< j <<endl;
    }
    outputFile.close();
}

EPPCompiler::~EPPCompiler(){
    targ.~Parser();
    least_mem_loc.~MinHeap();
}

