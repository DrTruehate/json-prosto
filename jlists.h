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


typedef struct {
  size_t  owner;  // owner of item (shift from the beginning of the list)
  json_type_t
          type;   // type of record
  size_t  datasz; // size of data field
  char    data[0];// beginning of data field
} json_record_t;


typedef struct {
  size_t  listsz, maxsz;
  json_record_t
          *tail;
} json_list_t;


void JListInit(json_list_t *const list, void *const buf, const size_t bufsz);
int JListEnd(void *const buf, const int listsz, const int bufsz);
int AddJNode(void *const buf, json_record_t *const node,
             const int listsz, const int bufsz);

int StrFill(char *data, const char *str, const int datasz);
int KeyStrFill(char *data, const char *key, const char *value, int datasz);
int KeyNumFill(char *data, const char *key, const char *value, int datasz);
void JNodePrint(void *ptr);
