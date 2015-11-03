#include <iostream>
#include <string>

class Avl{
private:
	Node *root = NULL;
	Node* SetNode(int value = 0, int BF = 0, Node *parent = NULL, Node *left = NULL, Node *right = NULL){
		Node* tmp;
		tmp = new Node;
		tmp->Value = value;
		tmp->BF = BF;
		tmp->Parent = parent;
		tmp->Left = left;
		tmp->Right = right;
		return tmp;
	}
	Node* pred(Node * member){
		Node * r;
		if (member != NULL){
			if (member->Left != NULL){
				member = member->Left;
				while (member->Right) member = member->Right;
			}
			else{
				do{
					r = member;
					member = member->Parent;
				} while (member && member->Right != r);
			}
		}
		return member;
	}
	Node* Find(int pValue, bool &found){
		Node* member = root,*parent = NULL;
		while (member != NULL){
			if (member->Value == pValue){
				found = true;
				return member;
			}
			parent = member;
			if (member->Value > pValue)member = member->Left;
			else member = member->Right;
		}
		found = false;
		return parent;
	}
	Node* RotateRightRight(Node* member){
		Node *parent = member->Parent, *Bnode = member->Right;
		member->Right = Bnode->Left;								
		if (member->Right != NULL)member->Right->Parent = member;	
		Bnode->Left = member;										
		Bnode->Parent = parent;										
		member->Parent = Bnode;										
		if (parent != NULL){										
			if (parent->Left == member)parent->Left = Bnode;		
			else parent->Right = Bnode;
		}
		else root = Bnode;											
		if (Bnode->BF == 1){										
			member->BF = 0;
			Bnode->BF = 0;
		}
		else{
			member->BF = 1;
			Bnode->BF = -1;
		}
		return Bnode;
	}
	Node* RotateLeftLeft(Node* member){
		Node *parent = member->Parent, *Bnode = member->Left;
		member->Left = Bnode->Right;								
		if (member->Left != NULL)member->Left->Parent = member;		
		Bnode->Right = member;										
		Bnode->Parent = parent;										
		member->Parent = Bnode;										
		if (parent != NULL){										
			if (parent->Left == member)parent->Left = Bnode;		
			else parent->Right = Bnode;
		}
		else root = Bnode;											
		if (Bnode->BF == -1){										
			member->BF = 0;
			Bnode->BF = 0;
		}
		else{
			member->BF = -1;
			Bnode->BF = 1;
		}
		return Bnode;
	}
	Node* RotateRightLeft(Node* member){
		Node *parent = member->Parent, *Bnode = member->Right, *Cnode = member->Right->Left;
		Bnode->Left = Cnode->Right;									
		if (Bnode->Left != NULL)Bnode->Left->Parent = Bnode;		
		member->Right = Cnode->Left;								
		if (member->Right != NULL)member->Right->Parent = member;	
		Cnode->Left = member;										
		Cnode->Right = Bnode;										
		Bnode->Parent = Cnode;										
		member->Parent = Cnode;										
		Cnode->Parent = parent;										
		if (parent != NULL){										
			if (parent->Left == member)parent->Left = Cnode;		
			else parent->Right = Cnode;
		}
		else root = Cnode;											
		if (Cnode->BF == 1) member->BF = -1;
		else member->BF = 0;
		if (Cnode->BF == -1) Bnode->BF = 1;
		else Bnode->BF = 0;
		Cnode->BF = 0;
		return Bnode;
	}
	Node* RotateLeftRight(Node* member){
		Node *parent = member->Parent, *Bnode = member->Left, *Cnode = member->Left->Right;
		Bnode->Right = Cnode->Left;									
		if (Bnode->Right != NULL)Bnode->Right->Parent = Bnode;
		member->Left = Cnode->Right;
		if (member->Left != NULL)member->Left->Parent = member;
		Cnode->Right = member;
		Cnode->Left = Bnode;
		Bnode->Parent = Cnode;
		member->Parent = Cnode;
		Cnode->Parent = parent;
		if (parent != NULL){
			if (parent->Left == member)parent->Left = Cnode;
			else parent->Right = Cnode;
		}
		else root = Cnode;
		if (Cnode->BF == -1)member->BF = 1;
		else member->BF = 0;
		if (Cnode->BF == 1)Bnode->BF = -1;
		else Bnode->BF = 0;
		Cnode->BF = 0;
		return Bnode;
	}
	Node* Remove(Node* member){
		Node *y; 
		bool nest;
		if (member->Left != NULL && member->Right != NULL){
			y = Remove(pred(member));
			nest = false;
		}
		else {
			if (member->Left != NULL) {
				y = member->Left;
				member->Left = NULL;
			}
			else {
				y = member->Right;
				member->Right = NULL;
			}
			member->BF = 0; // poniewa¿ jeœli member mia³ syna to jest on juz w y
			nest = true;
		}
		if (y != NULL){
			y->Parent = member->Parent;
			y->Left = member->Left;
			if (y->Left != NULL)y->Left->Parent = y;
			y->Right = member->Right;
			if (y->Right != NULL)y->Right->Parent = y;
			y->BF = member->BF;
		}
		if (member->Parent != NULL){
			if (member->Parent->Left == member)member->Parent->Left = y;
			else member->Parent->Right = y;
		}
		else root = y;
		if (nest){
			CheckCases(y, member->Parent);
		}
		return member;
	}
	Node* CheckCases(Node *member, Node *parent){
		Node *z = member,*t; 
		member = parent;
		while (member != NULL){
			if (member->BF == 0){
				if (member->Left == z)member->BF = 1;
				else member->BF = -1;
				break;
			}
			else{
				if ((member->BF != -1 || member->Left != z) && (member->BF != 1 || member->Right != z)){
					if (member->Left == z)t = member->Right;
					else t = member->Left;
					if (t->BF == 0){
						if (member->BF == -1)member = RotateLeftLeft(member);
						else member = RotateRightRight(member);
						break;
					}
					else{
						if (member->BF == t->BF){
							if (member->BF == -1)member = RotateLeftLeft(member);
							else member = RotateRightRight(member);
							z = t;
							member = t->Parent;
							continue;
						}
						else{
							if (member->BF == -1)member = RotateLeftRight(member);
							else member = RotateRightLeft(member);
							z = member->Parent;
							member = z->Parent;
						}
					}
				}
				else{
					member->BF = 0;
					z = member;
					member = member->Parent;
					continue;
				}
			}
		}
		return member;
	}
	void Equivalent(Node *member){
		while (member->Parent != NULL){
			if (member == member->Parent->Left)member->Parent->BF--;
			else member->Parent->BF++;
			if (member->Parent->BF == 0)return;
			if (member->Parent->BF == 2){
				if (member->BF == 1 || member->BF == 0)member = RotateRightRight(member->Parent);
				else member = RotateRightLeft(member->Parent);
				if (member == root)member->Parent = NULL;
				return;
			}
			else if (member->Parent->BF == -2){
				if (member->BF == -1 || member->BF == 0)member = RotateLeftLeft(member->Parent);
				else member = RotateLeftRight(member->Parent);
				if (member == root)member->Parent = NULL;
				return;
			}
			member = member->Parent;
		}
	}
public:
	Avl (){
		root = NULL;
	}
	Node* GetRoot(){
		return root;
	}
	bool Find(int pValue){
		bool found = false;
		Find(pValue,found)
		if (!found)return false;
		else return true;
	}
	void Insert(int pValue){
		if (root == NULL){
			root = SetNode(pValue);
			return;
		}
		bool found = false;
		Node *tmp = Find(pValue, found);
		if (found)return;
		if (pValue < tmp->Value){
			tmp->Left = SetNode(pValue,0,tmp);
			Equivalent(tmp->Left);
		}
		else {
			tmp->Right = SetNode(pValue, 0, tmp);
			Equivalent(tmp->Right);
		}
	}
	void Remove(int pValue){
		bool found;
		Node *tmp = Find(pValue, found);
		if (!found)return;
		Remove(tmp);
	}
	void Print(Node* pRoot){
		if (pRoot == NULL)return;
		if (pRoot->Left != NULL)Print(pRoot->Left);
		cout << pRoot->Value << " ";
		if (pRoot->Right != NULL)Print(pRoot->Right);
	}
};

int main(char* argv, int argc){

	string pol;
	int n,pVal;
	Avl avl;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> pol;
		if (pol.compare("PRINT") == 0) avl.Print(avl.GetRoot());
		else {
			cin >> pVal;
			if (pol.compare("INSERT") == 0)avl.Insert(pVal);
			if (pol.compare("REMOVE") == 0)avl.Remove(pVal);
			if (pol.compare("FIND") == 0){
				if (avl.Find(pVal))cout << "YES" << endl;
				else cout << "NO" << endl;
			}
		}
	}

	system("pause");
	return 0;
}