#include <stdio.h>
#include <stdlib.h>
#include "flv_tag_script.h"
#include "flv_tag_script_double.h"
#include "flv_tag_script_string.h"
#include "flv_tag_script_ecma.h"

/**
 * flv script tag 
 */
typedef struct _FLVTagScript
{
    /**
     * script data 的数据类型
     * 0-number
     * 1-boolean
     * 2-string
     * 3-object
     * 4-movie clip
     * 5-null
     * 6-undefined
     * 7-reference
     * 8-ECMA array
     * 9-object and maker
     * 10-script array
     * 11-date
     * 12-long string
     */
    byte type;

    /**
     * script data数据
     */
    void *data;
} FLVTagScript;

/**
 * script tag
 */
FLVTagScript *flv_tag_script_new()
{
    FLVTagScript *tag_script = (FLVTagScript *)malloc(sizeof(FLVTagScript));
    memset(tag_script, 0, sizeof(FLVTagScript));
    return tag_script;
}

/**
 * 释放script tag
 */
void flv_tag_script_free(FLVTagScript *script)
{
    if (script != NULL)
    {
        free(script);
    }
}

/**
 * 释放script tag
 */
void flv_tag_script_and_data_free(FLVTagScript *script)
{
    if (script != NULL)
    {
        if (script->data != NULL)
        {
            switch (flv_tag_script_get_type(script))
            {
            case SCRIPT_TYPE_NUMBER:
                flv_tag_script_double_free((FLVTagScriptDouble *)(script->data));
                break;
            case SCRIPT_TYPE_BOOLEAN:
                break;
            case SCRIPT_TYPE_STRING:
                flv_tag_script_string_and_data_free((FLVTagScriptString *)(script->data));
                break;
            case SCRIPT_TYPE_OBJECT:
                break;
            case SCRIPT_TYPE_MOVE_CLIP:
                break;
            case SCRIPT_TYPE_TYPE_NULL:
                break;
            case SCRIPT_TYPE_UNDEFINED:
                break;
            case SCRIPT_TYPE_REFERENCE:
                break;
            case SCRIPT_TYPE_ECMA_ARRAY:
                flv_tag_script_ecma_and_data_free((FLVTagScriptEcma *)(script->data));
                break;
            case SCRIPT_TYPE_OBJECT_AND_MAKER:
                break;
            case SCRIPT_TYPE_SCRIPT_ARRAY:
                break;
            case SCRIPT_TYPE_DATE:
                break;
            case SCRIPT_TYPE_LONG_STRING:
                break;
            default:
                break;
            }
        }
        free(script);
    }
}

/**
 * 获取script类型
 */
FLVTagScriptDataType flv_tag_script_get_type(FLVTagScript *script)
{
    if (script == NULL)
    {
        return SCRIPT_TYPE_UNKNOW;
    }
    switch (script->type)
    {
    case 0x00:
        return SCRIPT_TYPE_NUMBER;
    case 0x01:
        return SCRIPT_TYPE_BOOLEAN;
    case 0x02:
        return SCRIPT_TYPE_STRING;
    case 0x03:
        return SCRIPT_TYPE_OBJECT;
    case 0x04:
        return SCRIPT_TYPE_MOVE_CLIP;
    case 0x05:
        return SCRIPT_TYPE_TYPE_NULL;
    case 0x06:
        return SCRIPT_TYPE_UNDEFINED;
    case 0x07:
        return SCRIPT_TYPE_REFERENCE;
    case 0x08:
        return SCRIPT_TYPE_ECMA_ARRAY;
    case 0x09:
        return SCRIPT_TYPE_OBJECT_AND_MAKER;
    case 0x10:
        return SCRIPT_TYPE_SCRIPT_ARRAY;
    case 0x11:
        return SCRIPT_TYPE_DATE;
    case 0x12:
        return SCRIPT_TYPE_LONG_STRING;
    default:
        return SCRIPT_TYPE_UNKNOW;
    }
}

/**
 * 设置script类型
 */
void flv_tag_script_set_type(FLVTagScript *script, int type)
{
    if (script == NULL)
    {
        return;
    }
    script->type = type & 0xff;
}

/**
 * 获取数据
 */
void *flv_tag_script_get_data(FLVTagScript *script)
{
    if (script == NULL)
    {
        return NULL;
    }
    return script->data;
}

/**
 * 设置数据
 */
void flv_tag_script_set_data(FLVTagScript *script, void *data)
{
    if (script == NULL)
    {
        return;
    }
    script->data = data;
}