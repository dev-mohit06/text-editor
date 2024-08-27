// file_operations.h
#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "common.h"
#include <sys/stat.h>   // For mkdir
#include <sys/types.h>  // For mode_t

void generateRandomFileName();
void saveFile();

#endif // FILE_OPERATIONS_H