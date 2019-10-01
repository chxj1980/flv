#ifndef FLV_HEADER_HEADER
#define FLV_HEADER_HEADER

#include <stdbool.h>
#include "types.h"
/**
 * 文件头定义
 */
typedef struct _FLVHeader FLVHeader;

/**
 * 创建header
 */
FLVHeader *flv_header_new();

/**
 * 释放header
 */
void flv_header_free(FLVHeader *header);

/**
 * 获取头类型
 */
char *flv_header_get_type(FLVHeader *header);

/**
 * 设置头类型
 */
void flv_header_set_type(FLVHeader *header, char *type);

/**
 * 获取flv版本
 */
int flv_header_get_version(FLVHeader *header);

/**
 * 设置flv版本
 */
void flv_header_set_version(FLVHeader *header, int version);

/**
 * 是否包含音频
 */
bool flv_header_has_audio(FLVHeader *header);

/**
 * 设置是否包含音频
 */
void flv_header_set_audio(FLVHeader *header, bool has);

/**
 * 是否包含视频
 */
bool flv_header_has_video(FLVHeader *header);

/**
 * 设置是否包含视频
 */
void flv_header_set_video(FLVHeader *header, bool has);

/**
 * flv header的大小
 */
int flv_header_length(FLVHeader *header);

/**
 * 设置flv header的大小
 */
void flv_header_set_length(FLVHeader *header, int length);

#endif // !FLV_HEADER