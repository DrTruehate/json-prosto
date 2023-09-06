#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "misc.h"
#include "jlists.h"

int JNodeInit(jlist_node_t *const node, const size_t bufsz)
{
  assert(sizeof(jlist_node_t) <= bufsz);
  if(sizeof(jlist_node_t) > bufsz) return 0;

  node->owner = NULL;// root obj
  node->next = NULL;
  node->type = JSON_OBJECT;
  node->datasz = 0;

  return sizeof(jlist_node_t);
}


int AddJNodeData(jlist_node_t **tail, const char *data, const int datasz, const size_t bufsz)
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


void JNodePrint(jlist_node_t *ptr)
{
  printf("nodePtr = %p\n"
         "owner   = %p\n" "next    = %p\n" "type    = %d\n" "datasz  = %d\n",
         ptr,
         ptr->owner, ptr->next, ptr->type, ptr->datasz);
}


int main(int argc, char** argv)
{
  char jlist[BUFSIZ], jdata[256], *jptr;
  jlist_node_t *jtail;
  void *depth[10];
  int listsz = BUFSIZ;

  // JTreeInit()
  jtail = (jlist_node_t *)jlist;
  int nodeSize = JNodeInit(jtail, listsz);
  if(nodeSize == 0) ERROR("No space to allocate jtree[]\n");
  listsz -= nodeSize;
  depth[0] = jtail; // root obj
  //printf("depth[0] = %p\n", depth[0]);
  printf("nodeSize = %d\n", nodeSize);
  //JNodePrint(jtail);

  // AddJNode()
  int strsz = 0; jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256, "name") +1;
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);
  jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256-strsz, "Google") +1;
  if(strsz > 256) ERROR("No space to allocate jdata[]");
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);

  nodeSize = AddJNodeData(&jtail, jdata, strsz, listsz);
  printf("nodeSize = %d\n", nodeSize);
  //JNodePrint(jtail);

  depth[1] = jtail;
  JNodePrint(depth[0]);
  JNodePrint(depth[1]);
  printf("jtail->data = %s\n", jtail->data);

  return EXIT_SUCCESS;
}
