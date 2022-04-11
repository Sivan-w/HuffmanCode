#include <string>
#include<bitset>
#include<fstream>
#include "huffman.h"

using namespace std;

int main()
{ 
	do {
		int flag;
		cout << "请选择功能：\n1.压缩.txt文件\n2.解码.tiny文件\n3.退出程序\n（输入对应序号即可）" << endl;
		cin >> flag;
		switch (flag)
		{
		case 1:
			encode();
			break;
		case 2:
			decode();
			break;
		case 3:
			return 0;
		default:
			return 0;
		}
	} while (1);
	return 0;
}
