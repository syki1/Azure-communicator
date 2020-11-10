#include <iostream>
#include "operations.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv[i] == " << argv[i] << endl;
	}

	if (argc >= 2)
	{
		//const char fileName[20] = "File.txt";
		const char* fileName = argv[2];
		string command = argv[1];

		if (command == "--account_name")
		{
			cout << "account";
		}
		else if (command == "--add")
		{
			cout << "--add if" << endl;
			addFileToContainer(fileName);
		}
		else if (command == "--delete")
		{
			cout << "delete file";
			deleteFileFromContainer(fileName);
		}
		else if (command == "--logs")
		{
			cout << "logs" << endl;
			addLog(fileName, "Added");
		}
		else if (command == "--print")
		{
			cout << "print logs" << endl;
			printLog();
		}
		else
			cout << "Unknown option";
	}
	else
	{
		cout << "Give more parameters" << endl;
	}
	return 0;
}