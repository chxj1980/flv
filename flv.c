#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"
#include "flv_header.h"
#include "flv_tag.h"
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
    *offset += fread(header, 9, 1, file) * 9;

    byte b[4];
    fseek(file, 0x05, SEEK_SET);
    fread(&b, 4, 1, file);

    printf("%d\n", flv_header_length(header));
    printf("%d\n", read_big(b, 4));

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
    *offset += fread(tag, 15, 1, file) * 15;

    byte b[3];
    fseek(file, 0x0e, SEEK_SET);
    fread(&b, 3, 1, file);
    printf("%d\n", flv_tag_get_data_size(tag));
    printf("%d\n", read_big(b, 3));
    // 打印tag信息
    printf("====FLVTag====\n");
    printf("tag类型: %d\n", flv_tag_get_type(tag));
    printf("上一个大小: %d\n", flv_tag_get_previous_size(tag));
    printf("当前tag大小: %d\n", flv_tag_get_data_size(tag));
    printf("时间戳: %d\n", flv_tag_get_time_stamp(tag));
    printf("====FLVTag END====\n\n");

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
