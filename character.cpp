#include "character.h"

using namespace std;

characters::characters()
{
	id = 128;
	weight = 0;
	bincode = 0;
	parent = NULL;
	left = NULL;
	right = NULL;
	next = NULL;
}

characters::~characters()
{

}