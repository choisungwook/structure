#include <iostream>
#include <cstdlib>


typedef int Data;

typedef struct _NODE{
	Data data;
	struct _NODE *next;
}NODE;

//function//
NODE* create_node(Data data);
typedef void show_function(Data data);
void show_data(Data data);

class STACK{
private:
	NODE* head;
public:
	STACK();
	~STACK();
	void push(NODE* new_node);
	bool pop(Data *data);
	void show(show_function action);
	bool isempty();
};

int main()
{
		STACK s1;
		Data del_data = 0;

		s1.push(create_node(3));
		s1.push(create_node(1));
		s1.push(create_node(2));
		s1.push(create_node(4));
		s1.push(create_node(23));
		s1.push(create_node(6));
		s1.push(create_node(11));

		printf("STACK show() 함수 호출\n");
		s1.show(show_data);
		printf("\n\n");

		printf("STACK pop() 함수 호출\n");
		while(s1.pop(&del_data)){
			printf("%d ",del_data);
		}
		printf("\n\n");

		printf("STACK show() 함수 호출\n");
		s1.show(show_data);
		printf("\n");
		return 0;
}

STACK::STACK()
{
	head = create_node(0);	
}

STACK::~STACK()
{
	NODE* cur = head->next;
	NODE* before = NULL;

	while(cur != NULL){
		before = cur;
		cur = cur->next;
		free(before);
	}
}

void STACK::push(NODE* new_node)
{
	new_node->next = head->next;
	head->next = new_node;
}

bool STACK::pop(Data *data)
{
	NODE* del_node = head->next;

	if(isempty())
		return false;

	*data = del_node->data;
	head->next = del_node->next;
	free(del_node);

	return true;
}

void STACK::show(show_function action)
{
	NODE* search = head->next;

	while(search != NULL){
		action(search->data);
		search = search->next;
	}
}

bool STACK::isempty()
{
	return head->next==NULL ? true : false ;
}

//////////////function /////////////////

NODE* create_node(Data data)
{
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = data;
	new_node->next = NULL;

	return new_node;
}

void show_data(Data data)
{
	printf("%d ",data);
}
