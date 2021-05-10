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
void iterativeInorder(Node* node) // 반복적 중위 순회 함수
{
	int top= 1;
	Node stack[MAX_STACK_SIZE];
	for(;;)
	{
		for(; node; node = node -> left)
		{
			push(node);
		}
		node = pop();

		if(!node) break;
		{
			printf("%d", node -> key);
			node = node -> right;
		}
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 레벨 순서 트리 순회 함수
{
	int front = rear = 0;
	Node queue[MAX_QUEUE_SIZE];

	if(!ptr)
	{
		return;
	}
	enqueue(ptr);

	for(;;)
	{
		ptr =
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
	Node* parent = NULL;
	Node* node = head -> left;
	Node* child;
	Node* del;
	Node* del2;

	if(node == head)
	{
		printf("키가 존재하지않습니다\n");
		return 1;
	}

	while(node -> key != key)
	{
		parent = node;

		if(node -> key > key)
		{
			node = node -> left;
		}
		else
			node = node -> right;
	}

	if(node -> left == NULL && node -> right == NULL)
	{
		if(parent)
		{
			if(parent -> left == node)
			{
				parent -> left = NULL;
			}
			else
			{
				parent -> right = NULL;
			}
		}
		else
			head -> left = head;
	}
	else if (node -> left == NULL || node -> right == NULL)
	{
		child = (node -> left != NULL) ? node -> left : node -> right;

		if(parent)
		{
			if(parent -> left == node)
			{
				parent -> left == child;
			}
			else
			{
				parent -> right = child;
			}
		}
	}
	else
	{
		del2 = node;
		del = node -> right;

		while(del -> left != NULL)
		{
			del2 = del;
			del = del -> left;
		}
		if(del2 -> left == del)
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
}

void push(Node* aNode)
{
}



Node* deQueue()
{
}

void enQueue(Node* aNode)
{
}





