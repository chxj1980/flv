#ifndef FLV_TAG_SCRIPT_DOUBLE_HEADER
#define FLV_TAG_SCRIPT_DOUBLE_HEADER

/**
 * double script数据类型
 */
typedef struct _FLVTagScriptDouble FLVTagScriptDouble;

/**
 * 创建
 */
FLVTagScriptDouble *flv_tag_script_double_new();

/**
 * 释放
 */
void flv_tag_script_double_free(FLVTagScriptDouble *script_double);

/**
 * 获取值
 */
double flv_tag_script_get_data(FLVTagScriptDouble *script_double);

/**
 * 设置data值
 */
void flv_tag_script_set_data(FLVTagScriptDouble *script_double, void *data);

#endif // !FLV_TAG_SCRIPT_DOUBLE_HEADER