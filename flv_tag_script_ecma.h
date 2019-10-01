#ifndef FLV_TAG_SCRIPT_ECMA_HEADER
#define FLV_TAG_SCRIPT_ECMA_HEADER
#include <stdbool.h>
#include "flv_tag_script.h"
#include "flv_tag_script_object.h"

/**
 * ecma script
 */
typedef struct _FLVTagScriptEcma FLVTagScriptEcma;

/**
 * 创建ecma
 */
FLVTagScriptEcma *flv_tag_script_ecma_new();

/**
 * 释放ecma
 */
void flv_tag_script_ecma_free(FLVTagScriptEcma *script_ecma);

/**
 * 释放ecma和数据
 */
void flv_tag_script_ecma_and_data_free(FLVTagScriptEcma *script_ecma);

/**
 * 获取长度
 */
int flv_tag_script_ecma_length(FLVTagScriptEcma *script_ecma);

/**
 * 获取容量
 */
int flv_tag_script_ecma_capacity(FLVTagScriptEcma *script_ecma);

/**
 * objects
 */
FLVTagScriptObject **flv_tag_script_ecma_get_objects(FLVTagScriptEcma *script_ecma);

/**
 * get data
 */
FLVTagScriptObject *flv_tag_script_ecma_get_object(FLVTagScriptEcma *script_ecma, char *key);

/**
 * find index
 */
int flv_tag_script_ecma_find(FLVTagScriptEcma *script_ecma, char *key);

/**
 * put
 */
void flv_tag_script_ecma_put_object(FLVTagScriptEcma *script_ecma, FLVTagScriptObject *object);

/**
 * remove
 */
void flv_tag_script_ecma_remove_object(FLVTagScriptEcma *script_ecma, char *key);

#endif // !FLV_TAG_SCRIPT_ECMA_HEADER