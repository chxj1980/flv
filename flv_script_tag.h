#ifndef FLV_SCRIPT_TAG_HEADER
#define FLV_SCRIPT_TAG_HEADER
/**
 * flv script tag 
 */
typedef struct _FLVScriptTag{
    /**
     * script data 的数据类型
     * 0-number
     * 1-boolean
     * 2-string
     * 3-object
     * 4-movie clip
     * 5-null
     * 6-undefined
     * 7-reference
     * 8-ECMA array
     * 9-object and maker
     * 10-script array
     * 11-date
     * 12-long string
     */
    byte type;
}FLVScriptTag;
#endif // !FLV_SCRIPT_TAG_HEADER