// linked_list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

NODE *getNode(char *string);
void insertLine(char *string);
void edit(char *string, int lineNumber);
void deleteLine(int lineNumber);
void display();
void reset();

#endif // LINKED_LIST_H