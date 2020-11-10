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

int main(int argc, char **argv)
{
	if (argc < 2)
		cout << "Give more parameters" << endl;

	int choice = 0;

	switch (choice)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
		default:
			cout << "Unknown option" << endl;
	}
		


	return 0;
}