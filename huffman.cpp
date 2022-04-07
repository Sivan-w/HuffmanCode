#include"huffman.h"



using namespace std;

void encode()
{
	//��ȡtxt�ļ�
	string txt;
	stringstream buffer;
	string txtPath="D:\\test.txt";
	//string txt;
	string tinyPath;
	cout << "������.txt�ļ�·����\n�����磺��D:\\test.txt����\n<<<";
	//cin >> txtPath;
	fstream file;
	file.open(txtPath, ios::in|ios::binary);
	buffer << file.rdbuf();
	buffer >> txt;
	file.close();
	
	cout << "��ָ��.tiny�ļ����·����\n�����磺��D:\\test.tiny����\n<<<";
	tinyPath = "D:\\test.tiny";
	//cin >> tinyPath;

	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;
	
	/*txt.length()���ص���un int,
	����i����Ϊun int���淶Ҳ����ȫ*/
	for (int i = 0; i < 128; i++)
		cells[i].id = i;
	cout << txt.size();
	for (unsigned int i = 0; i < txt.size(); i++)
	{
		//�����ı��ַ�Ƶ��
		cells[(int)txt[i]].weight++;
	}
	for (int i = 0; i < CHARNUM; i++)
	{
		//�������queue
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







