#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jlists.h"


/*
 *
 */
int JNodeInit(jlist_node_t *const node, const size_t bufsz)
{
  assert(sizeof(jlist_node_t) <= bufsz);
  if(sizeof(jlist_node_t) > bufsz) return 0;

  node->owner = NULL;// root obj
  node->next = NULL;
  node->type = JSON_OBJECT;
  node->datasz = 1;
  node->data[0] = 0;
  return sizeof(jlist_node_t) +1;
}


/*
 *
 */
int AddJNodeData(jlist_node_t **tail,
                 const char *data, const int datasz, const size_t bufsz)
{
  int nodesz = sizeof(jlist_node_t) + datasz;
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
void JNodePrint(jlist_node_t *ptr)
{
  printf("nodePtr = %p\n"
         "owner   = %p\n" "next    = %p\n" "type    = %d\n" "datasz  = %d\n",
         ptr,
         ptr->owner, ptr->next, ptr->type, ptr->datasz);
}
