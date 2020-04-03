#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	char buf[10];
	int i;
	struct D_LIST_NODE node;
} NodeTest_t;


int main()
{
	NodeTest_t *list_new;
	struct D_LIST_NODE list_head;
	struct D_LIST_NODE *pos = NULL, *n = NULL;
	int i = 0;
	
	D_LIST_HEAD_INIT(&list_head);

	for (i = 0; i < 10; i++) {
		list_new = calloc(1, sizeof(NodeTest_t));
		if (list_new == NULL) {
			printf("calloc fail\n");
			return;
		}
		
		list_new->buf[0] = i + 48; 
		list_new->i = i;
		DoubleListAddTail(&list_new->node, &list_head);
	}
	DoubleListDump(&list_head);
	LIST_FOR_EACH_SAFE(pos, n, &list_head) {
		list_new = LIST_NODE_ENTRY(pos, NodeTest_t, node);
		
		if (list_new->i == 7)
			DoubleListDel(&list_new->node);
		else 
			printf("index[%d] -- node[%c]\n", list_new->i, list_new->buf[0]);
	}
	int num = 0;
	LIST_LENGTH_GET(pos, &list_head, num);
	printf("num : %d\n", num);
	
	return 1;
}

