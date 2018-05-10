// SampleSet-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

struct Node
{
	struct Node *next;
	int nVal;
};

Node *head;

void InsertNodeAtEnd(int data)
{
	Node *newNode1 = new Node();

	newNode1->nVal = data;
	newNode1->next = NULL;

	if (head == NULL)
	{
		head = newNode1;
	}
	else
	{
		Node *temp = head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode1;
	}
}

void InsertNodeAtBegining(int data)
{
	Node *newNode1 = new Node();

	newNode1->nVal = data;
	newNode1->next = head;

	head = newNode1;
}

void InsertNodeAt(int nPos, int data)
{
	Node *temp = head;
	Node *tempNext;

	Node *newNode1 = new Node();

	newNode1->nVal = data;

	for (int n = 0; n < nPos - 1 && temp->next != NULL; n++)
	{
		temp = temp->next;
	}

	tempNext = temp->next;

	temp->next = newNode1;
	newNode1->next = tempNext;

}

void PrintNodes(Node *printNode)
{
	std::cout << std::endl << "Printing Nodes: " << std::endl;
	Node *temp = printNode;
	while (temp != NULL)
	{
		std::cout << "Value: " << temp->nVal <<  "  ::  CurrentNode: " << temp << std::endl;
		temp = temp->next;
	}
}

void ReverseLinkList()
{
	
	Node *currentNode = head, *nextNode = NULL, *prevNode = NULL;
	while (currentNode != NULL)
	{
		nextNode = currentNode->next;
		currentNode->next = prevNode;
		prevNode = currentNode;
		currentNode = nextNode;
		PrintNodes(prevNode);
	}
	head = prevNode;
}

void MidElementInLinkedList()
{
	Node *slowNode = head, *fastNode = head;

	while (slowNode && fastNode && fastNode->next)
	{
		slowNode = slowNode->next;
		fastNode = fastNode->next->next;

	/*	if (slowNode == fastNode)
		{
			break;
		}*/
	}
	std::cout << std::endl << "Middle Node: " << slowNode << " :: Value: " << slowNode->nVal;
}

void CreateLoopNode()
{
	Node* loopNode = head->next->next;

	Node* temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}

	temp->next = loopNode;
}

void FixLoopNode()
{
	Node *slowNode = head, *fastNode = head;

	while (slowNode && fastNode && fastNode->next)
	{
		slowNode = slowNode->next;
		fastNode = fastNode->next->next;

		if (slowNode == fastNode)
		{
			break;
		}
	}

	std::cout << std::endl << "Last Node: " << slowNode << " :: Value: " << slowNode->nVal;

	Node *loopNode = slowNode;

	Node *ptr1, *ptr2;
	ptr1 = head;

	while (1)
	{
		ptr2 = loopNode;

		while (ptr2->next != loopNode && ptr2->next != ptr1)
			ptr2 = ptr2->next;

		if (ptr2->next == ptr1)
			break;

		ptr1 = ptr1->next;
	}
	ptr2->next = NULL;
}

void FindNthNode(int nPos)
{
	Node *targetNode, *lastNode;
	targetNode = lastNode = head;

	int nCount = 0;

	while (nCount < nPos - 1 && lastNode->next != NULL)
	{
		lastNode = lastNode->next;
		nCount++;
	}

	while (lastNode->next != NULL)
	{
		targetNode = targetNode->next;
		lastNode = lastNode->next;
	}

	std::cout << std::endl << nPos << " Node from the end: " << targetNode->nVal << " :: Node: " << targetNode;
}

void CallBack_Fun(void(*Fun_Ptr)(int), int nVal)
{
	Fun_Ptr(nVal);
}
template <typename T>
const T& Result(T a1, T a2)
{
	return a1 + a2;

}

void Template()
{
	
	std::cout << std::endl << "Sum: 5 + 25: " << Result(5, 25);;
	
	std::cout << std::endl << "Sum: 1.27 + 55.84: " << Result(1.27, 55.84);

	std::cout << std::endl;

}
int _tmain(int argc, _TCHAR* argv[])
{
	InsertNodeAtEnd(3);
	InsertNodeAtEnd(4);
	InsertNodeAtEnd(7);
	InsertNodeAtEnd(9);

	InsertNodeAtBegining(20);

	PrintNodes(head);

	MidElementInLinkedList();

	InsertNodeAt(3, 50);

	PrintNodes(head);

	//ReverseLinkList();

	//PrintNodes(head);

	MidElementInLinkedList();

	CreateLoopNode();

	FixLoopNode();

	PrintNodes(head);

	FindNthNode(5);

	FindNthNode(3);

	void(*Fun_Ptr)(int) = FindNthNode;

	CallBack_Fun(Fun_Ptr, 4);
	
	Template();

	return 0;
}

