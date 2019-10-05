#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "flv_header.h"
#include "flv_tag.h"
#include "flv_tag_script.h"
#include "flv_tag_script_string.h"
#include "flv_tag_script_double.h"
#include "flv_tag_script_ecma.h"
#include "flv_tag_script_object.h"
#include "flv_tag_script_bool.h"
#include "utils.h"

/**
 * 解析文件头
 */
FLVHeader *parse_header(FILE *file, int *offset)
{
    // 跳转到文件头部分
    fseek(file, *offset, SEEK_SET);
    // 读取文件头
    FLVHeader *header = flv_header_new();
    *offset += fread(header, 5, 1, file) * 5;
    // 读取文件头大小
    byte length[4];
    // 跳转到文件头大小部分
    fseek(file, *offset, SEEK_SET);
    *offset += fread(length, 4, 1, file) * 4;
    flv_header_set_length(header, (int)read_big(length, 4));

    // 判断文件格式
    if (strncmp(flv_header_get_type(header), "FLV", 3))
    {
        printf("不是FLV文件!!!\n");
        return NULL;
    }
    // 打印文件头信息
    printf("====FLVHeader====\n");
    printf("文件类型: %s\n", flv_header_get_type(header));
    printf("FLV版本: %d\n", flv_header_get_version(header));
    printf("有音频: %d\n", flv_header_has_audio(header));
    printf("有视频: %d\n", flv_header_has_video(header));
    printf("文件头长度: %d\n", flv_header_length(header));
    printf("====FLVHeader END====\n\n");

    return header;
}

void *parse_tag_script_type(FILE *file, int *offset, FLVTagScriptDataType type);
void *parse_tag_script_number(FILE *file, int *offset);
void *parse_tag_script_string(FILE *file, int *offset);
void *parse_tag_script_long_string(FILE *file, int *offset);
void *parse_tag_script_ecma(FILE *file, int *offset);
void *parse_tag_script_object(FILE *file, int *offset);
void *parse_tag_script_bool(FILE *file, int *offset);

/**
 * 解析数字
 */
void *parse_tag_script_number(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    FLVTagScriptDouble *script_double = flv_tag_script_double_new();
    byte bytes[8];
    *offset += fread(bytes, 8, 1, file) * 8;
    long *longs = (long *)malloc(sizeof(long));
    for (int i = 0; i < 8; ++i)
    {
        *longs = (*longs << 8) | bytes[i];
    }
    flv_tag_script_double_set_data(script_double, longs);

    return script_double;
}

/**
 * 解析字符串
 */
void *parse_tag_script_string(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    FLVTagScriptString *script_string = flv_tag_script_string_new();
    byte bytes[2];
    *offset += fread(bytes, 2, 1, file) * 2;
    flv_tag_script_set_string_length(script_string, read_big(bytes, 2));
    char *strs = (char *)malloc(sizeof(char) * flv_tag_script_string_length(script_string));
    fseek(file, *offset, SEEK_SET);
    *offset += fread(strs, flv_tag_script_string_length(script_string), 1, file) * flv_tag_script_string_length(script_string);
    flv_tag_script_string_set_data(script_string, strs);
    return script_string;
}

/**
 * 解析长字符串
 */
void *parse_tag_script_long_string(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    FLVTagScriptString *script_string = flv_tag_script_string_new();
    byte bytes[4];
    *offset += fread(bytes, 4, 1, file) * 4;
    flv_tag_script_set_string_length(script_string, read_big(bytes, 4));
    char *strs = (char *)malloc(sizeof(char) * flv_tag_script_string_length(script_string));
    fseek(file, *offset, SEEK_SET);
    *offset += fread(strs, flv_tag_script_string_length(script_string), 1, file) * flv_tag_script_string_length(script_string);
    flv_tag_script_string_set_data(script_string, strs);
    return script_string;
}

/**
 * 解析ecma数组
 */
void *parse_tag_script_ecma(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    FLVTagScriptEcma *script_ecma = flv_tag_script_ecma_new();
    int size = 0;
    byte bytes[4];
    *offset += fread(bytes, 4, 1, file) * 4;
    size = read_big(bytes, 4);

    for (int i = 0; i < size; ++i)
    {
        parse_tag_script_object(file, offset);
        //flv_tag_script_ecma_put_object(script_ecma, parse_tag_script_object(file, offset));
    }

    return script_ecma;
}

/**
 * 解析object
 */
void *parse_tag_script_object(FILE *file, int *offset)
{
    FLVTagScriptObject *script_object = flv_tag_script_object_new();
    flv_tag_script_object_set_key(script_object, parse_tag_script_string(file, offset));
    printf("%s : ", flv_tag_script_string_get_data(flv_tag_script_object_get_key(script_object)));
    fseek(file, *offset, SEEK_SET);

    FLVTagScript *tag_script = flv_tag_script_new();
    *offset += fread(tag_script, 1, 1, file) * 1;
    flv_tag_script_set_data(tag_script, parse_tag_script_type(file, offset, flv_tag_script_get_type(tag_script)));

    switch (flv_tag_script_get_type(tag_script))
    {
    case SCRIPT_TYPE_NUMBER:
        printf("%f\n", flv_tag_script_double_get_data((FLVTagScriptDouble *)flv_tag_script_get_data(tag_script)));
        break;
    case SCRIPT_TYPE_STRING:
        printf("%s\n", flv_tag_script_string_get_data((FLVTagScriptString *)flv_tag_script_get_data(tag_script)));
        break;
    case SCRIPT_TYPE_BOOLEAN:
        printf("%d\n", flv_tag_script_bool_get_data((FLVTagScriptBool *)flv_tag_script_get_data(tag_script)));
        break;
    }

    flv_tag_script_object_set_type(script_object, flv_tag_script_get_type(tag_script));
    flv_tag_script_object_set_value(script_object, tag_script);
    return script_object;
}

