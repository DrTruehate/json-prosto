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
  JSON_KEYNUM,  // "key" :number
  JSON_KEYTRUE, JSON_KEYFALSE, JSON_KEYNULL
} json_type_t;


typedef struct {
  void
    *owner, // owner of item (object or array)
    *next;  // next node
  json_type_t type; // type of node
  int datasz;       // size of data field
  char data[0];     // beginning of data field
} jlist_node_t;


typedef struct {
  int listsz;
  jlist_node_t *tail;
  char nodes[0];
} jlist_t;

int JNodeInit(jlist_node_t *const node, const size_t bufsz);
int AddJNodeData(jlist_node_t **tail,
                 const char *data, const int datasz, const size_t bufsz);
void JNodePrint(jlist_node_t *ptr);
