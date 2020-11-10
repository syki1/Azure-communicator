#include "operations.h"

using namespace std;

void addLog(const char* fileName, const char* operation)
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

		// Create a new customer entity.
		azure::storage::table_entity log(U("NULL"), U("2"));

		azure::storage::table_entity::properties_type& properties = log.properties();
		properties.reserve(2);
		//properties[U("File_name")] = azure::storage::entity_property(U("example2.txt"));
		properties[U("File_name")] = azure::storage::entity_property(utility::conversions::to_string_t(fileName));
		properties[U("Operation")] = azure::storage::entity_property(U("added"));

		// Create the table operation that inserts the customer entity.
		azure::storage::table_operation insert_operation = azure::storage::table_operation::insert_entity(log);

		// Execute the insert operation.
		azure::storage::table_result insert_result = table.execute(insert_operation);
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}

void printLog()
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

		//query.set_filter_string(azure::storage::table_query::generate_filter_condition(U("RowKey"), azure::storage::query_comparison_operator::equal, U("Smith")));

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

			wcout << "File " << properties.at(U("Operation")).string_value() << " " << properties.at(U("File_name")).string_value() << endl;
		}
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}

void addFileToContainer(const char* fileName)
{
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
		//azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("a.txt"));

		// Create or overwrite the "my-blob-2" and "my-blob-3" blobs with contents from text.
		// Retrieve a reference to a blob named "my-blob-2".
		azure::storage::cloud_block_blob blob = container.get_block_blob_reference(utility::conversions::to_string_t(fileName));
		blob.upload_from_file(U("file.txt"));

	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}

void deleteFileFromContainer(const char* fileName)
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

		// Retrieve reference to a blob named "my-blob-1".
		azure::storage::cloud_block_blob blockBlob = container.get_block_blob_reference(U("example.txt"));

		// Delete the blob.
		blockBlob.delete_blob();
		cout << "OK" << endl;
	}
	catch (const exception& e)
	{
		cout << "Error " << endl << e.what() << endl;
	}
}