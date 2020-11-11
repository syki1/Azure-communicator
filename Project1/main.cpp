#include <iostream>
#include <fstream>
#include <json/value.h>
#include <json/json.h>
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
		fileName = "";

		if (argc > 2)
			fileName = argv[2];

		std::ifstream file(fileName, std::ios::binary | std::ios::ate);
		unsigned int sizeOfFile = file.tellg();
		if (command == "--add" && sizeOfFile > 2000000)  
			cout << "Too large file " << endl;

		if (command == "--account_name" && argc >= 5)
		{
			string accountName = argv[2];
			string accountKey = argv[4];
			cout << "accName = " << accountName << " accKey = " << accountKey << endl;
			
			Json::Value users;
			std::ifstream userFile("user_pass.json", std::ifstream::binary);
			userFile >> users;

			cout << users << endl; //This will print the entire json object
			cout << "users size = " << users.size();

			bool userAndKey = false;
			for (int i = 1; i < users.size() + 1; i++)
			{
				string objectName = ("User" + std::to_string(i)).c_str();
				if (accountName == users[objectName]["User"].asString() && accountKey == users[objectName]["Password"].asString())
				{
					userAndKey = true;
					break;
				}
			}
			if (userAndKey)
				cout << "User and key exist" << endl;
			else
				cout << "User and key don't exist" << endl;
		}
		else if (command == "--add")
		{
			if (sizeOfFile < 2000000)
			{
				cout << "--add if" << endl;
				addFileToContainer(fileName);
				addLog(fileName, "added", sizeOfFile);
			}
			else
				cout << "File too large" << endl;
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