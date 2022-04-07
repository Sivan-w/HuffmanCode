#pragma once
#include <iostream>

class characters
{
public:
	int id;
	int weight;
	int bincode;
	characters* next;
	characters* parent;
	characters* left;
	characters* right;

	characters();
	~characters();

private:

};

