#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jlists.h"


/*
 *
 *
 */
int JListInit(void *const buf, const int bufsz)
{
  assert(buf != NULL);
  int newsize = sizeof(json_list_node_t) +1;
  assert(newsize <= bufsz);
  if(newsize > bufsz) return -1;

  json_list_node_t *tail = buf;
  tail->owner = 0;          // root obj
  tail->type = JSON_OBJECT; //
  tail->datasz = 1;         //
  tail->data[0] = '\0';     //

  return newsize;
}


int JListEnd(void *const buf, const int listsz, const int bufsz)
{
  assert(buf != NULL);
  int newsize = listsz + sizeof(json_list_node_t);
  assert(newsize <= bufsz);
  if(newsize > bufsz) return -1;

  json_list_node_t *tail = buf + listsz;
  tail->owner = 0;
  tail->type = JSON_END;
  tail->datasz = 0;

  return newsize;
}


int AddJNode(void *const buf, json_list_node_t *const node,
             const int listsz, const int bufsz)
{
  assert(buf != NULL);
  int nodesz = sizeof(json_list_node_t) + node->datasz;
  int newsize = listsz + nodesz;
  assert(newsize <= bufsz);
  if(newsize > bufsz) return -1;

  memcpy(buf + listsz, node, nodesz);

  return newsize;
}

int StrFill(char *data, const char *str, const int datasz)
{
  int strsz = strnlen(str, datasz) +1;
  if(strsz > datasz) return -1;

  memcpy(data, str, strsz);

  return strsz;
}


int KeyStrFill(char *data, const char *key, const char *value, int datasz)
{
  int keysz = strnlen(key, datasz) +1;
  int valsz = strnlen(value, datasz) +1;
  if(keysz+valsz > datasz) return -1;

  memcpy(data, key, keysz);
  data += keysz;
  memcpy(data, value, valsz);

  return keysz + valsz;
}


int KeyNumFill(char *data, const char *key, const char *value, int bufsz)
{
  int keysz = strnlen(key, bufsz) +1;
  if(keysz+sizeof(double) > bufsz) return -1;

  memcpy(data, key, keysz);
  data += keysz;
  *(double *)data = strtod(value, NULL);

  return keysz + sizeof(double);
}


int JNodeFill(json_list_node_t *node,
              const char *name, const char *value, int bufsz)
{
  assert(node != NULL);
  bufsz -= sizeof(json_list_node_t);
  int namesz = strnlen(name, bufsz) +1;
  int valsz = strnlen(value, bufsz) +1;

  switch(node->type) {
    case JSON_UNDEFINED: break;
    case JSON_OBJECT: case JSON_ARRAY: case JSON_STRING:
    case JSON_KEYTRUE: case JSON_KEYFALSE: case JSON_KEYNULL:
      if(namesz < 0) return -1;
      memcpy(node->data, name, namesz);
      node->datasz = namesz;
      return 0;
    case JSON_NUMBER:
      *(double *)node->data = strtod(value, NULL);
      node->datasz = sizeof(double);
      return 0;
//    case JSON_KEYSTR: return 0;
//    case JSON_KEYNUM: return 0;
    case JSON_TRUE: case JSON_FALSE: case JSON_NULL: case JSON_END:
      node->datasz = 0;
      return 0;
  }

  return -2;
}
/*
 *
 */
void JNodePrint(void *ptr)
{
  json_list_node_t *node = ptr;
  printf("node \"%s\" ptr = %p\n"
         "owner   = %d\n" "type    = %d\n" "datasz  = %d\n",
         node->data, ptr,
         node->owner, node->type, node->datasz);
}

