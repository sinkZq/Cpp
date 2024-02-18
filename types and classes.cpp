#include <iostream>
#include <string>

class iterClass {
	public:
		int cNum;
		std::string cString;
		char cChar;

};

bool largeStr(std::string str) {
	if (str.size() > 5) 
	{
		return true;
	}	
	else 
	{
		return false;
	}
};

bool largeNum(int num) {
	if (num > 5)
	{
		return true;
	}
	else
	{
		return false;
	}
};

int main() {
	iterClass newObject;

	newObject.cNum = 100;
	newObject.cString = "dasdasfhajdsajdajd";
	newObject.cChar = 'a'; //char types are single characters identified with '' instead of ""

	if (largeNum(newObject.cNum) && largeStr(newObject.cString))
	{
		std::cout << newObject.cNum << " large " << newObject.cString << std::endl;
	}
	else
	{
		std::cout << newObject.cNum << " small " << newObject.cString << std::endl;
	}

	return 0;
};
