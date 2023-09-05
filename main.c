#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "misc.h"
#include "jtrees.h"


int JNodeInit(jtree_node_t *node, size_t bufsz)
{
  if(sizeof(jtree_node_t) > bufsz) return 0;

  node->owner = NULL;// root obj
  node->next = NULL;
  node->type = JSON_OBJECT;
  node->datasz = 0;

  return sizeof(jtree_node_t);
}


int AddJNode(jtree_node_t *tail, char *data, int datasz, size_t bufsz)
{
  int nodesz = sizeof(jtree_node_t) + datasz;
  if(nodesz > bufsz) return 0;

  tail->next = (void *)(tail+1) + tail->datasz;
  printf("tail = %p\n"
         "tail->next = %p\n", tail, tail->next);

  tail = tail->next;
  printf("new tail = %p\n", tail);
  tail->next = NULL;
  tail->datasz = datasz;
  memcpy( tail->data, data, datasz );
  printf("new tail->data = %s\n", tail->data);

  return nodesz;
}


void JNodePrint(jtree_node_t *ptr)
{
  printf("owner   = %p\n" "next    = %p\n" "type    = %d\n" "datasz  = %d\n",
         ptr->owner, ptr->next, ptr->type, ptr->datasz);
}


int main(int argc, char** argv)
{
  char jtree[BUFSIZ], jdata[256], *jptr;
  jtree_node_t *jtail;
  //void *depth[10];
  int treesz = BUFSIZ;

  // JTreeInit()
  jtail = (jtree_node_t *)jtree;
  int nodeSize = JNodeInit(jtail, treesz);
  if(nodeSize == 0) ERROR("No space to allocate jtree[]\n");
  treesz -= nodeSize;
  //depth[0] = &jtail; // root obj
  printf("jtail = %p\n", jtail);

  // AddJNode()
  int strsz = 0; jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256, "name") +1;
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);
  jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256-strsz, "Google") +1;
  if(strsz > 256) ERROR("No space to allocate jdata[]");
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);

  nodeSize = AddJNode(jtail, jdata, strsz, treesz);
  printf("nodeSize = %d\n", nodeSize);

  //depth[1] = &jtail;
  //JNodePrint(depth[0]);
  //JNodePrint(depth[1]);

  return EXIT_SUCCESS;
}
