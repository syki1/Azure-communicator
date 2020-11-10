#include <iostream>
#include "operations.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	cout << "argc = " << argc << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv["<<i<<"] == " << argv[i] << endl;
	}

	if (argc >= 2)
	{
		string command = argv[1];
		string fileName = argv[2];

		if (command == "--account_name")
		{
			cout << "account";
		}
		else if (command == "--add")
		{
			cout << "--add if" << endl;
			addFileToContainer(fileName);
			addLog(fileName, "added");
		}
		else if (command == "--delete")
		{
			cout << "delete file";
			addLog(fileName, "deleted");
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