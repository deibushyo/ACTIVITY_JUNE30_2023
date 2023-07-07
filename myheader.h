#ifndef MYHEADER_H
#define MYHEADER_H

#define EMPTY 0
#define DELETED -1

#include <stdbool.h>

typedef struct {
	int elem;
	int link;
} Data;

typedef struct {
	Data *data;
	int avail;
	int count;
	int max;
} VSpace;

VSpace newVSpace(int max);
int allocSpace(VSpace *vs);
void freeSpace(VSpace *vs, int loc);
bool addElement(VSpace *vs);
bool removeElement(VSpace *vs);
void visualize(VSpace vs);
int hash(int val, int size);

#endif
