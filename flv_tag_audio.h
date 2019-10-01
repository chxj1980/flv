#ifndef FLV_TAG_AUDIO_HEADER
#define FLV_TAG_AUDIO_HEADER
#include "types.h"
/**
 * flv audio tag data定义
 */
typedef struct _FLVTagAudio
{
    /**
     * audio info
     * bit[7-4]: 音频格式,
     *           0 - Linear PCM, platform endian
     *           1 - ADPCM
     *           2 - MP3
     *           3 - LinearPCM，little endian
     *           4 - Nellymoser 16-kHz mono
     *           5 - Nellymoser 8-kHZ mono
     *           6 - Nellymoser
     *           7 - G.711 A-law logarithmic PCM
     *           8 - G.711 U-law logarithmic PCM
     *           9 - reserved
     *           10 - AAC
     *           11 - Speex
     *           14 - MP3 8-kHz
     *           15 - Device-specific sound
     * bit[3-2]: 声音频率
     *           0 - snd 8 bit
     *           1 - snd 16 bit
     * bit[1]: 采样大小,0-八位,1-十六位
     * bit[0]: 声道数,0-mono sound,1-stereo sound
     */
    byte audio_info;
    /**
     * 声音格式为10时,会有多的一个字节
     * 0-aac序列头
     * 1-aac裸数据
     */
    byte aac_packet_type;
}FLVTagAudio; 
#endif // !FLV_TAG_AUDIO_HEADER