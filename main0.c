#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <sys/stat.h>
#include <string.h>
#include "misc.h"
#include "jparse.h"

#define BUFSIZE 1024*8

#define ISSPACE(ch) \
  (strchr( " \r\n\t", (ch) ) != NULL)


#define ROOT \
  bzero(tokbuf, BUFSIZE); \
  TreeInit(tokbuf); \
  owner[cnt=0] = nextTail

#define OBJECT(name) \
  Add2tree(JSON_OBJECT, owner[cnt++], #name, NULL); \
  owner[cnt] = nextTail

#define ARRAY(name) \
  Add2tree(JSON_ARRAY, owner[cnt++], #name, NULL); \
  owner[cnt] = nextTail

#define MEMBER(key, value) \
  Add2tree(JSON_MEMBER, owner[cnt], #key, #value)

#define ELEMENT(value) \
  Add2tree(JSON_ELEMENT, owner[cnt], NULL, #value)

#define END cnt--

int main(int argc, char** argv)
{
  char tokbuf[BUFSIZE];
  void* owner[10];
  int cnt;

  //#include "jsons/test.inc"
  //#include "jsons/valid-0001.inc"
  #include "jsons/valid-0000.inc"

  if(cnt != -1) ERROR("Wrong json_file.inc\n");
  PrettyPrint_JSON(tokbuf);

  return EXIT_SUCCESS;
}
