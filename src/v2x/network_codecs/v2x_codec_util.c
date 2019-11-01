/**
 * 
 * implements utilities for safe buffer position pointer
 * 
 * @copyright Eric Young 2019-present
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void v2x_codec_util_assertion(int condition, const char *failure, const char *func, int line)
{
    if (condition) {
        fprintf(stderr, "Assertion %s @ %s->%d", failure, func, line);
        abort();
    }
}

void v2x_codec_util_safe_inc(int *pos, int to_size, int bufsize)
{
    v2x_codec_util_assertion((*pos + to_size > bufsize),
                            "out of bounds bufsize", __func__, __LINE__);
    *pos = *pos + to_size;
}
