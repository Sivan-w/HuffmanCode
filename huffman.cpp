#include<iostream>
#include<fstream>
#include<bitset>
#include"huffman.h"

using namespace std;

characters::characters()
{
	id = iteratorNum++;
	weight = 0;
	parent = NULL;
	left = NULL; 
	right = NULL;
	next = NULL;
}

characters::~characters()
{

}

treeRoot::treeRoot()
{
	first = NULL;
}

queueRoot::queueRoot()
{
	size = 0;
	first = NULL;
}

void addQueue(characters *cell, queueRoot* que)
{
	//������Ϊ�ջ����Ȩֵ��С��ֱ�Ӳ���
	if (que->first==NULL || cell->weight<=que->first->weight)
	{
		cell->next = que->first;
		que->first = cell;
		que->size++;
	}
	//�������
	else
	{
		//����������
		characters* iteratorChar = que->first;
		while (iteratorChar->next != NULL && cell->weight>iteratorChar->next->weight )
		{
			iteratorChar = iteratorChar->next;
		}
		cell->next = iteratorChar->next;
		iteratorChar->next = cell;
		que->size++;
	}
}

void printque(queueRoot *que)
{
	characters* point;
	point = que->first;
	while (point)
	{
		cout << point->id << (char)point->id <<" "<<point->weight << endl;
		point = point->next;
	}
}