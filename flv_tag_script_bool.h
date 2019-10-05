#ifndef FLV_TAG_SCRIPT_BOOL_HEADER
#define FLV_TAG_SCRIPT_BOOL_HEADER
#include <stdbool.h>

typedef struct _FLVTagScriptBool FLVTagScriptBool;

FLVTagScriptBool *flv_tag_script_bool_new();

void flv_tag_script_bool_free(FLVTagScriptBool *script_bool);

bool flv_tag_script_bool_get_data(FLVTagScriptBool *script_bool);

void flv_tag_script_bool_set_data(FLVTagScriptBool *script_bool, bool data);

#endif // !FLV_TAG_SCRIPT_BOOL_HEADER