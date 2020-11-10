#include <iostream>

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
	enum command
	{
		CHECK_USER,
		ADD,
		DEL,
		LOG,
		UNKNOWN
	};

	if (argc > 2)
	{
		string command = argv[1];
		int choice = UNKNOWN;

		if (command == "--account_name")
			choice = CHECK_USER;
		else if (command == "--add")
			choice = ADD;
		else if (command == "--delete")
			choice = DEL;
		else if (command == "--logs")
			choice = LOG;
		else
			choice = UNKNOWN;

		switch (choice)
		{
		case ADD:
			break;
		case DEL:
			break;
		case LOG:
			break;
		default:
			cout << "Unknown option" << endl;
		}
	}
	else
	{
		cout << "Give more parameters" << endl;
	}
	
	return 0;
}