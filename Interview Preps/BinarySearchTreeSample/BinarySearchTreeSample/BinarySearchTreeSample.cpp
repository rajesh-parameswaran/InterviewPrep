// BinarySearchTreeSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;



struct Node
{
	int nKey;
	struct Node *left, *right;
};

Node *root;

Node* createNewNode(int nKey)
{
	Node *newNode = new Node();
	newNode->nKey = nKey;
	newNode->left = newNode->right = NULL;
	return newNode;
}
void inOrderTraversal(Node *root)
{
	if (root != NULL)
	{
		inOrderTraversal(root->left);
		cout << " " << root->nKey;
		inOrderTraversal(root->right);
	}
}

void preOrderTraversal(Node *root)
{
	if (root != NULL)
	{
		cout << " " << root->nKey;
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}

void postOrderTraversal(Node *root)
{
	if (root != NULL)
	{
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		cout << " " << root->nKey;
	}
}

int findHeightOfTree(Node *root)
{
	if (root == NULL)
		return 0;

	int lHeight = findHeightOfTree(root->left);
	int rHeight = findHeightOfTree(root->right);

	if (lHeight > rHeight)
		return lHeight + 1;
	else
		return rHeight + 1;

}
void printGivenLevel(Node *root, int nLevel)
{
	if (root == NULL)
		return;

	if (nLevel == 1)
	{
		cout << " " << root->nKey;
	}
	else if (nLevel > 1)
	{
		printGivenLevel(root->left, nLevel - 1);
		printGivenLevel(root->right, nLevel - 1);
	}
}
void levelOrderTraversal(Node *root)
{
	int height = findHeightOfTree(root);

	cout << endl << "Height: " << height << endl;
	int i;
	for (i = 1; i <= height; i++)
	{
		printGivenLevel(root, i);
	}

}
Node* insertNode(Node *node, int nKey)
{
	if (node == NULL)
		return createNewNode(nKey);

	if (nKey < node->nKey)
		node->left = insertNode(node->left, nKey);
	else if (nKey > node->nKey)
		node->right = insertNode(node->right, nKey);

	return node;
}

void DeleteNodes(Node* root) 
{
	if (root == NULL)
		return;
	if (root->left != NULL)
		DeleteNodes(root->left);
	if (root->right != NULL)
		DeleteNodes(root->right);

	delete root;

	return;
}

int _tmain(int argc, _TCHAR* argv[])
{
	root = insertNode(root, 50);

	insertNode(root, 20);
	insertNode(root, 10);

	insertNode(root, 80);
	insertNode(root, 40);
	insertNode(root, 30);
	insertNode(root, 60);

	cout << endl << "Pre-Order-Traversal: ";
	preOrderTraversal(root);
	cout << endl << "In-Order-Traversal: ";
	inOrderTraversal(root);
	cout << endl << "Post-Order-Traversal: ";
	postOrderTraversal(root);
	cout << endl << "Level-Order-Traversal: ";
	levelOrderTraversal(root);
	cout << endl;

	DeleteNodes(root);

	return 0;
}

