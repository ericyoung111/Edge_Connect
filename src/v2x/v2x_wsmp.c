#include <stdio.h>
#include <string.h>
#include <v2x_wsmp.h>

/**
 * Encode WSMP packet and return outbuf and the length of final payload
 */
int v2x_wsmp_encode(struct v2x_wsmp_packet *pkt, uint8_t *data, size_t datalen, uint8_t *outbuf)
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
    pos ++;

    // set opts
    if (valid_opts) {

        // set opt count
        outbuf[pos] = valid_opts;
        pos ++;

        // encode channel
        //
        // always IE name | length | value
        if (pkt->chan.valid) {
            outbuf[pos] = V2X_WSMP_IE_CHAN;
            pos ++;

            outbuf[pos] = V2X_WSMP_IE_CHAN_LEN;
            pos ++;

            outbuf[pos] = pkt->chan.chan;
            pos ++;
        }

        // encode rate ..
        //
        // IE name | length | value
        if (pkt->rate.valid) {
            outbuf[pos] = V2X_WSMP_IE_RATE;
            pos ++;

            outbuf[pos] = V2X_WSMP_IE_RATE_LEN;
            pos ++;

            outbuf[pos] = pkt->rate.datarate;
            pos ++;
        }

        // encode txpow ..
        //
        // IE name | length | value
        if (pkt->txpow.valid) {
            outbuf[pos] = V2X_WSMP_IE_TXPOW;
            pos ++;

            outbuf[pos] = V2X_WSMP_IE_TXPOW_LEN;
            pos ++;

            outbuf[pos] = pkt->txpow.txpower;
            pos ++;
        }
    }

    // encode tpid
    //
    // no IE for TPID
    outbuf[pos] = pkt->tpid;
    pos ++;

    // encode PSID
    //
    memcpy(outbuf + pos, &pkt->psid, sizeof(pkt->psid));
    pos += sizeof(pkt->psid);

    // encode wsmplen
    //
    memcpy(outbuf + pos, &pkt->wsmplen, sizeof(pkt->wsmplen));
    pos += sizeof(pkt->wsmplen);

    // copy final data packet
    //
    memcpy(outbuf + pos, data, datalen);
    pos += datalen;

    return pos;
}