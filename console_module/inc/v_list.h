/*****************************************************************
** 文件名:链表模块 v_list.h
** 
 
** 创建人: 
** 日  期: 
** 描  述: 
** 版  本: 

** 修改人:
** 日  期:
** 修改描述:
** 版  本: 
******************************************************************/
#ifndef _V_LIST_H_
#define _V_LIST_H_

#include "v_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/*****************************************************************
* 宏定义
******************************************************************/

#define V_OFFSET_OF(type,member)	\
		((V_UINT32)(&(((type *)0)->member)))
#define V_CONTAINER_OF(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
		(type *)( (char *)__mptr - V_OFFSET_OF(type,member) );})

/*	获取链表节点所在结构体*/
#define V_LIST_ENTRY(ptr, type, member) \
		V_CONTAINER_OF(ptr, type, member)

/*	遍历链表*/
#define V_LIST_FOR_EACH(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)



#define LIST_HEAD_INIT(name) { &(name), &(name) }

/*	list head申明*/
#define LIST_HEAD(name) \
	struct V_LIST_HEAD name = LIST_HEAD_INIT(name)

/* list head初始化*/
#define INIT_LIST_HEAD(ptr) do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

/*****************************************************************
* 结构定义
******************************************************************/

struct V_LIST_HEAD
{
	struct V_LIST_HEAD *next;
	struct V_LIST_HEAD *prev;
};

/*****************************************************************
* 函数原型声明
******************************************************************/

/*****************************************************************
  Function:       插入节点
  Description:    在列表的已知两节点间插入节点
  Input:	pNew,	新节点
  		pPrev,	 前一节点
  		pNext，	后一节点
 
******************************************************************/
static inline V_VOID V_ListAdd(struct V_LIST_HEAD *pNew,
				  struct V_LIST_HEAD *pPrev,
				  struct V_LIST_HEAD *pNext)
{
	pNext->prev = pNew;
	pNew->next = pNext;
	pNew->prev = pPrev;
	pPrev->next = pNew;
}

/*****************************************************************
  Function:       在列表尾部添加节点
  Description:    在列表尾部添加节点
  Input:	listNew,	新节点
  		listHead,	 链表头
  
******************************************************************/

static inline V_VOID V_ListAddTail(struct V_LIST_HEAD *listNew,struct V_LIST_HEAD *listHead)
{
	V_ListAdd(listNew,listHead->prev,listHead);
}


/*****************************************************************
  Function:       删除节点
  Description:    删除节点
  Input:	listEntry,	要删除的节点
 ******************************************************************/

static inline V_VOID V_ListDel(struct V_LIST_HEAD *listEntry)
{
	listEntry->next->prev = listEntry->prev;
	listEntry->prev->next = listEntry->next;
	listEntry->next = NULL;
	listEntry->prev = NULL;
}


/*****************************************************************
  Function:      判断链表是否为空
  Description:   判断链表是否为空
  Input:	listHead,	 链表头
  Return:        链表为空，则返回V_TRUE，非空则返回V_FALSE      

******************************************************************/

static inline V_BOOL V_ListIsEmpty(struct V_LIST_HEAD *listHead)
{
	return (listHead->next == listHead);
}


/*****************************************************************
  Function:      打印链表(调试用)
  Description:    打印链表
  Input:	listHead,	 链表头
  Return:        链表为空，则返回V_TRUE，非空则返回V_FALSE      

******************************************************************/
static inline V_RET V_ListDump(const V_CHAR *pcString,struct V_LIST_HEAD *listHead)
{
	struct V_LIST_HEAD *pNode;

	printf("%s:",pcString);

	V_LIST_FOR_EACH(pNode,listHead)
	{
		printf("%p->",pNode);
		
	}
	printf("\n");
	return V_OK;
}

#ifdef __cplusplus
}
#endif

#endif


