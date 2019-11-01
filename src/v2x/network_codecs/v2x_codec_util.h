/**
 * 
 * implements codec utilities
 * 
 * @copyright Eric Young 2019-present
 */
#ifndef __V2X_CODEC_UTIL_H__
#define __V2X_CODEC_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

void v2x_codec_util_safe_inc(int *pos, int to_size, int bufsize);

#ifdef __cplusplus
}
#endif

#endif