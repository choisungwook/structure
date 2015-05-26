#include <iostream>
using namespace std;


template <typename T>
class NODE{
public :
	NODE* Lnext;
	NODE* Rnext;
	T data;
	NODE(T _data)
	{
		data = _data;
		Lnext = NULL;
		Rnext = NULL;
	}
	NODE()
	{
		Lnext = NULL;
		Rnext = NULL;
		data = 0;
	}
	NODE<T>* GetLeftNode()
	{
		return this->Lnext;
	}
	NODE<T>* GetRightNode()
	{
		return this->Rnext;
	}
	void makeLeftNode(NODE<T>* newNode)
	{
		this->Lnext = newNode;
	}
	void makeRightNode(NODE<T>* newNode)
	{
		this->Rnext = newNode;
	}
	void deleteNode(NODE<T>* delNode)
	{
		delete delNode;
	}
	void removeLeftNode()
	{
		this->Lnext = NULL;
	}
	void removeRightNode()
	{
		this->Rnext = NULL;
	}
};

template <typename T>
class BinaryTree : public NODE<T>
{
public:
	BinaryTree()
	{
		this->root = NULL;
	}
	NODE* root;
	void insert(T data);
	void preorder(NODE<T>* Root);
	void inorder(NODE<T>* Root);
	NODE<T>* remove(T delData);	
};

template <typename T>
void BinaryTree<T>::preorder(NODE<T>* Root)
{
	if (Root)
	{
		cout << Root->data << " ";
		preorder(Root->GetLeftNode());
		preorder(Root->GetRightNode());
	}
}

template <typename T>
void BinaryTree<T>::inorder(NODE<T>* Root)
{
	if (Root)
	{		
		inorder(Root->GetLeftNode());
		cout << Root->data << " ";
		inorder(Root->GetRightNode());
	}
}

template <typename T>
void BinaryTree<T>::insert(T data)
{
	NODE<T>* curNode = root;
	NODE<T>* parentNode = NULL;
	NODE<T>* newNode = NULL;

	while (curNode != NULL)
	{
		if (data == curNode->data)
			return;

		parentNode = curNode;
		if (curNode->data > data)
			curNode = curNode->GetLeftNode();
		else
			curNode = curNode->GetRightNode();
	}

	newNode = new NODE<T>(data);

	if (parentNode != NULL)
	{
		if (parentNode->data > data)
			parentNode->makeLeftNode(newNode);
		else
			parentNode->makeRightNode(newNode);
	}
	else
		this->root = newNode;
}

template <typename T>
NODE<T>* BinaryTree<T>::remove(T delData)
{
	NODE<T>* virtualRoot = new NODE<T>(0);
	NODE<T>* curNode = root;
	NODE<T>* parentNode = virtualRoot;
	NODE<T>* delNode = NULL;
	
	virtualRoot->makeRightNode(root);

	while ((curNode != NULL) && (curNode->data != delData))
	{
		parentNode = curNode;

		if (curNode->data > delData)
			curNode = curNode->GetLeftNode();
		else
			curNode = curNode->GetRightNode();
	}

	if (curNode == NULL)
		return NULL;
	
	delNode = curNode;

	if ((delNode->GetLeftNode() == NULL) && (delNode->GetRightNode() == NULL))
	{
		if (parentNode->GetLeftNode() == delNode)
			parentNode->removeLeftNode();
		else
			parentNode->removeRightNode();
	}
	else if (delNode->GetLeftNode() == NULL || delNode->GetRightNode() == NULL)
	{
		NODE<T>* delChildNode;

		if (delNode->GetLeftNode() != NULL)
			delChildNode = delNode->GetLeftNode();
		else
			delChildNode = delNode->GetRightNode();

		if (parentNode->GetLeftNode() == delNode)
			parentNode->makeLeftNode(delChildNode);
		else
			parentNode->makeRightNode(delChildNode);
	}
	else
	{
		NODE<T>* delparentNode = delNode;
		NODE<T>* delChildNode = delNode->GetRightNode();
		T delData;

		while (delChildNode->GetLeftNode() != NULL)
		{
			delparentNode = delChildNode;
			delChildNode = delChildNode->GetLeftNode();
		}

		delData = delNode->data;
		delNode->data = delChildNode->data;

		if (delparentNode->GetLeftNode() == delChildNode)
			delparentNode->makeLeftNode(delChildNode->GetRightNode());
		else
			delparentNode->makeRightNode(delChildNode->GetRightNode());

		delNode = delChildNode;
		delChildNode->data = delData;
	}

	if (virtualRoot->GetRightNode() != root)
		root = virtualRoot->GetRightNode();

	delete virtualRoot;

	return delNode;
}

int main()
{
	BinaryTree<int> bt1;

	bt1.insert(3);

	bt1.insert(1);
	bt1.insert(2);
	bt1.insert(4);
	bt1.insert(5);
		
	bt1.inorder(bt1.root);
	cout << endl;

	bt1.remove(5);
	bt1.inorder(bt1.root);
	cout << endl;
	return 0;
}
