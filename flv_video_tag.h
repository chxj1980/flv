#ifndef FLV_VIDEO_TAG_HEADER
#define FLV_VIDEO_TAG_HEADER
/**
 * flv video tag data定义
 */
typedef struct _FLVVideoTag
{
    /**
     * 帧类型
     * 1-
     */
    byte type:4;
    byte codec_id:4;
}FLVVideoTag;
#endif // !FLV_VIDEO_TAG_HEADER