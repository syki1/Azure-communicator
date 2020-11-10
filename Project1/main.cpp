#include <iostream>
#include <string>
#include "operations.h"

/* Blob storage */
#include <was/storage_account.h>
#include <was/blob.h>
#include <cpprest/filestream.h>  
#include <cpprest/containerstream.h> 

/* Table storage */
#include <was/storage_account.h>
#include <was/table.h>

using namespace std;

int main(int argc, char** argv)
{
	cout << "argc = " << argc;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv[i] == " << argv[i] << endl;
	}

	if (argc >= 2)
	{
		const char fileName[20] = "File.txt";
		//string fileName = argv[2];
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
			cout << "file";
			deleteFileFromContainer(fileName);
		}
		else if (command == "--logs")
		{
			addLog(fileName, "Added");

			cout << "logs" << endl;
		}
		else if (command == "--print")
		{
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