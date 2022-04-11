#include "queue.h"


using namespace std;

queueRoot::queueRoot()
{
	size = 0;
	first = NULL;
}

void queueRoot::addQueue(characters* cell)
{
	//若队列为空或插入权值最小就直接插入
	if (this->first == NULL || cell->weight <= this->first->weight)
	{
		cell->next = this->first;
		this->first = cell;
		this->size++;
	}
	//排序插入
	else
	{
		//创建迭代器
		characters* iteratorChar = this->first;
		while (iteratorChar->next != NULL && cell->weight > iteratorChar->next->weight)
		{
			iteratorChar = iteratorChar->next;
		}
		cell->next = iteratorChar->next;
		iteratorChar->next = cell;
		this->size++;
	}
}

void queueRoot::printque()
{
	characters* point;
	point = this->first;
	while (point)
	{
		cout  << (char)point->id << " "<<point->id<<" " << point->weight << endl;
		point = point->next;
	}
	cout <<"over" << endl<<endl;
}