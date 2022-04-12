#pragma once
#include <iostream>

class characters
{
public:
	int id;
	int weight;
	char bincode;
	characters* next;
	characters* parent;
	characters* left;
	characters* right;

	characters();
	~characters();
};

