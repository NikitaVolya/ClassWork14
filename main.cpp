
#include <iostream>
#include "LinkedList.h"

int main()
{
	LinkedList<int> lst{ 1, 6, 8, 4 };
	lst.push_back(5);

	std::cout << lst;

	return 0;
}