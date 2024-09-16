#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <regex.h>
#include "misc.h"
#include "jlists.h"

#define SET_REC(Obj, Owner, Type) \
  Obj->owner = Owner;\
  Obj->type = Type;\
  Obj->datasz = 0

int JAddData(json_record_t *const rec,
             void *const data, const size_t size, const size_t maxsz)
{
  assert(rec != NULL);
  assert(data != NULL);

  size_t newsize = rec->datasz + size;
  if(newsize > maxsz) return -1;

  memcpy(&rec->data[rec->datasz], data, size);
  rec->datasz = newsize;

  return 0;
}


int JAddRecord(json_list_t *lst, json_record_t *rec)
{
  assert(lst != NULL);
  assert(rec != NULL);

  size_t recSize = rec->datasz + sizeof(json_record_t);
  if(lst->listsz + recSize > lst->maxsz) return -1;

  memcpy(lst->tail, rec, recSize);
  lst->tail = (void *)lst->tail + recSize;
  lst->listsz += recSize;

  return 0;
}


int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "C"); // for correct use strtod()

  char lbuf[BUFSIZ], rbuf[256+sizeof(json_record_t)];
  json_list_t test;
  json_record_t *rec = (json_record_t *)rbuf;

  JListInit(&test, lbuf, BUFSIZ);

  SET_REC(rec, 0, JSON_KEYSTR);
  JAddData(rec, OBJ_SIZEOF("\"name\""), 256);
  JAddData(rec, OBJ_SIZEOF("\"Google\""), 256);
  JAddRecord(&test, rec);

  //printf("%s,%s size = %lu\n", test.tail->data, &test.tail->data[7], test.tail->datasz);

//  json_list_head_t lhead;
//  int depth[10];
//  json_list_t *jlist = (json_list_t *)listbuf;
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

  JListInit(jlist, BUFSIZ);
  depth[0] = jlist->tail;
  printf("jlist = %p\n"
         "jlist->listsz = %d\n"
         "jlist->bufsz = %d\n"
         "jlist->tail = %p\n",
         listbuf, jlist->listsz, jlist->bufsz, jlist->tail);
  JNodePrint(jlist->tail);
*/

//  JListInit(&lhead, (json_list_node_t *)lbuf, BUFSIZ);
//  depth[0] = lhead.tail;
//  JNodePrint(depth[0]);

//  int size = KeyStrFill(jdata, "name", "Google", 256);
//  printf("size = %d, \"%s\": \"%s\"\n", size, jdata, &jdata[5]);
//
//  size = KeyNumFill(jdata, "number", "4.576", 256);
//  printf("size = %d, \"%s\": %.2f\n", size, jdata, *(double *)&jdata[7]);

  /*int size = 0,
  newsize = JListInit(lbuf, BUFSIZ);//13
  JNodePrint(lbuf);
  printf("newsize = %d\n", newsize);
  size = newsize;

  node->owner = 0;
  node->type = JSON_STRING;
  node->datasz =
    StrFill(node->data, "TEST MESSAGE", 256) + sizeof(json_record_t);
  newsize = AddJNode(lbuf, node, size, BUFSIZ);
  JNodePrint(lbuf+size);
  printf("newsize = %d\n", newsize);
  size = newsize;

  newsize = JListEnd(lbuf, size, BUFSIZ);//12
  JNodePrint(lbuf+size);
  printf("newsize = %d\n", newsize);
  size = newsize;*/

  return EXIT_SUCCESS;
}
