/**
 * 
 * implements WSA encode and decode layer
 * 
 * @copyright Eric Young 2019-present
 */
#include <iostream>
#include <string>
#include <vector>
#include <v2x_codec_util.h>
#include <v2x_16093_common_structs.h>
#include <v2x_wsa.h>

int v2x_wsa_encode(v2x_wsa_packet *wsa_pkt, uint8_t *dataout, size_t datasize)
{
    int pos = 0;

    if (wsa_pkt->wsa_version != V2X_WSA_VERSION_CUR) {
        return -1;
    }

    // fill in WSA version
    dataout[pos] = (wsa_pkt->wsa_version << 4);

    // fill in opts
    if (wsa_pkt->has_info_elem) {
        dataout[pos] |= 0x08;
    }
    if (wsa_pkt->has_service_info_elem) {
        dataout[pos] |= 0x04;
    }
    if (wsa_pkt->has_channel_info_elem) {
        dataout[pos] |= 0x02;
    }
    if (wsa_pkt->has_wra_elem) {
        dataout[pos] |= 0x01;
    }

    v2x_codec_util_safe_inc(&pos, 1, datasize);

    // fill in WSA id
    dataout[pos] = (wsa_pkt->wsa_id << 4);

    // fill in content count
    dataout[pos] |= (wsa_pkt->content_count);

    v2x_codec_util_safe_inc(&pos, 1, datasize);

    // fill in info element ext
    if (wsa_pkt->has_info_elem) {
        int ie_count_position = pos;
        v2x_codec_util_safe_inc(&pos, 1, datasize);

        int ie_optcount = 0;

        // fill in the repeat rate TAG, LEN, VAL
        if (wsa_pkt->info_elem.repeatrate.valid) {
            ie_optcount ++;

            dataout[pos] = V2X_WSMP_IE_REPEAT_RATE;
            v2x_codec_util_safe_inc(&pos, 1, datasize);

            dataout[pos] = V2X_WSMP_IE_REPEAT_RATE_LEN;
            v2x_codec_util_safe_inc(&pos, 1, datasize);

            dataout[pos] = wsa_pkt->info_elem.repeatrate.repeatrate;
            v2x_codec_util_safe_inc(&pos, 1, datasize);
        }
    }

    // fill in service info elem ext
    if (wsa_pkt->has_service_info_elem) {

    }

    // fill in channel info elem ext
    if (wsa_pkt->has_channel_info_elem) {

    }

    // fill in wra info elem ext
    if (wsa_pkt->has_wra_elem) {

    }

    // finally returned buffer length that is being encoded
    return pos;
}

int v2x_wsa_decode(v2x_wsa_packet *wsa_pkt, uint8_t *datain, size_t datalen)
{
    return -1;
}
