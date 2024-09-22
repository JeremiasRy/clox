#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"
typedef enum
{
    PREC_NONE,
    PREC_ASSIGNMENT,
    PREC_OR,
    PREC_AND,
    PREC_EQUALITY,
    PREC_COMPARISON,
    PREC_TERM,
    PREC_FACTOR,
    PREC_UNARY,
    PREC_CALL,
    PREC_PRIMARY
} Precedence;

bool compile(const char *source, Chunk *chunk);

const char *getPrecedenceName(Precedence precedence);

#endif