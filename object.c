#include <stdio.h>
#include <string.h>

#include "object.h"
#include "memory.h"
#include "table.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type *)allocateObject(sizeof(type), objectType)

uint32_t hashKey(Key *key)
{
    switch (key->type)
    {
    case KEY_BOOL:
    {
        return AS_BOOL(key->key->val) ? hashNumber(1) : hashNumber(0);
    }
    case KEY_NIL:
    {
        return hashNumber(2);
    }
    case KEY_NUMBER:
    {
        return hashNumber(AS_NUMBER(key->key->val));
    }
    case KEY_STRING:
    {
        return hashString(key->key->string->chars, key->key->string->length);
    }
    }
}

static Obj *allocateObject(size_t size, ObjType type)
{
    Obj *object = (Obj *)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

static ObjString *allocateString(char *chars, int length, uint32_t hash)
{
    ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    string->hash = hash;
    tableSet(&vm.strings, string, NIL_VAL);
    return string;
}

static uint32_t hashString(const char *key, int length)
{
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++)
    {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

static uint32_t hashNumber(double number)
{
    uint64_t bits;

    memcpy(&bits, &number, sizeof(number));
    uint32_t hash = 2166136261u;

    uint32_t lo = (uint32_t)(bits & 0xFFFFFFFF);
    uint32_t hi = (uint32_t)((bits >> 32) & 0xFFFFFFFF);
    hash ^= lo;
    hash *= 16777619;

    hash ^= hi;
    hash *= 16777619;

    return hash;
}

ObjString *takeString(char *chars, int length)
{
    uint32_t hash = hashString(chars, length);
    return allocateString(chars, length, hash);
}

ObjString *copyString(const char *chars, int length)
{
    uint32_t hash = hashString(chars, length);
    ObjString *interned = tableFindString(&vm.strings, chars, length, hash);

    if (interned != NULL)
    {
        FREE_ARRAY(char, chars, length + 1);
        return interned;
    }

    char *heapChars = ALLOCATE(char, length + 1);
    memcpy(heapChars, chars, length);
    heapChars[length] = '\0';
    return allocateString(heapChars, length, hash);
}

void printObject(Value value)
{
    switch (OBJ_TYPE(value))
    {
    case OBJ_STRING:
    {
        printf("%s", AS_CSTRING(value));
        break;
    }
    }
}
