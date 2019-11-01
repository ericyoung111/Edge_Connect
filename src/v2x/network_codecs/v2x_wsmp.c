/**
 * 
 * implement V2X WSMP protocol
 * 
 * copyright Eric Young 2019-present
 */
#include <stdio.h>
#include <string.h>
#include <v2x_codec_util.h>
#include <v2x_wsmp.h>

/**
 * Encode WSMP packet and return outbuf and the length of final payload
 */
int v2x_wsmp_encode(const struct v2x_wsmp_packet *pkt, uint8_t *data, size_t datalen, uint8_t *outbuf)
{
    int pos = 0;
    int valid_opts = 0;

    // fill in first byte
    outbuf[pos] = (pkt->subtype << 4);

    // check for opts
    if (pkt->chan.valid) {
        valid_opts ++;
    }
    if (pkt->rate.valid) {
        valid_opts ++;
    }
    if (pkt->txpow.valid) {
        valid_opts ++;
    }

    if (valid_opts) {
        outbuf[pos] |= 0x80;
    }
    outbuf[pos] |= pkt->wsmp_version;
    v2x_codec_util_safe_inc(&pos, 1, datalen);

    // set opts
    if (valid_opts) {

        // set opt count
        outbuf[pos] = valid_opts;
        v2x_codec_util_safe_inc(&pos, 1, datalen);

        // encode channel
        //
        // always IE name | length | value
        if (pkt->chan.valid) {
            outbuf[pos] = V2X_WSMP_IE_CHAN;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = V2X_WSMP_IE_CHAN_LEN;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = pkt->chan.chan;
            v2x_codec_util_safe_inc(&pos, 1, datalen);
        }

        // encode rate ..
        //
        // IE name | length | value
        if (pkt->rate.valid) {
            outbuf[pos] = V2X_WSMP_IE_RATE;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = V2X_WSMP_IE_RATE_LEN;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = pkt->rate.datarate;
            v2x_codec_util_safe_inc(&pos, 1, datalen);
        }

        // encode txpow ..
        //
        // IE name | length | value
        if (pkt->txpow.valid) {
            outbuf[pos] = V2X_WSMP_IE_TXPOW;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = V2X_WSMP_IE_TXPOW_LEN;
            v2x_codec_util_safe_inc(&pos, 1, datalen);

            outbuf[pos] = pkt->txpow.txpower;
            v2x_codec_util_safe_inc(&pos, 1, datalen);
        }
    }

    // encode tpid
    //
    // no IE for TPID
    outbuf[pos] = pkt->tpid;
    v2x_codec_util_safe_inc(&pos, 1, datalen);

    // encode PSID
    //
    memcpy(outbuf + pos, &pkt->psid, sizeof(pkt->psid));
    v2x_codec_util_safe_inc(&pos, sizeof(pkt->psid), datalen);

    // encode wsmplen
    //
    memcpy(outbuf + pos, &pkt->wsmplen, sizeof(pkt->wsmplen));
    v2x_codec_util_safe_inc(&pos, sizeof(pkt->wsmplen), datalen);

    // copy final data packet
    //
    memcpy(outbuf + pos, data, datalen);
    v2x_codec_util_safe_inc(&pos, pkt->wsmplen, datalen);

    return pos;
}

int v2x_wsmp_decode(struct v2x_wsmp_packet *packet, uint8_t *datain, size_t datasize, uint8_t *wsmdata)
{
    int pos = 0;

    // copy subtype
    packet->subtype = datain[pos] >> 4;

    // copy options
    packet->options = datain[pos] & 0x08;

    // copy wsmp version
    packet->wsmp_version = datain[pos] & 0x07;

    pos ++;

    if (packet->options) {
        int ie_count = datain[pos];
        pos ++;

        int i;
        // if no IE available.. we don't enter here
        for (i = 0; i < ie_count; i ++) {
            if (datain[pos] == V2X_WSMP_IE_CHAN) {
                // skip the type and length field
                pos += 2;

                packet->chan.chan = datain[pos];
                pos ++;
            }
            if (datain[pos] == V2X_WSMP_IE_RATE) {
                // skip the type and length field
                pos += 2;

                packet->rate.datarate = datain[pos];
                pos ++;
            }
            if (datain[pos] == V2X_WSMP_IE_TXPOW) {
                // skip the type and length field
                pos += 2;

                packet->txpow.txpower = datain[pos];
                pos ++;
            }
        }
    }

    // copy TPID
    packet->tpid = datain[pos];
    pos ++;

    // copy PSID
    memcpy(&packet->psid, datain + pos, sizeof(packet->psid));
    pos += sizeof(packet->psid);

    // copy WSMPlen
    memcpy(&packet->wsmplen, datain + pos, sizeof(packet->wsmplen));
    pos += sizeof(packet->wsmplen);

    // finally after the head, we leave with the data
    // avoid this memcpy?
    memcpy(wsmdata, datain + pos, packet->wsmplen);

    return pos + packet->wsmplen;
}