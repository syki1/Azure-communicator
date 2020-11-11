#include <iostream>
#include "operations.h"

using std::cout;
using std::endl;

int main(int argc, char** argv)
{
	if (argc >= 2)
	{
		string command = argv[1];
		string fileName = "";
		unsigned sizeOfFile = 0;

		if (argc > 2)
			fileName = argv[2];

		if (command == "--account_name" && argc >= 5)
		{
			string accountName = argv[2];
			string accountKey = argv[4];
			checkUserAndPassword(accountName, accountKey);
		}
		else if (command == "--add")
		{
			std::ifstream file(fileName, std::ios::binary | std::ios::ate);
			sizeOfFile = file.tellg();

			if (file.fail())
			{
				cout << "File isn't open" << endl;
				return -1;
			}
			
			if (sizeOfFile < 2000000)
			{
				if(addFileToContainer(fileName) == 1);
					addLog(fileName, "added", sizeOfFile);
			}
			else
				cout << "File too large" << endl;
		}
		else if (command == "--delete")
		{
			unsigned int sizeOfDeletedFile = 0;
			if(deleteFileFromContainer(fileName, &sizeOfDeletedFile) == 1);
				addLog(fileName, "deleted", sizeOfDeletedFile);
		}
		else if (command == "--logs")
		{
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