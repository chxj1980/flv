#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flv_header.h"

/**
 * 文件头定义
 */
typedef struct _FLVHeader
{
    /**
     * 文件头
     * F(0x46)L0(0x4c)V(0x56)
     */
    char type[3];
    /**
     * flv 版本
     * version: 0x01
     */
    byte version;
    /**
     * flv 流信息
     * bit[7-3]: 00000 保留
     * bit[2]: 1-audio 0-no
     * bit[1]: 0 保留
     * bit[0]: 1-video 0-no
     */
    byte stream_info;
    /**
     * 头长度
     * 一般情况是9,大于9表示还有扩展
     */
    int length;
} FLVHeader;

/**
 * 创建header
 */
FLVHeader *flv_header_new()
{
    FLVHeader *header = (FLVHeader*)malloc(sizeof(FLVHeader));
    memset(header, 0, sizeof(FLVHeader));
    return header;
}

/**
 * 释放header
 */
void flv_header_free(FLVHeader *header)
{
    if(header != NULL)
    {
        free(header);
    }
}

/**
 * 获取头类型
 */
char *flv_header_get_type(FLVHeader *header)
{
    if(header == NULL)
    {
        return NULL;
    }
    return header->type;
}

/**
 * 设置头类型
 */
void flv_header_set_type(FLVHeader *header, char *type)
{
    if(header == NULL || strlen(type) <3)
    {
        return;
    }
    for(int i = 0;i < 3;++i)
    {
        header->type[i] = type[i];
    }
}

/**
 * 获取flv版本
 */
int flv_header_get_version(FLVHeader *header)
{
    if(header == NULL)
    {
        return -1;
    }
    return (int)(header->version);
}

/**
 * 设置flv版本
 */
void flv_header_set_version(FLVHeader *header, int version)
{
    if(header == NULL)
    {
        return;
    }
    header->version = version & 0xff;
}

/**
 * 是否包含音频
 */
bool flv_header_has_audio(FLVHeader *header)
{
    if(header == NULL)
    {
        return false;
    }
    return ((header->stream_info) & 0x04) >> 2;
}

/**
 * 设置是否包含音频
 */
void flv_header_set_audio(FLVHeader *header, bool has)
{
    if(header == NULL)
    {
        return;
    }
    header->stream_info = (header->stream_info & 0xfb) | (has ? 0x04 : 0x00);
}

/**
 * 是否包含视频
 */
bool flv_header_has_video(FLVHeader *header)
{
    if(header == NULL)
    {
        return false;
    }
    return (header->stream_info) & 0x01;
}

/**
 * 设置是否包含视频
 */
void flv_header_set_video(FLVHeader *header, bool has)
{
    if(header == NULL)
    {
        return;
    }
    header->stream_info = (header->stream_info & 0xfe) | (has ? 0x01 : 0x00);
}

/**
 * flv header的大小
 */
int flv_header_length(FLVHeader *header)
{
    if(header == NULL)
    {
        return -1;
    }
    return header->length;
}

/**
 * 设置flv header的大小
 */
void flv_header_set_length(FLVHeader *header, int length)
{
    if(header == NULL)
    {
        return;
    }
    header->length = length;
}