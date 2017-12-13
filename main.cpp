#include "iostream"
#include "list"
using namespace std;

struct Charnode{
    Charnode(){}
    Charnode(char s){
        data=s;
    }
    Charnode*next= nullptr;
    char data;
};
class Charlist{

public:
    Charnode* root;
    Charlist(){}
    Charlist(string name){
        root = new Charnode();
        Charnode* temp = root;
        for (char c :name) {
            temp->next= new Charnode(c);
            temp=temp->next;
        }
    }
    static int lenght(Charlist *s) {
        Charnode * temp  = s->root;
        int i = 0;
        while (temp){
            i++;
            temp=temp->next;
        }
        return i-1;
    }
    bool isequal (Charlist *s) {
        int len1=0;
        int len2=0;
        Charnode *it1 = this->root;
        Charnode *it2 = s->root;

        Charnode * temp  = it1;
        int i = 0;
        while (temp){
            i++;
            temp=temp->next;
        }
        len1=i;
        temp  = it2;
        i = 0;
        while (temp){
            i++;
            temp=temp->next;
        }
        len2=i;
        if(len1 !=len2){
            return false ;
        }
        for (int i = 0; i < len1; i++) {
            if (it1->data!=it2->data) {
                //cout<<i<<'\n';
                return false;
            } else {
                it1 = it1->next;
                it2 = it2->next;
            }

        }
        return true;
    }
    bool isbigger(Charlist *s){
        Charnode*it1=this->root;
        Charnode*it2 = s->root;
        while (it1!= nullptr && it2!= nullptr){
            if(it1->data==it2->data){
                it1=it1->next;
                it2=it2->next;
            } else{
                if (it1->data>it2->data){
                    return true;
                } else{
                    return false;
                }
            }
        }
        if(lenght(this)>lenght(s)){
            return true;
        } else{
            return false;
        }
    }
};
struct Namenode{
    Namenode(){}
    Namenode(string ss){
        name=new Charlist(ss);
    }
    Charlist* name;
    Namenode*next;
};
class NameList{
public:
    Namenode* root;
    NameList(){}
    NameList(string name1) {
        root = new Namenode(name1);
    }
    void insert(Charlist* name1){
     Namenode* temp=root ;
        if(!root){
            root=new Namenode();
            root->name=name1;
            return;
        }
        while (temp->next!= nullptr){
            temp=temp->next;
        }
        temp->next=new Namenode();
        temp->next->name=name1;
        return;
    }
    bool contain(Charlist* data){
        Charlist *temp = data;
        Namenode *it = root;
        while (it){
            if(it->name->isequal(temp)){
                return true;
            }
            it=it->next;
        }
        return false;
    }
    int size(){
        int i =0;
        Namenode* temp=root;
        while (temp){
            i++;
            temp=temp->next;
        }
        return i;
    }
    void remove(Charlist* name1){
        Namenode* namenode = new Namenode();
        namenode->name=name1;
        Namenode* temp=root;
        if(temp->name==namenode->name){
            temp=temp->next;
            return;
        }
        while (temp){
            if(temp->name=namenode->name){
                delete temp->next;
                temp->next=temp->next->next;
            }
            temp=temp->next;
        }

    }
};
struct Gene{
    int x1,x2;
    list<Gene*>Connected;
    NameList Names;
};
struct dictNode{
    Charlist* name;
    Gene * gene;
    dictNode *leftChild;
    dictNode * rightChild ;
};
class dict {
public:
    list<Gene*> Genes;
    dictNode* Rotate_to_l(dictNode *dictNode1) {
        dictNode* temp = dictNode1->rightChild;
        dictNode1->rightChild = temp->leftChild;
        temp->leftChild = dictNode1;
        return temp;
    }
    dictNode* Rotata_to_r(dictNode *dictNode1){
        dictNode* temp = dictNode1->leftChild;
        dictNode1->leftChild = temp->rightChild;
        temp->rightChild = dictNode1;
        return temp;
    }
    dictNode* Splay(Charlist *key, dictNode* root) {
        if (!root)
            return NULL;
        dictNode header;
        header.leftChild = header.rightChild = NULL;
        dictNode* LeftTreeMax = &header;
        dictNode* RightTreeMin = &header;
        //key.print();
        //  root->name.print();
        while (1) {
            if (!root->leftChild)
                break;
            if (!(root->name->isbigger(key))&&!root->name->isequal(key)) {
                //        key.print();
                root->leftChild->name;
                if (root->leftChild->name->isbigger(key)&&!root->name->isequal(key)) {
                    root = Rotata_to_r(root);
                    if (!root->leftChild)
                        break;
                }
                RightTreeMin->leftChild = root;
                RightTreeMin = RightTreeMin->leftChild;
                root = root->leftChild;
                RightTreeMin->leftChild = NULL;
            }
            else if (key->isbigger(root->name)) {
                if (!root->rightChild)
                    break;
                if (key->isbigger(root->rightChild->name)) {
                    root = Rotate_to_l(root);
                    if (!root->rightChild)
                        break;
                }
                LeftTreeMax->rightChild = root;
                LeftTreeMax = LeftTreeMax->rightChild;
                root = root->rightChild;
                LeftTreeMax->rightChild = NULL;
            }
            else
                break;
        }
        LeftTreeMax->rightChild = root->leftChild;
        RightTreeMin->leftChild = root->rightChild;
        root->leftChild = header.rightChild;
        root->rightChild = header.leftChild;
        return root;
    }
    dictNode* New_Node(Charlist *key) {
        dictNode* p_node = new dictNode();
        p_node->name = key;
        p_node->leftChild = p_node->rightChild = NULL;
        return p_node;
    }
    dictNode* Insert(int x1,int x2,Charlist *key, dictNode* root) {
        dictNode* tempnode = new dictNode();
        tempnode->leftChild=tempnode->rightChild= nullptr;
        tempnode->name=key;
        for(Gene *G :Genes){
            if(G->x1==x1 && G->x2==x2){
                tempnode->gene=G;
                tempnode->gene->Names.insert(key);
            }
        }
        if(!tempnode->gene){
            tempnode->gene=new Gene();
            tempnode->gene->x1=x1;
            tempnode->gene->x2=x2;
            tempnode->gene->Names.insert(key);
            Genes.push_back(tempnode->gene);
        }

        if (!root) {
            root = tempnode;
            tempnode = NULL;
            return root;
        }
        root = Splay(key, root);
        /* This is BST that, all keys <= root->key is in root->lchild, all keys >
        root->key is in root->rchild. */
        if(root->name->isequal(key)){
            cout<<"Duplicate Name Inserted";
            return root;
        }
        if (root->name->isbigger(key)) {
            tempnode->leftChild = root->leftChild;
            tempnode->rightChild = root;
            root->leftChild= NULL;
            root = tempnode;
        }
        else if (key ->isbigger(root->name)) {
            tempnode->rightChild = root->rightChild;
            tempnode->leftChild = root;
            root->rightChild = NULL;
            root = tempnode;
        }
        else {
            root->gene->Names.insert(key);
            root->gene->x1 = x1;
            root->gene->x2 = x2;
            return root;
        }
        tempnode = NULL;
        // cout<<"Duplicate Name Inserted";
        return root;

    }
    dictNode* Delete(Charlist *key, dictNode* root) {
        dictNode* temp;
        if (!root) {
            return NULL;
        }
        root = Splay(key, root);

        if (!key->isequal(root->name)) {
            return root;
        }
        else
        {
            if (!root->leftChild) {
                temp = root;
                root = root->rightChild;
                //printall(temp->gene);
            }
            else {
                temp = root;
                if(temp->gene->Names.size()==1){
                    temp->gene->Names.remove(key);
                    delete temp->gene;
                    temp->gene=NULL;
                } else{
                    temp->gene->Names.remove(key);
                }
                /*Note: Since key == root->key,
                so after Splay(key, root->lchild),
                the tree we get will have no right child tree.*/
                root = Splay(key, root->leftChild);
                root->rightChild = temp->rightChild;
                //printall(temp->gene);
            }
            free(temp);
            return root;
        }
    }
    dictNode* Search(Charlist *key,dictNode* root) {
        root =  Splay(key, root);
        //key.print();
        //root->name.print();
        if(root->name->isequal(key)){
            return root;
        }
        return nullptr;
    }
    dictNode * AddGeneAlias(Charlist *name1 ,Charlist *name2,dictNode * root){
            root = Search(name1,root);
            root = Insert(root->gene->x1,root->gene->x2,name2,root);
            return root;

    }
    dictNode * RemoveAliasName(Charlist *name2 ,dictNode *root){
        return Delete(name2,root);


    }

};

int main(){
    dictNode *root = NULL;
    dict *dict1= new dict();
    root = dict1->Insert(5,8,new Charlist("Arman"),root);
    root = dict1->Insert(41,15,new Charlist("Danial"),root);
    root = dict1->AddGeneAlias(new Charlist("Danial"),new Charlist("Kamali"),root);
    root = dict1->RemoveAliasName(new Charlist("Kamali"),root);
    return 0;
}