#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
#include "rle.h"

typedef enum
{
    OP_CONSTANT_LONG,
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct
{
    int count;
    int capacity;
    uint8_t *code;
    ValueArray constants;
    LineEntries lineEntries;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
void writeConstant(Chunk *chunk, Value value, int line);
int getLine(Chunk *chunk, int index);
int addConstant(Chunk *chunk, Value value);
#endif