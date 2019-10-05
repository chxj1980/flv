#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flv_tag_script_bool.h"

typedef struct _FLVTagScriptBool
{
  bool data;
} FLVTagScriptBool;

FLVTagScriptBool *flv_tag_script_bool_new()
{
  FLVTagScriptBool *script_bool = (FLVTagScriptBool *)malloc(sizeof(FLVTagScriptBool));
  memset(script_bool, 0, sizeof(FLVTagScriptBool));
  return script_bool;
}

void flv_tag_script_bool_free(FLVTagScriptBool *script_bool)
{
  if (script_bool != NULL)
  {
    free(script_bool);
  }
}

bool flv_tag_script_bool_get_data(FLVTagScriptBool *script_bool)
{
  if (script_bool == NULL)
  {
    return NULL;
  }
  return script_bool->data;
}

void flv_tag_script_bool_set_data(FLVTagScriptBool *script_bool, bool data)
{
  if (script_bool == NULL)
  {
    return;
  }
  script_bool->data = data;
}