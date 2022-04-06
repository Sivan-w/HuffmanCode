#pragma once
#include "queue.h"

class treeRoot
{
public:
	characters* first;
	treeRoot();
	void buildTree(queueRoot *que);
	void printBinpath(characters* cell);
};