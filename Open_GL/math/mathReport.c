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
int visited[MAX];
int recursive(int index,int cnt);

void create_node(int src,int data);


int main()
{
	int total, couple;
	int num1, num2;
	int i;
	int value = 1;
	int result = 0;
	//memset(student, 0, sizeof(student));
	//memset(visited,0,sizeof(visited));
	
	scanf("%d %d", &total, &couple);

	for(int i=0; i<couple; i++){
		scanf("%d %d",&num1,&num2);
		create_node(num1,num2);
	}

	
	for(i=1; i<total+1; i++){
		if( recursive(i,value) )
			value++;
	}

	for(i=1; i<total+1; i++){
		if(visited[i] == 0)
			result++;
	}

	printf("%d\n",result+value-1);
	return 0;
}

int recursive(int index,int cnt)
{
	
	NODE* cur = student[index];
	
	if(cur == NULL || visited[index] != 0)
		return 0;

	visited[index] = cnt;
	
	while( cur != NULL){
		visited[cur->data] = cnt;
		recursive(cur->data,cnt);
		cur = cur->next;
	}

	return 1;
}

void create_node(int src,int data)
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;
	
	NODE* cur = student[src];
	NODE* before = NULL;

	while(cur != NULL){
		before = cur;
		cur = cur->next;
	}

	if(before == NULL)
		student[src] = new_node;
	else{
		before->next = new_node;
	}
}
