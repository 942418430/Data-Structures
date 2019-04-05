#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SListDataType;

//定义节点结构体
typedef struct Node{
	SListDataType valueue;   //保存的值
	struct Node *next; //保存下一个节点的地址

} Node;

//定义头指针
typedef struct SList{
	Node *first;   
} SList ;

//链表初始化
void SLisInit(SList *s){
	assert(s != NULL);
	s->first = NULL;
}

//头插
void SListPushFront(SList *s, SListDataType v){
	Node *node = (Node*)malloc(sizeof(node));
	node->valueue = v;
	node->next = s->first;
	s->first = node;
}

//尾插
void SListPushBack(SList *s, SListDataType v){
	Node *node = (Node *)malloc(sizeof(Node));
	node->valueue = v;
	node->next = NULL;

	if (s->first == NULL) {
		// 链表中为空的情况
		s->first = node;
		return;
	}
	// 链表中至少有一个结点的情况

	// 如何找到最后一个结点，隐含着链表中一定有结点
	Node *cur = s->first;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	// cur->next 一定是  NULL，也就是最后一个结点
	cur->next = node;
}

//链表的头删
void SListPopFront(SList *s) {
	assert(s != NULL);			// 不能没有链表
	assert(s->first != NULL);	// 不能没有结点

	Node *next = s->first->next;
	free(s->first);
	s->first = next;
}

//链表的尾删
void SListPopBack(SList *s) {
	assert(s != NULL);			// 不能没有链表
	assert(s->first != NULL);	// 不能没有结点

	if (s->first->next == NULL) {
		// 链表中只有一个结点
		free(s->first);
		s->first = NULL;
		return;
	}

	Node *cur;
	for (cur = s->first; cur->next->next != NULL; cur = cur->next) {
	}

	// cur 就是倒数第二个结点
	// cur->next->next = NULL;
	free(cur->next);
	cur->next = NULL;
}

//链表的逆序
//三
struct Node* reverseList(struct Node* head) {
	struct Node *newHead = NULL;

	struct Node *cur = head;
	while (cur != NULL) {
		struct Node *node = cur;
		cur = cur->next;

		// 把 node 插入到新链表 newHead
		node->next = newHead;
		newHead = node;
	}

	return newHead;
}

//查找
Node * SListFind(SList *s, SListDataType v) {
	for (Node *cur = s->first; cur != NULL; cur = cur->next) {
		if (cur->valueue == v) {
			return cur;
		}
	}

	return NULL;
}

//在pos后插入
// pos 一定是链表中的结点
void SListInsertAfter(SList *s, Node *pos, SListDataType v) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->valueue = v;
	node->next = pos->next;
	pos->next = node;
}


//删除pos后的节点
// pos 一定是链表中的结点，并且 pos 不是链表的最后一个结点
void SListEraseAfter(SList *s, Node *pos) {
	Node *next = pos->next;
	pos->next = pos->next->next;
	free(next);
	next = NULL;
}

//销毁链表
void SListDestroy(SList *s) {
	Node *next;
	for (Node *cur = s->first; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

	s->first = NULL;
}


//删除结点v
void SListRemove(SList *s, SListDataType v) {
	if (s->first == NULL) {
		// 链表为空
		return;
	}

	if (s->first->valueue == v) {
		// v 就是第一个结点的情况
		Node *next = s->first->next;
		free(s->first);
		s->first = next;
		return;
	}

	Node *cur = s->first;
	while (cur->next != NULL) {
		if (cur->next->valueue == v) {
			Node *next = cur->next->next;
			free(cur->next);
			cur->next = next;
			return;
		}

		cur = cur->next;
	}
}

struct Node* removeElements(struct Node* head, int value) {
	if (head == NULL) {
		return NULL;
	}

	// 先不管第一个结点的情况
	struct Node *cur = head;
	while (cur->next != NULL) {
		if (cur->next->valueue == value) {
			struct Node *next = cur->next->next;
			free(cur->next);
			cur->next = next;
		}
		else {
			cur = cur->next;
		}
	}

	if (head->valueue == value) {
		Node *newHead = head->next;
		free(head);
		return newHead;
	}
	else {
		return head;
	}
}


struct Node *Merge(struct Node *l1, struct Node *l2) {
	if (l1 == NULL) {
		return l2;
	}

	if (l2 == NULL) {
		return l1;
	}

	struct Node *c1 = l1;
	struct Node *c2 = l2;
	struct Node *result = NULL;	// 结果链表的第一个结点地址
	struct Node *tail = NULL;	// 结果链表的最后一个结点地址
	while (c1 != NULL && c2 != NULL) {
		if (c1->valueue <= c2->valueue) {
			// 取 l1 链表的结点
			if (tail == NULL) {
				result = tail = c1;
			}
			else {
				tail->next = c1;
				tail = c1;
			}

			c1 = c1->next;
		}
		else {
			// 取 l2 链表的结点
			if (tail == NULL) {
				result = tail = c2;
			}
			else {
				tail->next = c2;
				tail = c2;
			}

			c2 = c2->next;
		}
	}

	// l1 或者 l2 有一条链表的所有结点被去完了
	if (c1 != NULL) {
		tail->next = c1;	// c1 代表的不是一个结点，代表的是链表从 c1 的后序所有结点
	}
	else {
		tail->next = c2;
	}

	return result;
}

Node* partition(Node* pHead, int x) {
	Node *small = NULL;	// <
	Node *small_last = NULL;	// 比 x 小的最后一个结点
	Node *big = NULL;	// >=
	Node *big_last = NULL;	// 比 x 大于等于的最后一个结点

	for (Node *c = pHead; c != NULL; c = c->next) {
		if (c->valueue < x) {
			if (small_last == NULL) {
				small = small_last = c;
			}
			else {
				small_last->next = c;
				small_last = c;
			}
		}
		else {
			if (big_last == NULL) {
				big = big_last = c;
			}
			else {
				big_last->next = c;
				big_last = c;
			}
		}
	}

	if (small_last != NULL) {
		small_last->next = big;
	}

	if (big_last != NULL) {
		big_last->next = NULL;
	}

	if (small != NULL) {
		return small;
	}
	else {
		return big;
	}
}


Node* partition(Node* pHead, int x) {
	Node *small = NULL;	// <
	Node *big = NULL;	// >=
	Node *next;
	for (Node *c = pHead; c != NULL; c = next) {
		next = c->next;
		if (c->valueue < x) {
			c->next = small;
			small = c;
		}
		else {
			c->next = big;
			big = c;
		}
	}

	small = Reverse(small);
	big = Reverse(big);

	// ...
}

Node* deleteDuplication(Node* pHead) {
	if (pHead == NULL) {
		return NULL;
	}

	Node *fake = (Node *)malloc(sizeof(Node));
	fake->next = pHead;

	Node *prev = fake;	// 永远是 p1 的前驱
	Node *p1 = pHead;	// p1 和 p2 负责进行 value 的比较
	Node *p2 = pHead->next;	// p2 还有个职责，找第一个不相等的结点

	while (p2 != NULL) {
		if (p1->valueue != p2->valueue) {
			prev = p1;
			p1 = p2;
			p2 = p2->next;
		}
		else {
			while (p2 != NULL && p2->valueue == p1->valueue) {
				p2 = p2->next;
			}

			// 删除的就是 [p1, p2)
			// 笔试题里先不考虑内存泄漏
			prev->next = p2;

			p1 = p2;
			if (p2 != NULL) {
				p2 = p2->next;
			}
		}
	}

	pHead = fake->next;
	free(fake);

	return pHead;
}