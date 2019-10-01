#include <stdlib.h>
#include <string.h>
#include "flv_tag_script_double.h"

/**
 * double script数据类型
 */
typedef struct _FLVTagScriptDouble
{
    /**
     * double数据
     */
    double data;
}FLVTagScriptDouble;

/**
 * 创建
 */
FLVTagScriptDouble *flv_tag_script_double_new()
{
    FLVTagScriptDouble *script_double = (FLVTagScriptDouble*)malloc(sizeof(FLVTagScriptDouble));
    memset(script_double, 0, sizeof(FLVTagScriptDouble));
    return script_double;
}

/**
 * 释放
 */
void flv_tag_script_double_free(FLVTagScriptDouble *script_double)
{
    if(script_double != NULL)
    {
        free(script_double);
    }
}

/**
 * 获取值
 */
double flv_tag_script_get_data(FLVTagScriptDouble *script_double)
{
    if(script_double == NULL)
    {
        return -1;
    }
    return script_double->data;
}

/**
 * 设置data值
 */
void flv_tag_script_set_data(FLVTagScriptDouble *script_double, void *data)
{
    if(script_double == NULL)
    {
        return;
    }
    memcpy(&(script_double->data), data, 8);
}