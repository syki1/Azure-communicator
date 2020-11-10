#include "operations.h"

using namespace std;

void addLog()
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
		properties[U("File_name")] = azure::storage::entity_property(U("example2.txt"));

		properties[U("Operation")] = azure::storage::entity_property(U("Added"));

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