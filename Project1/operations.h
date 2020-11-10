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

void addLog(const char* fileName, const char* operation);
void addFileToContainer(const char* fileName);
void deleteFileFromContainer(const char* fileName);
void printLog();
