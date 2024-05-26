
#include <iostream>
#include <string>

#include "LinkedList.h"

class Human
{
public:
	std::string name;

	Human(const std::string& pName) : name(pName) {};
};

class Department
{
private:
	Human& worker;

public:
	Department(Human& persone) : worker(persone) {};

	void printWorkers()
	{
		std::cout << worker.name;
	}
};

int main()
{
	Human testHuman("Allan");
	Department testDepartment{ testHuman };
	testDepartment.printWorkers();

	return 0;
}