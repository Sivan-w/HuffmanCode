#include"huffman.h"



using namespace std;

void encode()
{
	//读取txt文件
	string txt;
	stringstream buffer;
	string txtPath="D:\\test.txt";
	//string txt;
	string tinyPath;
	cout << "请输入.txt文件路径：\n（例如：“D:\\test.txt”）\n<<<";
	//cin >> txtPath;
	fstream file;
	file.open(txtPath, ios::in|ios::binary);
	buffer << file.rdbuf();
	buffer >> txt;
	file.close();
	
	cout << "请指定.tiny文件存放路径：\n（例如：“D:\\test.tiny”）\n<<<";
	tinyPath = "D:\\test.tiny";
	//cin >> tinyPath;

	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;
	
	/*txt.length()返回的是un int,
	所以i类型为un int更规范也更安全*/
	for (int i = 0; i < 128; i++)
		cells[i].id = i;
	cout << txt.size();
	for (unsigned int i = 0; i < txt.size(); i++)
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

	//write queBuildInfo to file
	file.open(tinyPath, ios::out | ios::binary);
	file.write((char*)&que->size, 4);
	characters* point = que->first;
	while (point)
	{
		file.write((char*)&point->id, 4);
		file.write((char*)&point->weight, 4);
		point = point->next;
	}

	//build the tree
	tree->buildTree(que);
	que->printque();
	//tree->printBinpath(&cells['a']);

	//encode to the file
	
	
}







