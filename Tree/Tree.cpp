#include <iostream>
using namespace std;

typedef int Data;

class NODE{
public:
	Data data;
	NODE* Left;
	NODE* Right;

	NODE();
	NODE(Data data);
};

NODE::NODE()
{
	this->Left = NULL;
	this->Right = NULL;
}

NODE::NODE(Data data)
{
	this->data = data;
	this->Left = NULL;
	this->Right = NULL;
}

class Tree{
private:
	NODE* root;
public:
	Tree();
	void insert(NODE *new_node);
	NODE* GetLeftchild(NODE* parent);
	NODE* GetRightchild(NODE* parent);
	void MakesubLeft(NODE *parent,NODE *child);
	void MakesubRight(NODE *parent,NODE *child);
};

Tree::Tree()
{
	root = NULL;
}

NODE* Tree::GetLeftchild(NODE* parent)
{
	return parent->Left;
}

NODE* Tree::GetRightchild(NODE* parent)
{
	return parent->Right;
}


void Tree::MakesubLeft(NODE *parent,NODE *child)
{
	parent->Left = child;
}

void Tree::MakesubRight(NODE *parent,NODE *child)
{
	parent->Right = child;	
}

void Tree::insert(NODE *new_node)
{
	NODE* cur = root;
	NODE* parent = NULL;

	while( cur != NULL){
		parent = cur;
		
		if(new_node->data > cur->data)
			cur = GetRightchild(cur);
		else
			cur = GetLeftchild(cur);
	}

	if(parent){
		if(parent->data > new_node->data)
			MakesubLeft(parent,new_node);
		else
			MakesubRight(parent,new_node);
	}
	else
		root = new_node;
}

NODE* create_node(Data data)
{
	NODE* new_node = new NODE(data);
	return new_node;
}

int main()
{
	Tree t1;

	t1.insert(create_node(12));
	t1.insert(create_node(1));
	t1.insert(create_node(17));
	return 0;
}

