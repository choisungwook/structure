#include <stdio.h>
#include <stdlib.h>

#define max(a,b)    (((a) > (b)) ? (a) : (b))

typedef struct AvlNode
{
	int data; // key 값
	AvlNode *left_child, *right_child;
}AvlNode;

AvlNode *root;


// LL 회전 (오른쪽으로 회전한다)
//     A
//    /                B
//   B        ->      / \
//  /                C   A
// C
//
// ±2를 가지는 A가 부모가 되고 A->left_child인 B가 child가 된다.
// A->left에 B가 가지고 있는 right_child를 대입하고 B의 right_child에 A을 대입한다.

AvlNode* rotate_LL(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

// RR 회전 (왼쪽으로 회전한다)
//     A
//      \               B
//       B     ->      / \
//        \           A   C
//         C
//
// ±2를 가지는 A가 부모가 되고 A->right_child인 B가 child가 된다.
// A->right에 B가 가지고 있는 left_child를 대입하고 B의 left_child에 A을 대입한다.

AvlNode* rotate_RR(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

// RL 회전 (오른쪽-왼쪽으로 회전한다)
//     A                A              
//      \                \                C
//       B      ->        C      ->      / \
//      /                  \            A   B
//     C                    B
//
// ±2를 가지는 A가 부모가 되고 A->right_child인 B가 child가 된다.
// A->right_child에 rotate_LL(B)가 반환하는 값을 대입한다. (B,C에 대해 오른쪽 회전)
// rotate_LL(B)호출시 B와 C가 변화가 생기고 다시 rotate_RR(A)을 호출하면 균형트리가 된다. 

AvlNode* rotate_RL(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

// LR 회전 (왼쪽-오른쪽으로 회전한다)
//     A                 A              
//	  /                 /                  C
//   B         ->      C          ->      / \
//    \               /                  A   B
//     C             B      
//
// ±2를 가지는 A가 부모가 되고 A->left_child인 B가 child가 된다.
// A->left_child에 rotate_RR(B)가 반환하는 값을 대입한다. (B,C에 대해 왼쪽 회전)
// rotate_RR(B)호출시 B와 C가 변화가 생기고 다시 rotate_LL(A)을 호출하면 균형트리가 된다. 

AvlNode* rotate_LR(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

// 트리의 높이 측정 함수
// 순환호출로 각각의 높이를 구하고 이들 중에서 더 큰값에 1을 더하면 트리의 높이가 된다.
int get_height(AvlNode *node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// 노드의 균형인수 반환 함수
// 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
int get_balance(AvlNode *node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// 균형 트리를 만드는 함수
AvlNode* balance_tree(AvlNode **node)
{
	int height_diff = get_balance(*node);

	if (height_diff > 1) // 왼쪽 서브트리의 균형을 맞춘다
	{
		if (get_balance((*node)->left_child) > 0)
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if (height_diff < -1) // 오른쪽 서브트리의 균형을 맞춘다
	{
		if (get_balance((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

// AVL 트리의 삽입 연산
// key에 대해 순환호출을 반복하므로써 트리에 삽입 한 후 균형화 함수를 호출한다.
AvlNode* avl_add(AvlNode **root, int key)
{
	if (*root == NULL)
	{
		*root = (AvlNode*)malloc(sizeof(AvlNode));
		if (*root == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(-1);
		}

		(*root)->data = key;
		(*root)->left_child = (*root)->right_child = NULL;
	}
	else if (key < (*root)->data)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), key);
		(*root) = balance_tree(root);
	}
	else if (key >(*root)->data)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), key);
		(*root) = balance_tree(root);
	}
	else
	{
		printf("중복 키로 인한 삽입 실패\n");
		exit(-1);
	}
	return *root;
}

// AVL 트리 탐색 함수
// 일반 적인 이진 트리의 탐색 함수와 같다. AVL도 이진 탐색 트리의 일종이다.
AvlNode* avl_search(AvlNode *node, int key)
{
	if (node == NULL) return NULL;

	printf("%d->", node->data);

	if (key == node->data)
		return node;
	else if (key < node->data)
		avl_search(node->left_child, key);
	else
		avl_search(node->right_child, key);
}

int main()
{
	avl_add(&root, 1);
	avl_add(&root, 2);
	avl_add(&root, 3);
	avl_add(&root, 4);
	avl_add(&root, 5);
	avl_add(&root, 6);
	avl_add(&root, 7);
	avl_add(&root, 8);
	avl_add(&root, 9);
	avl_add(&root, 10);
	avl_add(&root, 11);
	avl_add(&root, 12);

	avl_search(root, 2);

	return 0;
}
