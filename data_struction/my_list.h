#ifndef _MY_LIST_H_
#define _MY_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdarg.h>




#define LIST_NODE_OFFSET_OF(type,member)	\
		((unsigned long)(&(((type *)0)->member)))
#define LIST_NODE_CONTAINER_OF(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - LIST_NODE_OFFSET_OF(type,member) );})

/*	获取链表节点所在结构体*/
#define LIST_NODE_ENTRY(ptr, type, member) \
		LIST_NODE_CONTAINER_OF(ptr, type, member)


//遍历链表
#define LIST_FOR_EACH_SAFE(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

	/*	获取链表长度*/
#define LIST_LENGTH_GET(pos, head, num) \
			for (pos = (head)->next; pos != (head); pos = pos->next) {num++;}



//single list
struct S_LIST_NODE {
	struct S_LIST_NODE *next;
};

//double list
struct D_LIST_NODE {
	struct D_LIST_NODE *next;
	struct D_LIST_NODE *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name); }



//#define S_LIST_HEAD_INIT(head) do { head->next = head; } while(0);

/* list head初始化*/
#define D_LIST_HEAD_INIT(ptr) do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)


/*****************************************************************

 
******************************************************************/
static inline void DoubleListAdd(struct D_LIST_NODE *new_node,
				  struct D_LIST_NODE *prev_node,
				  struct D_LIST_NODE *next_node)
{
	next_node->prev = new_node;
	new_node->next = next_node;
	new_node->prev = prev_node;
	prev_node->next = new_node;
}

/*****************************************************************

******************************************************************/

static inline void DoubleListAddTail(struct D_LIST_NODE *list_new,struct D_LIST_NODE *list_head)
{
	DoubleListAdd(list_new, list_head->prev, list_head);
}


/*****************************************************************

 ******************************************************************/

static inline void DoubleListDel(struct D_LIST_NODE *list_node)
{
	list_node->next->prev = list_node->prev;
	list_node->prev->next = list_node->next;
	list_node->next = NULL;
	list_node->prev = NULL;
}


/*****************************************************************
   

******************************************************************/

static inline int DoubleListIsEmpty(struct D_LIST_NODE *list_head)
{
	return (list_head->next == list_head);
}


/*****************************************************************
  

******************************************************************/
static inline void DoubleListDump(struct D_LIST_NODE *list_head)
{
	struct D_LIST_NODE *pos, *n;
	int i = 0;
	
	LIST_FOR_EACH_SAFE(pos, n, list_head)
	{
		printf("[%d][%p] ->\n", i++, pos);
	}
	printf("\n");
}	


static inline void SingleListAddTail(struct S_LIST_NODE *new_node,
				  struct S_LIST_NODE *prev_node)
{
	prev_node->next = new_node;
	new_node->next = new_node;
}

#ifdef __cplusplus
}
#endif


#endif
