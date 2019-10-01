#ifndef FLV_TAG_SCRIPT_STRING_HEADER
#define FLV_TAG_SCRIPT_STRING_HEADER

/**
 * flv tag data string
 */
typedef struct _FLVTagScriptString FLVTagScriptString;

/**
 * 创建string类型的tag
 */
FLVTagScriptString *flv_tag_script_string_new();

/**
 * 释放string的tag
 */
void flv_tag_script_string_free(FLVTagScriptString *script_string);

/**
 * 释放string的tag及其数据
 */
void flv_tag_script_string_and_data_free(FLVTagScriptString *script_string);

/**
 * 获取字符串长度
 */
int flv_tag_script_string_length(FLVTagScriptString *script_string);

/**
 * 设置字符串长度
 */
void flv_tag_script_set_string_length(FLVTagScriptString *script_string, int length);

/**
 * 获取字符串
 */
char *flv_tag_script_string_get_data(FLVTagScriptString *script_string);

/**
 * 设置字符串
 */
void flv_tag_script_string_set_data(FLVTagScriptString *script_string, char *data);

#endif // !FLV_TAG_SCRIPT_STRING_HEADER