#include"huffman.h"



using namespace std;

void encode()
{
	//读取txt文件
	string txt;
	stringstream buffer;
	string txtPath;
	string tinyPath;

	cout << "请输入.txt文件路径：\n（例如：“D:\\test.txt”）\n>>>";
	cin >> txtPath;
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
	cin >> tinyPath;

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
	string tinyPath;
	cin >> tinyPath;
	vector<bitset<32>> tinyContent;
	fstream file;
	bitset<32> reader;

	file.open(tinyPath, ios::in | ios::binary);
	
	//读取tiny文件
	while (file.read((char*)&reader, sizeof(reader)))
	{
		tinyContent.push_back(reader);
	}
	file.close();
	/*for (int i = 0; i < tinyContent.size(); i++)
		cout << tinyContent[i] << " ";*/

	//读取树信息、建树
	for (unsigned int i = 1; i < 2*tinyContent[0].to_ulong() + 1; i+=2)
	{
		cells[tinyContent[i].to_ulong()].weight = tinyContent[i + 1].to_ulong();
		que->addQueue(&cells[tinyContent[i].to_ulong()]);
	}
	tree->buildTree(que);
	que->printque();

	//解码二进制
	vector<char> txt;
	string binString;
	characters* point = tree->first;

	binString = tinyContent[tinyContent.size() - 2].to_string();
	for (unsigned int i = 31; i >= 32 - tinyContent[tinyContent.size() - 1].to_ulong(); i--)
		decodeFromTree(binString[i], &point, tree, txt);
	for (int i = tinyContent.size() - 3; i >= 2 * tinyContent[0].to_ulong() + 1; i--)
	{
		binString = tinyContent[i].to_string();
		for(int i=31;i>=0;i--)
			decodeFromTree(binString[i], &point, tree, txt);
	}
	txt.push_back((char)point->id);

	//写入.txt文件
	cout << "请输入要保存的txt文件路径：\n（例如“D:\\test.txt”）\n>>>";
	string txtPath;
	cin>>txtPath;
	file.open(txtPath,ios::out);
	for (int i = 0; i < txt.size(); i++)      //从1开始，因为txt最后一位是乱码。
		file.write(&txt[txt.size() - i-1], sizeof(txt[txt.size() - i-1]));
	file.close();
	cout << "解压成功！"<<endl<<endl;
}

void decodeFromTree(char k, characters** point, treeRoot* tree, std::vector<char> &txt)
{
	if (k == '0')
	{
		if ((*point)->left == NULL)
		{
			//cout << (char)(*point)->id;
			txt.push_back((char)(*point)->id);
			(*point) = tree->first;
		}
		(*point) = (*point)->left;
	}
	if (k == '1')
	{
		if ((*point)->right == NULL)
		{
			//cout << (char)(*point)->id;
			txt.push_back((char)(*point)->id);
			(*point) = tree->first;
		}
		(*point) = (*point)->right;
	}
}
