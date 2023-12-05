/*
*/
#pragma once  // replacement to "#include guard"

#define JSON_TAB  "  "

typedef enum {
  JSON_UNDEFINED,
  JSON_OBJECT,  // { member, member, ... }
  JSON_MEMBER,  // "string":value
  JSON_ARRAY,   // [ value, value, ... ]
  JSON_ELEMENT, // value
  JSON_STRING,  //   simple
  JSON_NUMBER,  //   types
  JSON_BOOLEAN  //   of value
} json_type_t;


enum json_err {
  JSON_ERROR_NOMEM = -1,// Not enough tokens were provided
  JSON_ERROR_INVAL = -2,// Invalid character inside JSON string
  // The string is not a full JSON packet, more bytes expected
  JSON_ERROR_PART = -3
};


typedef struct {
  json_type_t
    type;  // type of token
  int
    size;  // size of token
  void
    *prev, // previous token
    *next, // next token
    *owner;// owner of item
  char
    *value,// pointer to value string
    key[1];// beginning of key string + value string
} json_tok_t;


extern json_tok_t *prevTail, *nextTail;

void TreeInit(void* tree);
void Add2tree(json_type_t type, const void* owner,
              const char* key, const char* value);
void PrettyPrint_JSON(void* tree);

