#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "flv_tag_script_string.h"

/**
 * flv tag data string
 */
typedef struct _FLVTagScriptString
{
    /**
     * 字符串长度
     */
    int length;

    /**
     * 保存的值
     */
    char *data;
} FLVTagScriptString;

/**
 * 创建string类型的tag
 */
FLVTagScriptString *flv_tag_script_string_new()
{
    FLVTagScriptString *script_string = (FLVTagScriptString *)malloc(sizeof(FLVTagScriptString));
    memset(script_string, 0, sizeof(FLVTagScriptString));
    return script_string;
}

/**
 * 释放string的tag
 */
void flv_tag_script_string_free(FLVTagScriptString *script_string)
{
    if (script_string != NULL)
    {
        free(script_string);
    }
}

/**
 * 释放string的tag及其数据
 */
void flv_tag_script_string_and_data_free(FLVTagScriptString *script_string)
{
    if (script_string != NULL)
    {
        if (script_string->data != NULL)
        {
            free(script_string->data);
        }
        free(script_string);
    }
}

/**
 * 获取字符串长度
 */
int flv_tag_script_string_length(FLVTagScriptString *script_string)
{
    if (script_string == NULL)
    {
        return -1;
    }
    return script_string->length;
}

/**
 * 设置字符串长度
 */
void flv_tag_script_set_string_length(FLVTagScriptString *script_string, int length)
{
    if (script_string == NULL)
    {
        return;
    }
    script_string->length = length;
}

/**
 * 获取字符串
 */
char *flv_tag_script_string_get_data(FLVTagScriptString *script_string)
{
    if (script_string == NULL)
    {
        return NULL;
    }
    return script_string->data;
}

/**
 * 设置字符串
 */
void flv_tag_script_string_set_data(FLVTagScriptString *script_string, char *data)
{
    if (script_string == NULL || data == NULL || script_string->length <= 0)
    {
        return;
    }
    char *value = NULL;
    int length = script_string->length;
    bool has_zero = data[length - 1] != '\0';
    if (has_zero)
    {
        length++;
    }
    value = (char *)malloc(sizeof(char) * length);
    strncpy(value, data, length - (has_zero ? 0 : 1));
    value[length - 1] = '\0';
    script_string->data = value;
}