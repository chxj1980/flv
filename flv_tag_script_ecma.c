#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flv_tag_script_ecma.h"

// 初始容量
#define ECMA_ARRAY_INIT 10
// 扩容倍数
#define ECMA_ARRAY_SCALE 2

/**
 * ecma script
 */
typedef struct _FLVTagScriptEcma
{
    /**
     * ecma array长度
     */
    int length;

    /**
     * 容量
     */
    int capacity;

    /**
     * object
     */
    FLVTagScriptObject **objects;
} FLVTagScriptEcma;

/**
 * 创建ecma
 */
FLVTagScriptEcma *flv_tag_script_ecma_new()
{
    FLVTagScriptEcma *script_ecma = (FLVTagScriptEcma *)malloc(sizeof(FLVTagScriptEcma));
    memset(script_ecma, 0, sizeof(FLVTagScriptEcma));
    return script_ecma;
}

/**
 * 释放ecma
 */
void flv_tag_script_ecma_free(FLVTagScriptEcma *script_ecma)
{
    if (script_ecma != NULL)
    {
        free(script_ecma);
    }
}

/**
 * 释放ecma和数据
 */
void flv_tag_script_ecma_and_data_free(FLVTagScriptEcma *script_ecma)
{
    if (script_ecma != NULL)
    {
        if (script_ecma->objects != NULL && script_ecma->length > 0)
        {
            for (int i = 0; i < script_ecma->length; ++i)
            {
                flv_tag_script_object_and_data_free(script_ecma->objects[i]);
            }
            free(script_ecma->objects);
        }
        free(script_ecma);
    }
}

/**
 * 获取长度
 */
int flv_tag_script_ecma_length(FLVTagScriptEcma *script_ecma)
{
    if (script_ecma == NULL)
    {
        return -1;
    }
    return script_ecma->length;
}

/**
 * 获取容量
 */
int flv_tag_script_ecma_capacity(FLVTagScriptEcma *script_ecma)
{
    if (script_ecma == NULL)
    {
        return -1;
    }
    return script_ecma->capacity;
}

/**
 * objects
 */
FLVTagScriptObject **flv_tag_script_ecma_get_objects(FLVTagScriptEcma *script_ecma)
{
    if (script_ecma == NULL || script_ecma->length <= 0)
    {
        return NULL;
    }
    FLVTagScriptObject **objects = (FLVTagScriptObject **)malloc(sizeof(FLVTagScriptObject *) * script_ecma->length);
    memset(objects, 0, sizeof(FLVTagScriptObject *));
    for (int i = 0; i < script_ecma->length; ++i)
    {
        objects[i] = script_ecma->objects[i];
    }
    return objects;
}

/**
 * get data
 */
FLVTagScriptObject *flv_tag_script_ecma_get_object(FLVTagScriptEcma *script_ecma, char *key)
{
    if (script_ecma == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < script_ecma->length; ++i)
    {
        FLVTagScriptObject *object = script_ecma->objects[i];
        if (!strcmp(key, flv_tag_script_string_get_data(flv_tag_script_object_get_key(object))))
        {
            return object;
        }
    }
    return NULL;
}

/**
 * find index
 */
int flv_tag_script_ecma_find(FLVTagScriptEcma *script_ecma, char *key)
{
    if (script_ecma == NULL)
    {
        return -1;
    }
    for (int i = 0; i < script_ecma->length; ++i)
    {
        FLVTagScriptObject *object = script_ecma->objects[i];
        if (!strcmp(key, flv_tag_script_string_get_data(flv_tag_script_object_get_key(object))))
        {
            return i;
        }
    }
    return -1;
}

/**
 * put
 */
void flv_tag_script_ecma_put_object(FLVTagScriptEcma *script_ecma, FLVTagScriptObject *object)
{
    if (script_ecma == NULL)
    {
        return;
    }
    if (script_ecma->capacity > 0)
    {
        char *key = flv_tag_script_string_get_data(flv_tag_script_object_get_key(object));
        FLVTagScriptObject *object_old = flv_tag_script_ecma_get_object(script_ecma, key);
        int index = flv_tag_script_ecma_find(script_ecma, key);
        if (object_old != NULL)
        {
            flv_tag_script_object_and_data_free(object_old);
            script_ecma->objects[index] = object;
            return;
        }
    }
    else
    {
        script_ecma->capacity = ECMA_ARRAY_INIT;
        script_ecma->objects = (FLVTagScriptObject **)malloc(sizeof(FLVTagScriptObject *) * ECMA_ARRAY_INIT);
        memset(script_ecma->objects, 0, sizeof(FLVTagScriptObject *) * ECMA_ARRAY_INIT);
    }
    // TODO: 数据添加
    if (script_ecma->length == script_ecma->capacity)
    {
        FLVTagScriptObject **object_new = (FLVTagScriptObject **)malloc(sizeof(FLVTagScriptObject *) * script_ecma->length + sizeof(FLVTagScriptObject *) * ECMA_ARRAY_INIT * ECMA_ARRAY_SCALE);
        memset(object_new, 0, sizeof(FLVTagScriptObject *) * script_ecma->length + sizeof(FLVTagScriptObject *) * ECMA_ARRAY_INIT * ECMA_ARRAY_SCALE);
        memcpy(object_new, script_ecma->objects, sizeof(FLVTagScriptObject *) * script_ecma->length);
        for (int i = 0; i < script_ecma->length; ++i)
        {
            flv_tag_script_object_and_data_free(script_ecma->objects[i]);
        }
        free(script_ecma->objects);
        script_ecma->objects = object_new;
    }
    script_ecma->objects[script_ecma->length++] = object;
}

/**
 * remove
 */
void flv_tag_script_ecma_remove_object(FLVTagScriptEcma *script_ecma, char *key)
{
    if (script_ecma == NULL)
    {
        return;
    }
    // TODO: 实现object移除
}