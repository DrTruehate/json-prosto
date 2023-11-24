/*
*/
#pragma once

#define TEMP_NODE_BUF  256


typedef enum {
  JSON_UNDEFINED,
  JSON_OBJECT,  // { member, member, ... }
  JSON_ARRAY,   // [ value, value, ... ]
  // Simple types of value
  JSON_STRING, JSON_NUMBER, JSON_TRUE, JSON_FALSE, JSON_NULL,
  // "key": value
  JSON_KEYSTR,  // "key": "string"
  JSON_KEYNUM,  // "key": number (type of number similar with double type)
  JSON_KEYTRUE, JSON_KEYFALSE, JSON_KEYNULL,
  JSON_END
} json_type_t;


typedef struct json_list_node_s {
  int   owner;  // owner of item (shift from the beginning of the list)
  json_type_t
        type;   // type of node
  int   datasz; // size of data field
  char  data[0];// beginning of data field
} json_list_node_t;


typedef struct json_list_head_s {
  int listsz;
  json_list_node_t
      *tail;
} json_list_head_t;


int JListInit(void *const buf, const int bufsz);
int JListEnd(void *const buf, const int listsz, const int bufsz);
int AddJNode(void *const buf, json_list_node_t *const node,
             const int listsz, const int bufsz);

int StrFill(char *data, const char *str, const int datasz);
int KeyStrFill(char *data, const char *key, const char *value, int datasz);
int KeyNumFill(char *data, const char *key, const char *value, int datasz);
void JNodePrint(void *ptr);
