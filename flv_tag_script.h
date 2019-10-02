#ifndef FLV_TAG_SCRIPT_HEADER
#define FLV_TAG_SCRIPT_HEADER
#include "types.h"
/**
 * flv script tag 
 */
typedef struct _FLVTagScript FLVTagScript;

/**
 * sctipt tag data类型枚举
 */

typedef enum _FLVTagScriptDataType
{
    SCRIPT_TYPE_UNKNOW,
    SCRIPT_TYPE_NUMBER = 0,
    SCRIPT_TYPE_BOOLEAN = 1,
    SCRIPT_TYPE_STRING = 2,
    SCRIPT_TYPE_OBJECT = 3,
    SCRIPT_TYPE_MOVE_CLIP = 4,
    SCRIPT_TYPE_TYPE_NULL = 5,
    SCRIPT_TYPE_UNDEFINED = 6,
    SCRIPT_TYPE_REFERENCE = 7,
    SCRIPT_TYPE_ECMA_ARRAY = 8,
    SCRIPT_TYPE_OBJECT_AND_MAKER = 9,
    SCRIPT_TYPE_SCRIPT_ARRAY = 10,
    SCRIPT_TYPE_DATE = 11,
    SCRIPT_TYPE_LONG_STRING = 12
} FLVTagScriptDataType;

/**
 * script tag
 */
FLVTagScript *flv_tag_script_new();

/**
 * 释放script tag
 */
void flv_tag_script_free(FLVTagScript *script);

/**
 * 释放script tag和数据
 */
void flv_tag_script_and_data_free(FLVTagScript *script);

/**
 * 获取script类型
 */
FLVTagScriptDataType flv_tag_script_get_type(FLVTagScript *script);

/**
 * 设置script类型
 */
void flv_tag_script_set_type(FLVTagScript *script, int type);

/**
 * 获取数据
 */
void *flv_tag_script_get_data(FLVTagScript *script);

/**
 * 设置数据
 */
void flv_tag_script_set_data(FLVTagScript *script, void *data);
#endif // !FLV_TAG_SCRIPT_HEADER