#include <iostream>
#include <list>

using namespace std;
class charnode{

public:
    char data;
    charnode* next;
    charnode(){}
    charnode(string name){
        charnode * temp  = this;
        for (char c :name) {
            temp->data=c;
            temp->next= new charnode();
            temp=temp->next;
        }
    }

    bool isequal(charnode *s) {
            int len1=0;
            int len2=0;
            if(this->data!=s->data) {
                return false;
            }
            charnode *it1 = this->next;
            charnode *it2 = s->next;

        charnode * temp  = it1;
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
};
int lenght(charnode *s) {
    charnode * temp  = s;
    int i = 0;
    while (temp){
        i++;
        temp=temp->next;
    }
    return i-1;
}


class Gene{
public:
    string name;
    //Gene *Connected[20000];
    list<Gene> Connected;
    void Connect(Gene * second){
        Connected.push_back(*second);
        Gene *ss = &Connected.front();
        cout<<ss->name;
    }
};


int main() {
    //dtring * dtring1 = new dtring();
    charnode* s2 = new charnode("Danial");
    charnode* s1=new charnode("Danial");
    Gene *D = new Gene();
    D->name="Dan";
    Gene *S = new Gene();
    S->name="kiram too konet age kar nakoni";
    D->Connect(S);


    return 0;

}