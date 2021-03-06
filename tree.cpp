#include "tree.h"


using namespace std;

treeRoot::treeRoot()
{
	first = NULL;
}

void treeRoot::buildTree(queueRoot* que)
{
	characters* point = new characters;
	point->next = que->first;

	while (point->next->next != NULL)
	{
		characters* dad = new characters;

		dad->left = point->next;
		dad->right = point->next->next;

		dad->left->parent = dad;
		dad->right->parent = dad;

		dad->left->bincode = '0';
		dad->right->bincode = '1';

		dad->weight = dad->left->weight + dad->right->weight;
		que->addQueue(dad);
		point = point->next->next;
		//que->printque();
	}
	this->first = point->next;
}

void treeRoot::printBinpath(characters* cell)
{
	characters* point = cell;
	while (point != NULL)
	{
		cout << point->id << " ";
		point = point->parent;
	}
	cout << endl;
}