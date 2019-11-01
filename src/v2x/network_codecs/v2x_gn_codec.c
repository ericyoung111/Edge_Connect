/**
 *
 * implements Geonetworking Codecs
 * 
 * @copyright Eric Young 2019-present
 */
#include <string.h>
#include <v2x_gn_codec.h>
#include <v2x_codec_util.h>

int v2x_gn_encode_geonet_addr(struct geonet_addr *addr, uint8_t *bufout, int pos, size_t bufsize)
{
    bufout[pos] = !!(addr->manual) << 7;
    bufout[pos] |= (addr->station_type) << 6;
    v2x_codec_util_safe_inc(&pos, 2, bufsize);

    memcpy(bufout + pos, addr->mid, sizeof(addr->mid));
    v2x_codec_util_safe_inc(&pos, sizeof(addr->mid), bufsize);

    return pos;
}