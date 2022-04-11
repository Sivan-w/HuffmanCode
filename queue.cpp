#include "queue.h"


using namespace std;

queueRoot::queueRoot()
{
	size = 0;
	first = NULL;
}

void queueRoot::addQueue(characters* cell)
{
	//������Ϊ�ջ����Ȩֵ��С��ֱ�Ӳ���
	if (this->first == NULL || cell->weight <= this->first->weight)
	{
		cell->next = this->first;
		this->first = cell;
		this->size++;
	}
	//�������
	else
	{
		//����������
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