#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jlists.h"


/*
 *
 */
static void RootNodeInit(json_list_node_t *const node)
{
  node->owner = node->next = node;// root obj
  node->type = JSON_OBJECT;
  node->datasz = 1;
  node->data[0] = 0;
}


/*
 *
 */
int JListInit(json_list_t *const buf, const size_t bufsz)
{
  int listsz = sizeof(json_list_t) + sizeof(json_list_node_t) +1;
  if(listsz > bufsz) return listsz;

  buf->listsz = listsz;
  buf->bufsz = bufsz;
  buf->tail = (json_list_node_t *)&buf->list[0];// root node
  RootNodeInit(buf->tail);

  return listsz;
}


/*
 *
 */
int AddJNodeData(json_list_node_t **tail,
                 const char *data, const int datasz, const size_t bufsz)
{
  int nodesz = sizeof(json_list_node_t) + datasz;
  assert(nodesz <= bufsz);
  if(nodesz > bufsz) return 0;

  (*tail)->next = (void *)(*tail+1) + (*tail)->datasz;

  *tail = (*tail)->next;// Update tail
  (*tail)->next = NULL;
  (*tail)->datasz = datasz;
  memcpy( (*tail)->data, data, datasz );

  return nodesz;
}


/*
 *
 */
void JNodePrint(json_list_node_t *ptr)
{
  printf("node \"%s\" ptr = %p\n"
         "owner   = %p\n" "next    = %p\n" "type    = %d\n" "datasz  = %d\n",
         ptr->data, ptr,
         ptr->owner, ptr->next, ptr->type, ptr->datasz);
}
