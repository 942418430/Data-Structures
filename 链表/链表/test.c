#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SListDataType;

//����ڵ�ṹ��
typedef struct Node{
	SListDataType valueue;   //�����ֵ
	struct Node *next; //������һ���ڵ�ĵ�ַ

} Node;

//����ͷָ��
typedef struct SList{
	Node *first;   
} SList ;

//�����ʼ��
void SLisInit(SList *s){
	assert(s != NULL);
	s->first = NULL;
}

//ͷ��
void SListPushFront(SList *s, SListDataType v){
	Node *node = (Node*)malloc(sizeof(node));
	node->valueue = v;
	node->next = s->first;
	s->first = node;
}

//β��
void SListPushBack(SList *s, SListDataType v){
	Node *node = (Node *)malloc(sizeof(Node));
	node->valueue = v;
	node->next = NULL;

	if (s->first == NULL) {
		// ������Ϊ�յ����
		s->first = node;
		return;
	}
	// ������������һ���������

	// ����ҵ����һ����㣬������������һ���н��
	Node *cur = s->first;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	// cur->next һ����  NULL��Ҳ�������һ�����
	cur->next = node;
}

//�����ͷɾ
void SListPopFront(SList *s) {
	assert(s != NULL);			// ����û������
	assert(s->first != NULL);	// ����û�н��

	Node *next = s->first->next;
	free(s->first);
	s->first = next;
}

//�����βɾ
void SListPopBack(SList *s) {
	assert(s != NULL);			// ����û������
	assert(s->first != NULL);	// ����û�н��

	if (s->first->next == NULL) {
		// ������ֻ��һ�����
		free(s->first);
		s->first = NULL;
		return;
	}

	Node *cur;
	for (cur = s->first; cur->next->next != NULL; cur = cur->next) {
	}

	// cur ���ǵ����ڶ������
	// cur->next->next = NULL;
	free(cur->next);
	cur->next = NULL;
}

//���������
//��
struct Node* reverseList(struct Node* head) {
	struct Node *newHead = NULL;

	struct Node *cur = head;
	while (cur != NULL) {
		struct Node *node = cur;
		cur = cur->next;

		// �� node ���뵽������ newHead
		node->next = newHead;
		newHead = node;
	}

	return newHead;
}

//����
Node * SListFind(SList *s, SListDataType v) {
	for (Node *cur = s->first; cur != NULL; cur = cur->next) {
		if (cur->valueue == v) {
			return cur;
		}
	}

	return NULL;
}

//��pos�����
// pos һ���������еĽ��
void SListInsertAfter(SList *s, Node *pos, SListDataType v) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->valueue = v;
	node->next = pos->next;
	pos->next = node;
}


//ɾ��pos��Ľڵ�
// pos һ���������еĽ�㣬���� pos ������������һ�����
void SListEraseAfter(SList *s, Node *pos) {
	Node *next = pos->next;
	pos->next = pos->next->next;
	free(next);
	next = NULL;
}

//��������
void SListDestroy(SList *s) {
	Node *next;
	for (Node *cur = s->first; cur != NULL; cur = next) {
		next = cur->next;
		free(cur);
	}

	s->first = NULL;
}


//ɾ�����v
void SListRemove(SList *s, SListDataType v) {
	if (s->first == NULL) {
		// ����Ϊ��
		return;
	}

	if (s->first->valueue == v) {
		// v ���ǵ�һ���������
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

	// �Ȳ��ܵ�һ���������
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
	struct Node *result = NULL;	// �������ĵ�һ������ַ
	struct Node *tail = NULL;	// �����������һ������ַ
	while (c1 != NULL && c2 != NULL) {
		if (c1->valueue <= c2->valueue) {
			// ȡ l1 ����Ľ��
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
			// ȡ l2 ����Ľ��
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

	// l1 ���� l2 ��һ����������н�㱻ȥ����
	if (c1 != NULL) {
		tail->next = c1;	// c1 ����Ĳ���һ����㣬������������ c1 �ĺ������н��
	}
	else {
		tail->next = c2;
	}

	return result;
}

Node* partition(Node* pHead, int x) {
	Node *small = NULL;	// <
	Node *small_last = NULL;	// �� x С�����һ�����
	Node *big = NULL;	// >=
	Node *big_last = NULL;	// �� x ���ڵ��ڵ����һ�����

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

	Node *prev = fake;	// ��Զ�� p1 ��ǰ��
	Node *p1 = pHead;	// p1 �� p2 ������� value �ıȽ�
	Node *p2 = pHead->next;	// p2 ���и�ְ���ҵ�һ������ȵĽ��

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

			// ɾ���ľ��� [p1, p2)
			// ���������Ȳ������ڴ�й©
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