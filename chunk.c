#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants);
    initLineEntries(&chunk->lineEntries);
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    freeValueArray(&chunk->constants);
    freeLineEntries(&chunk->lineEntries);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    writeLineEntry(&chunk->lineEntries, line);
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void writeConstant(Chunk *chunk, Value value, int line)
{
    int operand = addConstant(chunk, value);
    if (operand >= 1 << 8)
    {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, operand & 0xFF, line);
        writeChunk(chunk, operand >> 8 & 0xFF, line);
        writeChunk(chunk, operand >> 16 & 0xFF, line);
        return;
    }
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, operand, line);
}

int getLine(Chunk *chunk, int index)
{
    int totalSum = 0;
    for (int i = 0; i < chunk->lineEntries.lineCount; i++)
    {
        totalSum += chunk->lineEntries.lines[i].count;
        if (totalSum >= index)
        {
            return chunk->lineEntries.lines[i].line;
        }
    }
    return 0;
}

int addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