void *parse_tag_script_bool(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    FLVTagScriptBool *script_bool = flv_tag_script_bool_new();
    byte boolean[1];
    *offset += fread(boolean, 1, 1, file) * 1;
    flv_tag_script_bool_set_data(script_bool, boolean[0] == 1);

    return script_bool;
}

/**
 * 解析数据类型
 */
void *parse_tag_script_type(FILE *file, int *offset, FLVTagScriptDataType type)
{
    switch (type)
    {
    case SCRIPT_TYPE_NUMBER:
        return parse_tag_script_number(file, offset);
    case SCRIPT_TYPE_STRING:
        return parse_tag_script_string(file, offset);
    case SCRIPT_TYPE_LONG_STRING:
        return parse_tag_script_long_string(file, offset);
    case SCRIPT_TYPE_ECMA_ARRAY:
        return parse_tag_script_ecma(file, offset);
    case SCRIPT_TYPE_OBJECT:
        return parse_tag_script_object(file, offset);
    case SCRIPT_TYPE_BOOLEAN:
        return parse_tag_script_bool(file, offset);
    default:
        return NULL;
    }
}

/**
 * 解析script tag
 */
FLVTagScript **parse_tag_script(FILE *file, int *offset, int size)
{
    int start = *offset;
    while (*offset - start < size)
    {
        // 跳转到tag位置
        fseek(file, *offset, SEEK_SET);
        FLVTagScript *tag_script = flv_tag_script_new();
        *offset += fread(tag_script, 1, 1, file) * 1;
        flv_tag_script_set_data(tag_script, parse_tag_script_type(file, offset, flv_tag_script_get_type(tag_script)));
    }
    return NULL;
}

/**
 * 解析tag
 */
FLVTag *parse_tag(FILE *file, int *offset)
{
    // 跳转到tag位置
    fseek(file, *offset, SEEK_SET);
    // flv tag
    FLVTag *tag = flv_tag_new();
    // 获取tag基本信息
    byte bytes[4];
    // prrvious
    *offset += fread(bytes, 4, 1, file) * 4;
    fseek(file, *offset, SEEK_SET);
    flv_tag_set_previous_size(tag, (int)read_big(bytes, 4));
    // type
    *offset += fread(bytes, 1, 1, file) * 1;
    fseek(file, *offset, SEEK_SET);
    flv_tag_set_type(tag, bytes[0]);
    // data size
    *offset += fread(bytes, 3, 1, file) * 3;
    fseek(file, *offset, SEEK_SET);
    flv_tag_set_data_size(tag, read_big(bytes, 3));
    // time
    *offset += fread(bytes, 4, 1, file) * 4;
    fseek(file, *offset, SEEK_SET);
    int time = read_big(bytes, 3);
    flv_tag_set_time_stamp(tag, (time & 0xffffff) | bytes[3]);
    // stream id
    *offset += fread(bytes, 3, 1, file) * 3;
    fseek(file, *offset, SEEK_SET);
    flv_tag_set_streams_id(tag, read_big(bytes, 3));

    // 打印tag信息
    printf("====FLVTag====\n");
    printf("tag类型: %d\n", flv_tag_get_type(tag));
    printf("上一个大小: %d\n", flv_tag_get_previous_size(tag));
    printf("当前tag大小: %d\n", flv_tag_get_data_size(tag));
    printf("时间戳: %d\n", flv_tag_get_time_stamp(tag));
    printf("====FLVTag END====\n\n");

    switch (flv_tag_get_type(tag))
    {
    case TAG_TYPE_SCRIPT:
        flv_tag_set_data(tag, parse_tag_script(file, offset, flv_tag_get_data_size(tag)));
        break;
    case TAG_TYPE_AUDIO:
        break;
    case TAG_TYPE_VIDEO:
        break;
    default:
        break;
    }
    return tag;
}

int main()
{
    // 打开文件
    char *flv_path = "/data/data/com.termux/files/home/Videos/test.flv";
    FILE *flv_file = fopen(flv_path, "rb");
    if (flv_file == NULL)
    {
        perror(flv_path);
        return 1;
    }

    int offset = 0;

    // 解析文件头
    FLVHeader *header = parse_header(flv_file, &offset);
    printf("文件头结束位置: %d\n", offset);

    // 解析tag
    FLVTag *tag = parse_tag(flv_file, &offset);
    printf("tag结束位置: %d\n", offset);

    // 关闭文件流
    fclose(flv_file);
    return 0;
}
