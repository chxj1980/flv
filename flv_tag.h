#ifndef FLV_TAG_HEADER
#define FLV_TAG_HEADER
/**
 * flv tag定义
 */
typedef struct _FLVTag FLVTag;

/**
 * tag类型枚举定义
 */
typedef enum _FLVTagType
{
    TAG_TYPE_UNKNOW,
    TAG_TYPE_AUDIO = 0x8,
    TAG_TYPE_VIDEO = 0x9,
    TAG_TYPE_SCRIPT = 0x12
} FLVTagType;

/**
 * 创建tag
 */
FLVTag *flv_tag_new();

/**
 * 释放tag
 */
void flv_tag_free(FLVTag *tag);

/**
 * 释放tag及其data
 */
void flv_tag_and_data_free(FLVTag *tag);

/**
 * 获取上一个tag大小
 */
int flv_tag_get_previous_size(FLVTag *tag);

/**
 * 设置上一个tag大小
 */
void flv_tag_set_previous_size(FLVTag *tag, int size);

/**
 * 获取tag类型
 */
FLVTagType flv_tag_get_type(FLVTag *tag);

/**
 * 设置tag类型
 */
void flv_tag_set_type(FLVTag *tag, int type);

/**
 * 获取tag data的长度
 */
int flv_tag_get_data_size(FLVTag *tag);

/**
 * 设置tag data的长度
 */
void flv_tag_set_data_size(FLVTag *tag, int size);

/**
 * 获取时间(ms)
 */
int flv_tag_get_time_stamp(FLVTag *tag);

/**
 * 设置时间(ms)
 */
void flv_tag_set_time_stamp(FLVTag *tag, int time);

/**
 * 获取streams id
 */
int flv_tag_get_streams_id(FLVTag *tag);

/**
 * 设置streams id
 */
void flv_tag_set_streams_id(FLVTag *tag, int id);

/**
 * 获取tag data
 */
void *flv_tag_get_data(FLVTag *tag);

/**
 * 设置tag data
 */
void flv_tag_set_data(FLVTag *tag, void *data);
#endif // !FLV_TAG_HEADER