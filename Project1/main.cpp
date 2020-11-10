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
	cout << "argc = " << argc;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv[i] == " << argv[i] << endl;
	}

	if (argc >= 2)
	{
		string user = "qazsed91@gmail.com";
		string password = "haslo123";

		string command = argv[1];
		int choice = UNKNOWN;

		if (command == "--account_name")
			choice = CHECK_USER;
		else if (command == "--add")
		{
			cout << "--add if" << endl;
			//string fileName = argv[2];
			//cout << "Copying " << fileName << " to Azure service ";

			// Define the connection-string with your values.
			const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=qazsed91@gmail.com;AccountKey=haslo123"));

			// Retrieve storage account from connection string.
			azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

			// Create the blob client.
			azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

			// Retrieve a reference to a previously created container.
			azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("filesstorage2"));

			// Retrieve reference to a blob named "my-blob-1".
			azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("files"));

			// Create or overwrite the "my-blob-1" blob with contents from a local file.
			concurrency::streams::istream input_stream = concurrency::streams::file_stream<uint8_t>::open_istream(U("file.txt")).get();
			blockBlob.upload_from_stream(input_stream);
			input_stream.close().wait();

			// Create or overwrite the "my-blob-2" and "my-blob-3" blobs with contents from text.
			// Retrieve a reference to a blob named "my-blob-2".
			azure::storage::cloud_block_blob blob2 = container.get_block_blob_reference(U("my-blob-2"));
			blob2.upload_from_file(U("file.txt"));

			/* // Retrieve a reference to a blob named "my-blob-3".
			azure::storage::cloud_block_blob blob3 = container.get_block_blob_reference(U("my-directory/my-sub-directory/my-blob-3"));
			blob3.upload_text(U("other text")); */

		}
		else if (command == "--delete")
		{
			cout << "Deleting file.txt from Azure service ";
			// Define the connection-string with your values.
			const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=qazsed91@gmail.com;AccountKey=haslo123"));

			// Retrieve storage account from connection string.
			azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

			// Create the blob client.
			azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

			// Retrieve a reference to a previously created container.
			azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("filesstorage2"));
			
			// Retrieve reference to a blob named "my-blob-1".
			azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("files"));

			// Delete the blob.
			blockBlob.delete_blob();
		}
			
		else if (command == "--logs")
		{
			cout << "logs" << endl;
		}
		else
		{
			cout << "Unknown option";
		}
			
	}
	else
	{
		cout << "Give more parameters" << endl;
	}
	
	return 0;
}