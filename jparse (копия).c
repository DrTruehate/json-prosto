#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
#include <string.h>
#include "jparse.h"


json_tok_t *prevTail, *nextTail;

/*
 *  Init Parse tree
 */
void TreeInit(void *tree)
{
  nextTail = tree;

  // root obj
  nextTail->type = JSON_OBJECT;
  nextTail->key[0] = '\0';
  nextTail->value = NULL;
  nextTail->size = sizeof(json_tok_t);
  nextTail->prev = NULL;
  nextTail->next = NULL;
  nextTail->owner = NULL;

  prevTail = nextTail;
}


/*
 *
 */
void Add2tree(json_type_t type, const void* owner,
              const char* key, const char* value)
{
  nextTail = prevTail->next = (void*)prevTail + prevTail->size;
  nextTail->type = type;

  if(key == NULL) nextTail->key[0] = '\0';
  else strcpy(nextTail->key, key);
  int strsLen = strlen(nextTail->key);
  nextTail->value = nextTail->key + strsLen;

  if(value == NULL) nextTail->value = NULL;
  else if(*value != '\0'){
    nextTail->value++;
    strcpy(nextTail->value, value);
    strsLen += strlen(nextTail->value) +1;
  }

  nextTail->size = sizeof(json_tok_t) + strsLen;
  nextTail->prev = prevTail;
  nextTail->next = NULL;
  nextTail->owner = (void*)owner;

  prevTail = nextTail;
}


/*
 *
 */
static void tab(int num)
{
  for(int i=0; i<num; i++) printf(JSON_TAB);
}


#define OWNER(ptr)  ( (json_tok_t*)(ptr) )->owner

#define BRACKET_CLOSE(ptr, shift) \
  tab( --(shift) ); \
  if(ptr->type == JSON_OBJECT) putchar('}'); \
  else putchar(']');


/*
 *
 */
static void brackets_close(json_tok_t *tok, int *cnt)
{
  json_tok_t *prev;

  if(tok->next == NULL){// last iteem of the tree
    putchar('\n');
    for(prev = tok->owner; prev != NULL; prev = prev->owner){
      BRACKET_CLOSE(prev, *cnt);
      putchar('\n');
    }
    return;
  }

  if( tok->owner == OWNER(tok->next) ){ puts(","); return; }

  // last iteem of current obj or array
  putchar('\n');
  for(prev = tok->owner; ; prev = prev->owner){
    BRACKET_CLOSE(prev, *cnt);
    if( prev->owner == OWNER(tok->next) ){ puts(","); return; }
    putchar('\n');
  }
}


#define BRACKET_OPEN(str) \
  if(tok->key[0] != '\0') printf("%s: ", tok->key); \
  puts(str); cnt++

/*
 *
 */
void PrettyPrint_JSON(void* tree)
{
  json_tok_t *tok;
  int cnt=0;

  for(tok=tree; /* see at the bottom */; tok = tok->next){
    tab(cnt);

    switch(tok->type){
      case JSON_OBJECT: BRACKET_OPEN("{"); break;
      case JSON_ARRAY:  BRACKET_OPEN("["); break;
      case JSON_MEMBER:
        printf("%s: %s", tok->key, tok->value);
        brackets_close(tok, &cnt);
        break;
      case JSON_ELEMENT:
        printf("%s", tok->value);
        brackets_close(tok, &cnt);
        break;
      default:
        printf("Error: \"unknown json_type_t\" %d\n", tok->type);
        return;
    } // end of switch()
    if(tok->next == NULL) break;
  } // end of for()
}
/* EOF */
