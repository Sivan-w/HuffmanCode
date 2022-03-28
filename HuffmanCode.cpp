#include <iostream>
#include <string>
#include "huffman.h"

#define CHARNUM 128
using namespace std;

int main()
{
	string txt = "arefi owe   hjf%&^$cvfaa";
	characters*cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	/*txt.length()返回的是un int,
	所以i类型为un int更规范也更安全*/
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
			addQueue(&cells[i],que);
		}
	}
	printque(que);
	return 0;
}
