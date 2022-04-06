#include <iostream>
#include <string>
#include "huffman.h"
#include "queue.h"
#include "tree.h"

#define CHARNUM 128
using namespace std;

int main()
{
	string txt = "abbcccddddeeeee";
	characters*cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;
	/*txt.length()返回的是un int,
	所以i类型为un int更规范也更安全*/
	for (int i = 0; i < 128; i++)
		cells[i].id = i;
	for (unsigned int i = 0; i < txt.length(); i++) 
	{	
		//分析文本字符频率
		cells[(int)txt[i]].weight++;
	}
	for (int i = 0; i < CHARNUM; i++)
	{	
		//排序插入queue
		if (cells[i].weight)
		{
			que->addQueue(&cells[i]);
		}
	}
	que->printque();
	//insert to the tree
	tree->buildTree(que);
	que->printque();
	//tree->printBinpath(&cells['a']);
	return 0;
}
