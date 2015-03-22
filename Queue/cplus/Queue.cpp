#include <stdio.h>
#include <stdlib.h>


typedef int Data;

typedef struct _NODE{
	Data data;
	struct _NODE* next;
}NODE;

NODE* create_node(Data data);

class Queue{
private:
	NODE* rear;
	NODE* front;
public:
	Queue();
	~Queue();
	void Enqueue(NODE* new_node);
	bool Dequeue(Data *data);
	bool isempty();	
	void show();
};

int main()
{
	Data del_data = 0;
	Queue q1;
	q1.Enqueue(create_node(3));
	q1.Enqueue(create_node(4));
	q1.Enqueue(create_node(5));
	q1.Enqueue(create_node(6));
	q1.Enqueue(create_node(7));

	q1.show();

	while(q1.Dequeue(&del_data)){
		printf("%d ",del_data);
	}
	printf("\n");

	q1.show();
	return 0;
}

Queue::Queue()
{
	rear = NULL;
	front = NULL;
}

Queue::~Queue()
{
	if(isempty())
		return;

	NODE* del_node = NULL;
	NODE* cur = front;

	while(cur != NULL){
		del_node = cur;
		cur = cur->next;
		free(del_node);
	}
}

bool Queue::isempty()
{
	return front == NULL ? true : false;
}

void Queue::Enqueue(NODE* new_node)
{
	if(isempty()){
		front = new_node;
		rear = new_node;
	}
	else{
		rear->next = new_node;
		rear = new_node;
	}
}

bool Queue::Dequeue(Data *data)
{
	if(isempty())
		return false;
	else{
		NODE* del_node = front;
		*data = del_node->data;
		front = del_node->next;
		free(del_node);
	}

	return true;
}

void Queue::show()
{
	if(isempty())
		return;
	
	NODE* cur = front;
	while(cur != NULL){
		printf("%d ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}
//function

NODE* create_node(Data data)
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;;

	return new_node;
	
}
