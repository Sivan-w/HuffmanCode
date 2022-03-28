#pragma once

class characters
{
public:
	int id;
	int weight;
	characters* next;
	characters* parent;
	characters* left;
	characters* right;

	characters();
	~characters();

private:

};

class treeRoot
{
public:
	characters* first;
	treeRoot();

};

class queueRoot
{
public:
	unsigned int size;
	characters* first;

	queueRoot();
};

void addQueue(characters* cell, queueRoot* que);
void printque(queueRoot* point);
//需要声明为static，否则会报错出现多重定义
static int iteratorNum = 0; 
