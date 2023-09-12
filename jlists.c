#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jlists.h"


/*
 *
 */
int JListInit(json_list_head_t *const head,
              json_list_node_t *const buf, const int bufsz)
{
  assert(head != NULL);
  assert(buf != NULL);
  size_t nodesz = sizeof(json_list_node_t) +1;
  assert(nodesz <= bufsz);
  if(nodesz > bufsz) return -1;

  head->listsz = nodesz;
  head->tail = buf;

  buf->next = buf->owner = buf;
  buf->datasz = 1;
  buf->data[0] = 0;

  return 0;
}


int KeyStrFill(char *data, const char *key, const char *value, int bufsz)
{
  int keysz = strnlen(key, bufsz) +1;
  int valsz = strnlen(value, bufsz) +1;
  if(keysz+valsz > bufsz) return -1;

  memcpy(data, key, keysz);
  data += keysz;
  memcpy(data, value, valsz);

  return keysz + valsz;
}


int KeyNumFill(char *data, const char *key, const char *value, int bufsz)
{
  int keysz = strnlen(key, bufsz) +1;
  if(keysz+sizeof(double) >bufsz) return -1;

  //setlocale(LC_NUMERIC, "C");
  memcpy(data, key, keysz);
  data += keysz;
  *(double *)data = strtod(value, NULL);
  //setlocale(LC_NUMERIC, "");

  return keysz + sizeof(double);
}


int JNodeDataFill(char *data, const char *key, const char *value,
                     const json_type_t type, int bufsz)
{
  switch(type) {
    case JSON_UNDEFINED ... JSON_NULL: break;
    case JSON_KEYSTR:
      return KeyStrFill(data, key, value, bufsz);
    case JSON_KEYNUM:
      return KeyNumFill(data, key, value, bufsz);
    case JSON_KEYTRUE ... JSON_END: break;
  }

  return -2;
}


/*
 *
 */
int AddJNode(json_list_head_t *const head,
             json_list_node_t *const node, const int bufsz)
{
  size_t nodesz = sizeof(json_list_node_t) + node->datasz;
  if(head->listsz + nodesz > bufsz) return -1;

  head->listsz += nodesz;
  head->tail->next = (void *)(head->tail+1) + head->tail->datasz;

  head->tail = head->tail->next;// Update tail
  head->tail->owner = node->owner;
  head->tail->next = head->tail;
  head->tail->datasz = node->datasz;
  memcpy(head->tail->data, node->data, node->datasz);

  return 0;
}


/*
 *
 */
void JNodePrint(json_list_node_t *ptr)
{
  printf("node \"%s\" ptr = %p\n"
         "owner   = %p\n" "next    = %p\n" "type    = %u\n" "datasz  = %d\n",
         ptr->data, ptr,
         ptr->owner, ptr->next, ptr->type, ptr->datasz);
}

