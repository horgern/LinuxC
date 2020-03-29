#include <stdio.h>
#include <stdlib.h>



typedef struct node Node_t;


typedef struct node* pNode_t;


struct node{
	pNode_t next;
	int index;
} ;

int main()
{
	int i = 0;
	pNode_t header = calloc(1, sizeof(Node_t));
	if (header == NULL) {
		return -1;
	}
	header->next = header;
	pNode_t p = header;
	for (i = 0; i < 10; i++) {
		pNode_t node = calloc(1, sizeof(Node_t));
		if (node == NULL) {
			return -1;
			printf("node is null\n");
		}
		node->next = NULL;
		


		p->next = node;
		p->index = i;
		p = node;
		
	}
	if (p->next == NULL) {
		printf("=======\n");
	}
	for (p = header; p->next != NULL; p = p->next) {
		printf("p->index[%d]\n", p->index);
	}

	
	pNode_t h_tmp = header;
	pNode_t p_tmp = NULL;

	printf("\n==========================\n");

	
	for (p = header; p->next != NULL; ) {

		//printf("p->index %d\n", p->index);


		p_tmp = p->next;
		
		p->next = h_tmp;
		h_tmp = p;

		printf("h_tmp->index %d\n", h_tmp->index);
		printf("h_tmp->next->index %d\n", h_tmp->next->index);
		p = p_tmp;


	}
	
	header->next = NULL;
	/*p = header;
	p = p->next;

	p_tmp = p->next;
	p->next = header;
	header->next = NULL;*/
	/*p_tmp2 = p_tmp->next;
	p_tmp->next = p;


	p = p_tmp2->next;
	p_tmp2->next = p_tmp;


	p_tmp = p->next;
	p->next = p_tmp2;*/

	/*for (i = 0; i < 3; i++) {
	 	p_tmp2 = p_tmp->next;
	 	p_tmp->next = p;

		p = p_tmp2->next;
		p_tmp2->next = p_tmp;


		p_tmp = p->next;
		p->next = p_tmp2;
	}*/
	printf("\n\n==============\n\n");
	for (p = h_tmp; p != NULL; p = p->next) {
		printf("p->index[%d]\n", p->index);
	}
	//printf("p->index[%d]\n", header->index);
}



