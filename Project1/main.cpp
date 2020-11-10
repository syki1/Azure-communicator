#include <iostream>
#include <string>

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
		string fileName = "File.txt";
		string command = argv[1];

		if (command == "--account_name")
		{
			cout << "account";
		}
		else if (command == "--add")
		{
			cout << "--add if" << endl;

			try
			{
				cout << "Copying " << fileName << " to Azure service ";

				// Define the connection-string with your values.
				const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

				// Retrieve storage account from connection string.
				azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

				// Create the blob client.
				azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

				// Retrieve a reference to a previously created container.
				azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("files"));

				// Retrieve reference to a blob named "my-blob-1".
				//azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("a.txt"));
				azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U(fileName));

				// Create or overwrite the "my-blob-2" and "my-blob-3" blobs with contents from text.
				// Retrieve a reference to a blob named "my-blob-2".
				azure::storage::cloud_block_blob blob = container.get_block_blob_reference(U("example.txt"));
				blob.upload_from_file(U("file.txt"));

			}
			catch (const exception& e)
			{
				cout << "Error " << endl << e.what() << endl;
			}

		}
		else if (command == "--delete")
		{
			try
			{
				cout << "Deleting " << fileName <<  " from Azure service ... ";

				// Define the connection-string with your values.
				const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

				// Retrieve storage account from connection string.
				azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

				// Create the blob client.
				azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

				// Retrieve a reference to a previously created container.
				azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("files"));

				// Retrieve reference to a blob named "my-blob-1".
				azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("example.txt"));

				// Delete the blob.
				blockBlob.delete_blob();
				cout << "OK" << endl;
			}
			catch(const exception& e)
			{
				cout << "Error " << endl << e.what() << endl;
			}
		}
		else if (command == "--logs")
		{


			cout << "logs" << endl;
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