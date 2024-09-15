#include "rle.h"
#include "stdio.h"

void initLineEntries(LineEntries *lineEntries)
{
    lineEntries->lineCount = 0;
    lineEntries->capacity = 0;
    lineEntries->lines = NULL;
}

void writeLineEntry(LineEntries *lineEntries, int line)
{

    if (lineEntries->lineCount > 0 && lineEntries->lines[lineEntries->lineCount - 1].line == line)
    {
        lineEntries->lines[lineEntries->lineCount - 1].count++;
    }
    else
    {
        if (lineEntries->capacity < lineEntries->lineCount + 1)
        {
            int oldCapacity = lineEntries->capacity;
            lineEntries->capacity = GROW_CAPACITY(oldCapacity);
            lineEntries->lines = GROW_ARRAY(LineEntry, lineEntries->lines, oldCapacity, lineEntries->capacity);
        }
        lineEntries->lines[lineEntries->lineCount].line = line;
        lineEntries->lines[lineEntries->lineCount].count = 1;
        lineEntries->lineCount++;
    }
}

void freeLineEntries(LineEntries *lineEntries)
{
    FREE_ARRAY(LineEntries, lineEntries->lines, lineEntries->capacity);
    initLineEntries(lineEntries);
}
