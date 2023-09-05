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


typedef struct jtree_node {
  void
    *owner, // owner of item (object or array)
    *next;  // next node
  json_type_t type; // type of node
  int datasz;       // size of data field
  char data[0];     // beginning of data field
} jtree_node_t;
