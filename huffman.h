#pragma once
#include<fstream>
#include<vector>
#include<sstream>
#include<bitset>
#include"tree.h"
#define CHARNUM 128



void encode();
void decode();
char decodeFromTree(char k, characters* point, treeRoot* tree);
