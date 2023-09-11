#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <regex.h>
#include "misc.h"
#include "jlists.h"


size_t KeyStrFill(char *data, const char *key, const char *value, size_t bufsz)
{
  size_t datasz = strnlen(key, bufsz) + strnlen(value, bufsz) +2;
  if(datasz > bufsz) return -1;

  bufsz = sprintf(data, "%s", key) +1;
  sprintf(&data[bufsz], "%s", value);

  return datasz;
}


size_t KeyNumFill(char *data, const char *key, const char *value, size_t bufsz)
{
  size_t datasz = strnlen(key, bufsz) + sizeof(double) +1;
  if(datasz > bufsz) return -1;

  bufsz = sprintf(data, "%s", key) +1;
  *(double *)(data+bufsz) = strtod("value", NULL);

  return datasz;
}


size_t JNodeDataFill(char *data, const char *key, const char *value,
                  const json_type_t type, int bufsz)
{
  switch(type) {
    case JSON_UNDEFINED ... JSON_NULL: break;
    case JSON_KEYSTR: return KeyStrFill(data, key, value, bufsz);
    case JSON_KEYNUM: return KeyNumFill;
    case JSON_KEYTRUE ... JSON_KEYNULL: break;
  }

  return -1;
}


int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");

  char listbuf[BUFSIZ]/*, jdata[256]*/;
  json_list_t *jlist = (json_list_t *)listbuf;
  json_list_node_t *depth[10];
  //int listsz = BUFSIZ;

  // JTreeInit()
//  jtail = (json_list_node_t *)jlist;
//  int nodeSize = JNodeInit(jtail, listsz);
//  if(nodeSize == 0) ERROR("No space to allocate jtree[]\n");
//  listsz -= nodeSize;
//  depth[0] = jtail; // root obj
//  //printf("depth[0] = %p\n", depth[0]);
  //printf("nodeSize = %d\n", nodeSize);
  //JNodePrint(jtail);

  // AddJNode()
/*  int strsz = 0; jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256, "name") +1;
  //printf("strsz = %d, jptr = %s\n", strsz, jptr);
  jptr = &jdata[strsz];
  strsz += snprintf(jptr, 256-strsz, "Google") +1;
  if(strsz > 256) ERROR("No space to allocate jdata[]");
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
*/
  JListInit(jlist, BUFSIZ);
  depth[0] = jlist->tail;
  printf("jlist = %p\n"
         "jlist->listsz = %d\n"
         "jlist->bufsz = %d\n"
         "jlist->tail = %p\n",
         listbuf, jlist->listsz, jlist->bufsz, jlist->tail);
  JNodePrint(jlist->tail);

  return EXIT_SUCCESS;
}
