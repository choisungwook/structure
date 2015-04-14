#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 500000

typedef struct _NODE
{
	int data;
	struct _NODE *next;
}NODE;

NODE* student[MAX];

int main()
{
	int total, couple;
	memset(student, 0, sizeof(student));

	scanf("%d %d", &total, &couple);
	return 0;
}

void create_node(int src,int data)
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;

	if (student[src] == NULL)
		student[src] = new_node;
	else{
		NODE* cur = student[src];
		NODE* before = NULL;

		while (cur != NULL){
			before = cur;
			
		}
	}
}
