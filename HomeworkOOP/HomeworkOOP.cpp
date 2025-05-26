#include <iostream>
#include "MyString.h"
#include "List.hpp"

int main()
{
	List<List<int>> l;

	MyString m = "j";
	m += "new";
	std::cout << m;
}