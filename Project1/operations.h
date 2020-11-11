#pragma once
#include <string>
#include <fstream>

/* Blob storage */
#include <was/storage_account.h>
#include <was/blob.h>
#include <cpprest/filestream.h>  
#include <cpprest/containerstream.h> 

/* Table storage */
#include <was/storage_account.h>
#include <was/table.h>

/* Json */
#include <json/value.h>
#include <json/json.h>

using std::string;
using std::cout;
using std::wcout;
using std::exception;
using std::endl;

/* Functions */
void addLog(string fileName, const char* operation, unsigned int sizeOfFile);
int addFileToContainer(string fileName = "file.txt");
int deleteFileFromContainer(string fileName, unsigned int* sizeOfFile);
void printLogs();
void checkUserAndPassword(string accountName, string accountKey);
