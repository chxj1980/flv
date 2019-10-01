#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "flv_tag.h"
#include "flv_tag_script.h"

/**
 * flv tag定义
 */
typedef struct _FLVTag
{
    /**
     * 上一个tag的大小
     * 第一个tag size总是0
     */
    int previous_size;
    /**
     * tag类型
     * bit[7-6]: 保留,应该为0
     * bit[5]: filter,通常为0
     * bit[4-0]: tag类型,音频(0x08),视频(0x09),脚本(0x12)
     */
    byte type;
    /**
     * tag data的长度 
     */
    int data_size : 24;
    /**
     * 毫秒,类型是脚本时为0
     */
    int time_stamp : 24;
    /**
     *时间戳高8位
     * time_stamp_extended<<24 + time_stamp
     */
    int time_stamp_extended : 8;
    /**
     * 0
     */
    int streams_id : 24;
    /**
     * tag保存的数据
     */
    void *data;
} FLVTag;

/**
 * 创建tag
 */
FLVTag *flv_tag_new()
{
    FLVTag *tag = (FLVTag *)malloc(sizeof(FLVTag));
    memset(tag, 0, sizeof(FLVTag));
    return tag;
}

/**
 * 释放tag
 */
void flv_tag_free(FLVTag *tag)
{
    if (tag != NULL)
    {
        free(tag);
    }
}

/**
 * 释放tag及其data
 */
void flv_tag_and_data_free(FLVTag *tag)
{
    if (tag != NULL)
    {
        if (tag->data != NULL)
        {
            // TODO: 添加tag data的释放
            switch (flv_tag_get_type(tag->data))
            {
            case TAG_TYPE_AUDIO:
                break;
            case TAG_TYPE_VIDEO:
                break;
            case TAG_TYPE_SCRIPT:
                flv_tag_script_and_data_free((FLVTagScript *)(tag->data));
                break;
            default:
                break;
            }
        }
        free(tag);
    }
}

/**
 * 获取上一个tag大小
 */
int flv_tag_get_previous_size(FLVTag *tag)
{
    if (tag == NULL)
    {
        return -1;
    }
    return tag->previous_size;
}

/**
 * 设置上一个tag大小
 */
void flv_tag_set_previous_size(FLVTag *tag, int size)
{
    if (tag == NULL)
    {
        return;
    }
    tag->previous_size = size;
}

/**
 * 获取tag类型
 */
FLVTagType flv_tag_get_type(FLVTag *tag)
{
    if (tag == NULL)
    {
        return TAG_TYPE_UNKNOW;
    }
    switch ((tag->type) & 0x1f)
    {
    case 0x08:
        return TAG_TYPE_AUDIO;
    case 0x09:
        return TAG_TYPE_VIDEO;
    case 0x12:
        return TAG_TYPE_SCRIPT;
    default:
        return TAG_TYPE_UNKNOW;
    }
}

/**
 * 设置tag类型
 */
void flv_tag_set_type(FLVTag *tag, int type)
{
    if (tag == NULL)
    {
        return;
    }
    tag->type = (tag->type & 0x1c) | (type | 0xff);
}

/**
 * 获取tag data的长度
 */
int flv_tag_get_data_size(FLVTag *tag)
{
    if (tag == NULL)
    {
        return -1;
    }
    return (int)(tag->data_size);
}

/**
 * 设置tag data的长度
 */
void flv_tag_set_data_size(FLVTag *tag, int size)
{
    if (tag == NULL)
    {
        return;
    }
    tag->data_size = size & 0xffffff;
}

/**
 * 获取时间(ms)
 */
int flv_tag_get_time_stamp(FLVTag *tag)
{
    if (tag == NULL)
    {
        return -1;
    }
    return ((int)(tag->time_stamp_extended) << 24) + tag->time_stamp;
}

/**
 * 设置时间(ms)
 */
void flv_tag_set_time_stamp(FLVTag *tag, int time)
{
    if (tag == NULL)
    {
        return;
    }
    tag->time_stamp_extended = (time & 0xff000000) >> 24;
    tag->time_stamp = (time & 0xffffff);
}

/**
 * 获取streams id
 */
int flv_tag_get_streams_id(FLVTag *tag)
{
    if (tag == NULL)
    {
        return -1;
    }
    return (int)(tag->streams_id);
}

/**
 * 设置streams id
 */
void flv_tag_set_streams_id(FLVTag *tag, int id)
{
    if (tag == NULL)
    {
        return;
    }
    tag->streams_id = id & 0xffffff;
}

/**
 * 获取tag data
 */
void *flv_tag_get_data(FLVTag *tag)
{
    if (tag == NULL)
    {
        return NULL;
    }
    return tag->data;
}

/**
 * 设置tag data
 */
void flv_tag_set_data(FLVTag *tag, void *data)
{
    if (tag == NULL)
    {
        return;
    }
    tag->data = data;
}