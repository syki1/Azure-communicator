#pragma once

/* Blob storage */
#include <was/storage_account.h>
#include <was/blob.h>
#include <cpprest/filestream.h>  
#include <cpprest/containerstream.h> 

/* Table storage */
#include <was/storage_account.h>
#include <was/table.h>
#include <string>

/* Functions */
void addLog(const char* fileName = "file.txt", const char* operation = "Unknown");
void addFileToContainer(const char* fileName = "file.txt");
void deleteFileFromContainer(const char* fileName = "file.txt");
void printLog();
