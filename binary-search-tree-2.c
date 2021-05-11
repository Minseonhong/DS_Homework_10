#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */




int main()
{
	printf("----- [민선홍] [2018038028] -----");
	char command; // 문자형 변수 command 생성
	int key; // 정수형 변수 key 생성
	Node* head = NULL; // Node형의 포인터 변수 head 생성한 뒤, NULL로 초기화

	do{ // 반복문 실행
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr) // 재귀함수를이용하여 중위순회 출력
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node) // 반복적 중위 순회 스택 함수
{
	for(;;) // 이중 반복문 실행
	{
		for(; node; node = node -> left)
		{
			push(node); // 스택에 삽입
		}
		node = pop(); // 스택에서 삭제

		if(!node) break; // 공백 스택
		{
			printf("[%d]", node -> key);
			node = node -> right;
		}
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨 순서 트리 순회 함수
{
	front = rear = -1;

	if(!ptr)
	{
		return;
	}
	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr)
		{
			printf("[%d]", ptr->key);
			if(ptr -> left)
			{
				enQueue(ptr -> left);
			}
			if(ptr -> right)
			{
				enQueue(ptr -> right);
			}
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* parent = NULL; // Node의 포인터형 변수 parent 생성한 뒤, NULL로 초기화
	Node* node = head -> left; // Node의 포인터형 변수 node 생성한 뒤, 헤더포인터가 가리키는 left 값 대입
	Node* child; // Node의 포인터형 변수 child 생성
	Node* del; // Node의 포인터형 변수 del 생성
	Node* del2; // Node의 포인터형 변수 del2 생성

	if(node == head) // 만일 헤더포인가 가라키는 left의 값이 들어가있는 node가 헤더포인터의 값과 같다면(루트노드가 없다면), 프린트문 출력
	{
		printf("삭제할 key의 값 노드가 없습니다.\n");
		return 1;
	}

	while(node -> key != key) // 삭제하려는 노드 탐색, node -> key의 값이 key의 값과 같을 때까지 반복
	{
		parent = node; // parent에 node 값 대입

		if(node -> key > key) // node -> key의 값이 key 값보다 클 경우
		{
			node = node -> left; // node에 node -> left 값을 넣어 왼쪽으로 이동
		}
		else // 아니라면 node에 node -> right 값을 넣어 오른쪽으로 이동
			node = node -> right;
	}

	if(node -> left == NULL && node -> right == NULL) // 단말 노드일 경우
	{
		if(parent)
		{
			if(parent -> left == node)
			{
				parent -> left = NULL; // parent -> left의 값에 NULL 대입
			}
			else
			{
				parent -> right = NULL; // parent -> right의 값에 NULL 대입
			}
		}
		else
			head -> left = head; // 헤더포인터가 가리키는 left의 값을 헤더포인터의 값으로 대입
	}
	else if (node -> left == NULL || node -> right == NULL) // 하나의 서브트리를 가질 경우
	{
		child = (node -> left != NULL) ? node -> left : node -> right; // node -> left의 값이 NULL이 참이면 node -> left의 값 대입, 거짓이면 node -> right 값 대입

		if(parent)
		{
			parent -> right = child; // parent -> right 값에 조건연산자로 인해 대입되엉 있는 child의 값 대입

		}
	}
	else // 두 개의 서브트리를 가질 경우
	{
		/* 삭제하려는 노드의 오른쪽 서브트리에서 제일 작은 값 탐색 */
		del2 = node; // del2 에 node 값 대입
		del = node -> right; // del은 node가 가리키는 right의 값

		while(del -> left != NULL)
		{
			del2 = del;
			del = del -> left;
		}
		if(del2 -> left == del) // 왼쪽 끝까지 왔지만, 마지막 노드의 오른쪾에 자식 노드가 존재 가능하여 조건문 실행
		{
			del2 -> left = del -> right;
		}
		else
		{
			del2 -> right = del -> right;
		}
		node -> key = del -> key;
		node = del;
	}
	free(node);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node* p = NULL; // Node의 포인터 변수 p 를 생성하여 NULL로 초기화
	if (top >= 0) // top의 값이 0보다 크거나 작을경우,
	{
		p = stack[top--]; // stack배열의 top의 값을 감소하여 p에 대입
	}
	return p; // p의 값 리턴
}

void push(Node* aNode)
{
	if(top < MAX_STACK_SIZE - 1 && aNode != NULL) // 만약 top이 스택의 사이즈 -1 보다 작고, aNode의 값이 NULL이 아닐 경우
	{
		stack[++top] = aNode; // stack배열의 top의 값을 증감시킨 뒤, aNode의 값 대입
	}
}



Node* deQueue()
{
	Node* node = NULL;

	if(front == rear)
	{
		return node;
	}
	front ++;
	node = queue[front];
	return node;
}


void enQueue(Node* aNode)
{
	if(rear == MAX_QUEUE_SIZE -1 )
	{
		return;
	}
	rear ++;
	queue[rear] = aNode;
}





