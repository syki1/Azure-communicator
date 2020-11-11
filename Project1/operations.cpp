#include "operations.h"

void addLog(string fileName, const char* operation, unsigned int sizeOfFile)
{
	try
	{
		// Define the connection-string with your values.
		const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

		// Retrieve the storage account from the connection string.
		azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

		// Create the table client.
		azure::storage::cloud_table_client table_client = storage_account.create_cloud_table_client();

		// Retrieve a reference to a table.
		azure::storage::cloud_table table = table_client.get_table_reference(U("operations"));

		// Create the table if it doesn't exist.
		table.create_if_not_exists();

		// Construct the query operation;
		azure::storage::table_query query;

		// Execute the query.
		azure::storage::table_query_iterator it = table.execute_query(query);

		// Print the fields for each customer.
		azure::storage::table_query_iterator end_of_results;

		// Find last element
		int indexLastElement = 1;
		for(; it != end_of_results; ++it)
		{
			indexLastElement++;
		}

		string indexElementString = std::to_string(indexLastElement);
		string sizeOfFileString = std::to_string(sizeOfFile);
		// Create a new log entity.
		azure::storage::table_entity log(utility::conversions::to_string_t(indexElementString), utility::conversions::to_string_t(indexElementString));

		azure::storage::table_entity::properties_type& properties = log.properties();
		properties.reserve(3);
		properties[U("File_name")] = azure::storage::entity_property(utility::conversions::to_string_t(fileName));
		properties[U("Operation")] = azure::storage::entity_property(utility::conversions::to_string_t(operation));
		properties[U("Size_of_file")] = azure::storage::entity_property(utility::conversions::to_string_t(sizeOfFileString));

		// Create the table operation that inserts the customer entity.
		azure::storage::table_operation insert_operation = azure::storage::table_operation::insert_entity(log);

		// Execute the insert operation.
		azure::storage::table_result insert_result = table.execute(insert_operation);
	}
	catch (const std::exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}

void printLogs()
{
	try
	{
		// Define the connection-string with your values.
		const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

		// Retrieve the storage account from the connection string.
		azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

		// Create the table client.
		azure::storage::cloud_table_client table_client = storage_account.create_cloud_table_client();

		// Create a cloud table object for the table.
		azure::storage::cloud_table table = table_client.get_table_reference(U("operations"));

		// Construct the query operation for all customer entities where PartitionKey="Smith".
		azure::storage::table_query query;

		// Execute the query.
		azure::storage::table_query_iterator it = table.execute_query(query);

		// Print the fields for each customer.
		azure::storage::table_query_iterator end_of_results;
		for (; it != end_of_results; ++it)
		{
			const azure::storage::table_entity::properties_type& properties = it->properties();

			/* std::wcout << U("PartitionKey: ") << it->partition_key() << U(", RowKey: ") << it->row_key()
				<< U(", Property1: ") << properties.at(U("File_name")).string_value()
				<< U(", Property2: ") << properties.at(U("Operation")).string_value() << endl; */

			wcout << "File " << properties.at(U("Operation")).string_value() << " " << properties.at(U("File_name")).string_value() << " size:" 
				<< properties.at(U("Size_of_file")).string_value() << "B" << endl;
		}
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}

int addFileToContainer(string fileName)
{
	try
	{
		cout << "Copying " << fileName << " to Azure service ... ";

		// Define the connection-string with your values.
		const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

		// Retrieve storage account from connection string.
		azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

		// Create the blob client.
		azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

		// Retrieve a reference to a previously created container.
		azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("files"));

		// Create the container if it doesn't already exist.
		container.create_if_not_exists();

		// Retrieve a reference to a blob.
		azure::storage::cloud_block_blob blob = container.get_block_blob_reference(utility::conversions::to_string_t(fileName));
		blob.upload_from_file(utility::conversions::to_string_t(fileName));

		cout << "OK " << endl;
		return 1;
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
		return -1;
	}
}

int deleteFileFromContainer(string fileName, unsigned int *sizeOfFile)
{
	try
	{
		cout << "Deleting " << fileName << " from Azure service ... ";

		// Define the connection-string with your values.
		const utility::string_t storage_connection_string(U("DefaultEndpointsProtocol=https;AccountName=filesstorage2;AccountKey=8+0/ZYgNQ/TCy16KG/DePV02hYwcru9DCTnetIDrO62aYhbIKf8DIwmtQa4qWg959DS2LQE3zlQV9OlupsoGQg=="));

		// Retrieve storage account from connection string.
		azure::storage::cloud_storage_account storage_account = azure::storage::cloud_storage_account::parse(storage_connection_string);

		// Create the blob client.
		azure::storage::cloud_blob_client blob_client = storage_account.create_cloud_blob_client();

		// Retrieve a reference to a previously created container.
		azure::storage::cloud_blob_container container = blob_client.get_container_reference(U("files"));

		// Retrieve reference to a blob.
		azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(utility::conversions::to_string_t(fileName));

		// Get size of deleted file (stream)
		concurrency::streams::container_buffer<std::vector<uint8_t>> buffer;
		concurrency::streams::ostream output_stream(buffer);
		blockBlob.download_to_stream(output_stream);
		*sizeOfFile = buffer.size();

		// Delete the blob.
		blockBlob.delete_blob();
		cout << "OK" << endl;

		return 1;
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
		return -1;
	}
}

void checkUserAndPassword(string accountName, string accountKey)
{
	Json::Value users;
	std::ifstream userFile("user_pass.json", std::ifstream::binary);

	if (userFile.fail()) {
		cout << "file isn't open" << endl;
		return;
	}

	userFile >> users;

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
		cout << "Pair of user and key exist" << endl;
	else
		cout << "Pair of user and key don't exist" << endl;
}