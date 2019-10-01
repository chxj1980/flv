#include <stdlib.h>
#include "flv_tag_script_object.h"

/**
 * script object类型
 */
typedef struct _FLVTagScriptObject
{
    FLVTagScriptString *key;
    FLVTagScript *value;
}FLVTagScriptObject;

/**
 * 创建object
 */
FLVTagScriptObject *flv_tag_script_object_new()
{
    FLVTagScriptObject *script_object = (FLVTagScriptObject*)malloc(sizeof(FLVTagScriptObject));
    memset(script_object, 0, sizeof(FLVTagScriptObject));
    return script_object;
}

/**
 * 释放object
 */
void flv_tag_script_object_free(FLVTagScriptObject *script_object)
{
    if(script_object != NULL)
    {
        free(script_object);
    }
}

/**
 * 释放object 和数据
 */
void flv_tag_script_object_and_data_free(FLVTagScriptObject *script_object)
{
    if(script_object != NULL)
    {
        if(script_object->key != NULL)
        {
            flv_tag_script_string_and_data_free(script_object->key);
        }
        if(script_object->value != NULL)
        {
            flv_tag_script_and_data_free(script_object->value);
        }
        free(script_object);
    }
}

/**
 * 获取type
 */
FLVTagScriptDataType flv_tag_script_object_get_type(FLVTagScriptObject *script_object)
{
    return flv_tag_script_get_type(script_object->value);
}

/**
 * 设置type
 */
void flv_tag_script_object_set_type(FLVTagScriptObject *script_object, int type)
{
    flv_tag_script_set_type(script_object->value, type);
}

/**
 * 获取key
 */
FLVTagScriptString *flv_tag_script_object_get_key(FLVTagScriptObject *script_object)
{
    if(script_object == NULL)
    {
        return NULL;
    }
    return script_object->key;
}

/**
 * 设置key
 */
void flv_tag_script_object_set_key(FLVTagScriptObject *script_object, FLVTagScriptString *key)
{
    if(script_object == NULL)
    {
        return;
    }
    script_object->key = key;
}

/**
 * 获取value
 */
FLVTagScript *flv_tag_script_object_get_value(FLVTagScriptObject *script_object)
{
    if(script_object == NULL)
    {
        return NULL;
    }
    return script_object->value;
}

/**
 * 设置value
 */
void flv_tag_script_object_set_value(FLVTagScriptObject *script_object, FLVTagScript *value)
{
    if(script_object == NULL)
    {
        return;
    }
    script_object->value = value;
}