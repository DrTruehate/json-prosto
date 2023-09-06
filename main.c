#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "misc.h"
#include "jlists.h"

int FormJNodeData(char *data, const char *key, char *value, json_type_t type, int bufsz)
{
  int keysz, valsz;

  switch(type) {
    case JSON_UNDEFINED ... JSON_NULL: break;
    case JSON_KEYSTR:
      keysz = snprintf(data, bufsz, "%s", key);
      assert(keysz >= 0);
      if(keysz < 0) return -1;
      keysz++;
      valsz = snprintf(&data[keysz], bufsz-keysz, "%s", value);
      assert(valsz >= 0);
      if(valsz < 0) return -1;
      valsz++;
      return keysz + valsz;
    case JSON_KEYNUM ... JSON_KEYNULL: break;
  }
  return -1;
}


int main(int argc, char** argv)
{
  char jlist[BUFSIZ], jdata[256];
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
  //printf("nodeSize = %d\n", nodeSize);
  //JNodePrint(jtail);

  // AddJNode()
/*  int strsz = 0; jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256, "name") +1;
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);
  jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256-strsz, "Google") +1;
  if(strsz > 256) ERROR("No space to allocate jdata[]");*/
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);
  int datasz = FormJNodeData(jdata, "name", "Google", JSON_KEYSTR, 256);
  if(datasz < 0) ERROR("No space to allocate jdata[]");

  nodeSize = AddJNodeData(&jtail, jdata, datasz, listsz);
  jtail->owner = depth[0];
  jtail->type = JSON_KEYSTR;
  //printf("nodeSize = %d\n", nodeSize);
  //JNodePrint(jtail);

  depth[1] = jtail;
  JNodePrint(depth[0]);
  JNodePrint(depth[1]);
  printf("key = \"%s\"\n" "value = \"%s\"\n",
         jtail->data, &jtail->data[strlen(jtail->data)+1]);

  return EXIT_SUCCESS;
}
