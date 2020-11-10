#include <iostream>
#include <fstream>
#include "operations.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	string command = "";
	string fileName = "";
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv["<<i<<"] == " << argv[i] << endl;
	}

	if (argc >= 2)
	{
		command = argv[1];
		if (argc == 2)
			fileName = "";
		else 
			fileName = argv[2];

		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		unsigned int sizeOfFile = file.tellg();
		if (command == "--add" && sizeOfFile > 2000000)  
			cout << "Too large file " << endl;

		if (command == "--account_name")
		{
			cout << "account";
		}
		else if (command == "--add" && sizeOfFile < 2000000)
		{
			cout << "--add if" << endl;
			addFileToContainer(fileName);
			addLog(fileName, "added", sizeOfFile);
		}
		else if (command == "--delete")
		{
			cout << "delete file" << endl;
			addLog(fileName, "deleted", sizeOfFile);
			deleteFileFromContainer(fileName);
		}
		else if (command == "--logs")
		{
			cout << "logs" << endl;
			printLogs();
		}
		else
			cout << "Unknown option";
	}
	else
	{
		cout << "Too less parameters" << endl;
	}
	return 0;
}