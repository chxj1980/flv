#ifndef FLV_TAG_VIDEO_HEADER
#define FLV_TAG_VIDEO_HEADER
#include "types.h"
/**
 * flv video tag data定义
 */
typedef struct _FLVTagVideo
{
    /**
     * 帧类型
     * 1-
     */
    byte type:4;
    byte codec_id:4;
}FLVTagVideo;
#endif // !FLV_TAG_VIDEO_HEADER