#include"huffman.h"



using namespace std;

void encode()
{
	//��ȡtxt�ļ�
	string txt;
	stringstream buffer;
	string txtPath;
	string tinyPath;

	cout << "������.txt�ļ�·����\n�����磺��D:\\test.txt����\n>>>";
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

	cout << "��ָ��.tiny�ļ����·����\n�����磺��D:\\test.tiny����\n>>>";
	cin >> tinyPath;

	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;

	/*txt.length()���ص���un int,
	����i����Ϊun int���淶Ҳ����ȫ*/
	for (int i = 0; i < 128; i++)
		cells[i].id = i;
	//cout << txt.size() << endl;
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

	cout << "��ʼ�������У�" << endl;
	que->printque();

	//�ѱ�����Ϣд��tiny�ļ�
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

	cout << "��ӡ�����У�" << endl;
	que->printque();
	//tree->printBinpath(&cells['a']);
	
	//encode to the file
	string bin32;
	vector<int> writeContent;  
	//�������������vector��
	//���ǵ����ڴ棬������һ��int����ѭ��д��ȽϺá�
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

	//��һ���ֽڴ��queue������֮��˳����cells��id��weight
	//Ȼ���Ŷ������룬��int 32λ���룬���һ�ֽڴ��ǰһ����λ����Ч�ֽ���

}

void decode()
{
	characters* cells = new characters[CHARNUM];
	queueRoot* que = new queueRoot;
	treeRoot* tree = new treeRoot;
	for (int i = 0; i < 128; i++)
		cells[i].id = i;

	cout << "������.tiny�ļ�·����\n�����磺��D:\\test.tiny����\n>>>";
	string tinyPath;
	cin >> tinyPath;
	vector<bitset<32>> tinyContent;
	fstream file;
	bitset<32> reader;

	file.open(tinyPath, ios::in | ios::binary);
	
	//��ȡtiny�ļ�
	while (file.read((char*)&reader, sizeof(reader)))
	{
		tinyContent.push_back(reader);
	}
	file.close();
	/*for (int i = 0; i < tinyContent.size(); i++)
		cout << tinyContent[i] << " ";*/

	//��ȡ����Ϣ������
	for (unsigned int i = 1; i < 2*tinyContent[0].to_ulong() + 1; i+=2)
	{
		cells[tinyContent[i].to_ulong()].weight = tinyContent[i + 1].to_ulong();
		que->addQueue(&cells[tinyContent[i].to_ulong()]);
	}
	tree->buildTree(que);
	que->printque();

	//���������
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

	//д��.txt�ļ�
	cout << "������Ҫ�����txt�ļ�·����\n�����硰D:\\test.txt����\n>>>";
	string txtPath;
	cin>>txtPath;
	file.open(txtPath,ios::out);
	for (int i = 0; i < txt.size(); i++)      //��1��ʼ����Ϊtxt���һλ�����롣
		file.write(&txt[txt.size() - i-1], sizeof(txt[txt.size() - i-1]));
	file.close();
	cout << "��ѹ�ɹ���"<<endl<<endl;
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
