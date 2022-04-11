#include"huffman.h"



using namespace std;

void encode()
{
	//读取txt文件
	string txt;
	stringstream buffer;
	string txtPath = "D:\\test.txt";
	string tinyPath;

	cout << "请输入.txt文件路径：\n（例如：“D:\\test.txt”）\n>>>";
	//cin >> txtPath;
	fstream file;
	file.open(txtPath, ios::in | ios::binary);
	buffer << file.rdbuf();
	txt = buffer.str();
	file.close();

	if (txt.length() == 0)
	{
		cout << "empty file! Are you kidding me?" << endl;
		return;
	}

	cout << "请指定.tiny文件存放路径：\n（例如：“D:\\test.tiny”）\n>>>";
	tinyPath = "D:\\test.tiny";
	//cin >> tinyPath;

	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;

	/*txt.length()返回的是un int,
	所以i类型为un int更规范也更安全*/
	for (int i = 0; i < 128; i++)
		cells[i].id = i;
	//cout << txt.size() << endl;
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

	cout << "初始化数据列：" << endl;
	que->printque();

	//把编码信息写入tiny文件
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

	cout << "打印树序列：" << endl;
	que->printque();
	//tree->printBinpath(&cells['a']);
	
	//encode to the file
	string bin32;
	vector<int> writeContent;  
	//看着舒服所以用vector。
	//考虑到爆内存，还是用一个int变量循环写入比较好。
	for (int i = 0; i < txt.length(); i++)
	{
		point = &cells[(int)txt[i]];
		while (point->parent)
		{
			bin32.push_back(point->bincode);
			point = point->parent;
			if (bin32.length() >= 32)
			{
				bitset<32> trans(bin32);
				writeContent.push_back(trans.to_ulong());
				bin32.clear();
			}
		}
	}
	if (bin32.length())
	{
		bitset<32> tran(bin32);
		writeContent.push_back(tran.to_ulong());
		writeContent.push_back(bin32.length());
	}
	else
		writeContent.push_back(32);
	for(int i=0;i<writeContent.size();i++)
		file.write((char*)&writeContent[i], sizeof(writeContent[i]));
	file.close();

	//第一个字节存放queue数量，之后按顺序存放cells的id和weight
	//然后存放二进制码，按int 32位存入，最后一字节存放前一个单位的有效字节数

}

void decode()
{
	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;
	for (int i = 0; i < 128; i++)
		cells[i].id = i;

	cout << "请输入.tiny文件路径：\n（例如：“D:\\test.tiny”）\n>>>";
	vector<bitset<32>> tinyContent;
	fstream file;
	bitset<32> reader;

	file.open("D:\\test.tiny", ios::in | ios::binary);
	
	while (file.read((char*)&reader, sizeof(reader)))
	{
		tinyContent.push_back(reader);
	}
	/*for (int i = 0; i < tinyContent.size(); i++)
		cout << tinyContent[i] << " ";*/

	for (unsigned int i = 1; i < 2*tinyContent[0].to_ulong() + 1; i+=2)
	{
		cells[tinyContent[i].to_ulong()].weight = tinyContent[i + 1].to_ulong();
		que->addQueue(&cells[tinyContent[i].to_ulong()]);
	}
	tree->buildTree(que);
	que->printque();

	vector<char> txt;
	string binString;
	characters* point = tree->first;
	binString = tinyContent[tinyContent.size() - 2].to_string();
	char flag;
	for (unsigned int i = 31; i >=32 - tinyContent[tinyContent.size() - 1].to_ulong(); i--)
	{
		if (flag = decodeFromTree(binString[i], point, tree))
			txt.push_back(flag);
	}
	for(int i=)
	//cout << endl << txt[0];

}

char decodeFromTree(char k, characters* point,treeRoot* tree)
{
	if (k == '0')
	{
		if (point->left == NULL)
		{
			k = (char)point->id;
			point = tree->first;
		}
		point = point->left;
	}
	else if (k == '1')
	{
		if (point->right == NULL)
		{
			k = (char)point->id;
			point = tree->first;
		}
		point = point->right;
	}
	else
		k = 0;
	return k;
}
