#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"
#include "object.h"

typedef enum
{
    KEY_NIL,
    KEY_BOOL,
    KEY_NUMBER,
    KEY_STRING
} KeyType;

typedef struct
{
    Key *key;
    Value value;
} Entry;

typedef struct
{
    KeyType type;
    union
    {
        ObjString *string;
        Value val
    } *key;
} Key;

typedef struct
{
    int count;
    int capacity;
    Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableGet(Table *table, Key *key, Value *value);
bool tableSet(Table *table, Key *key, Value value);
bool tableDelete(Table *table, Key *key);
void tableAddAll(Table *from, Table *to);
ObjString *tableFindString(Table *table, const char *chars, int length, uint32_t hash);

#endif