#ifndef FLV_TAG_SCRIPT_OBJECT_HEADER
#define FLV_TAG_SCRIPT_OBJECT_HEADER
#include "flv_tag_script_string.h"
#include "flv_tag_script.h"

/**
 * script object类型
 */
typedef struct _FLVTagScriptObject FLVTagScriptObject;

/**
 * 创建object
 */
FLVTagScriptObject *flv_tag_script_object_new();

/**
 * 释放object
 */
void flv_tag_script_object_free(FLVTagScriptObject *script_object);

/**
 * 释放object 和数据
 */
void flv_tag_script_object_and_data_free(FLVTagScriptObject *script_object);

/**
 * 获取type
 */
FLVTagScriptDataType flv_tag_script_object_get_type(FLVTagScriptObject *script_object);

/**
 * 设置type
 */
void flv_tag_script_object_set_type(FLVTagScriptObject *script_object, int type);

/**
 * 获取key
 */
FLVTagScriptString *flv_tag_script_object_get_key(FLVTagScriptObject *script_object);

/**
 * 设置key
 */
void flv_tag_script_object_set_key(FLVTagScriptObject *script_object, FLVTagScriptString *key);

/**
 * 获取value
 */
FLVTagScript *flv_tag_script_object_get_value(FLVTagScriptObject *script_object);

/**
 * 设置value
 */
void flv_tag_script_object_set_value(FLVTagScriptObject *script_object, FLVTagScript *value);
#endif // !FLV_TAG_SCRIPT_OBJECT_HEADER