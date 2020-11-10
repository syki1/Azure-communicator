#pragma once
#include <string>

/* Blob storage */
#include <was/storage_account.h>
#include <was/blob.h>
#include <cpprest/filestream.h>  
#include <cpprest/containerstream.h> 

/* Table storage */
#include <was/storage_account.h>
#include <was/table.h>

using std::string;
using std::cout;
using std::wcout;
using std::exception;
using std::endl;

/* Functions */
void addLog(string fileName, const char* operation);
void addFileToContainer(string fileName = "file.txt");
void deleteFileFromContainer(string fileName = "file.txt");
void printLog();
