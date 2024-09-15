#ifndef clox_rle_h
#define clox_rle_h

#include "common.h"
#include "memory.h"

typedef struct
{
    int line;
    int count;
} LineEntry;

typedef struct
{
    int lineCount;
    int capacity;
    LineEntry *lines;
} LineEntries;

void initLineEntries(LineEntries *lineEntries);
void writeLineEntry(LineEntries *lineEntries, int line);
void freeLineEntries(LineEntries *lineEntries);

#endif
