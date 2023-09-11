/*
*/
#pragma once

typedef enum {
  JSON_UNDEFINED,
  JSON_OBJECT,  // { member, member, ... }
  JSON_ARRAY,   // [ value, value, ... ]
  // Simple types of value
  JSON_STRING, JSON_NUMBER, JSON_TRUE, JSON_FALSE, JSON_NULL,
  // "key" :value
  JSON_KEYSTR,  // "key" :"string"
  JSON_KEYNUM,  // "key" :number (type of number similar with double type)
  JSON_KEYTRUE, JSON_KEYFALSE, JSON_KEYNULL
} json_type_t;


typedef struct json_list_node_s {
  void
    *owner, // owner of item (object or array)
    *next;  // next node
  json_type_t type; // type of node
  int datasz;       // size of data field
  char data[0];     // beginning of data field
} json_list_node_t;


typedef struct json_list_s {
  int
    listsz,
    bufsz;
  void *tail;
  char list[0];
} json_list_t;


int JListInit(json_list_t *const buf, const size_t bufsz);
int AddJNodeData(json_list_node_t **tail,
                 const char *data, const int datasz, const size_t bufsz);
void JNodePrint(json_list_node_t *ptr);
