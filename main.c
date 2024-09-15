#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "stdio.h"

int main(int argc, const char *argv[])
{
    Chunk chunk;
    initChunk(&chunk);
    writeConstant(&chunk, 1.2, 1);
    writeConstant(&chunk, 1.6, 2);
    writeConstant(&chunk, 1.23, 2);
    writeConstant(&chunk, 1.2444, 3);
    writeConstant(&chunk, 666, 4);
    writeConstant(&chunk, 134.3, 5);
    writeChunk(&chunk, OP_RETURN, 5);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);
    return 0;
}