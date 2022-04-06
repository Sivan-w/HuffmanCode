#pragma once
#include "character.h"
class queueRoot
{
public:
	unsigned int size;
	characters* first;

	void addQueue(characters* cell);
	void printque();
	queueRoot();
};



