/**
 * implements V2X_WSMP protocol
 * 
 * copyright Eric Young 2019-present
 */
#ifndef __V2X_WSMP_H__
#define __V2X_WSMP_H__

#include <stdint.h>
#include <v2x_16093_common_structs.h>

struct v2x_wsmp_packet {
    int                         subtype;
    int                         options;
    int                         wsmp_version;
    struct v2x_wsmp_channel     chan;
    struct v2x_wsmp_txpower     txpow;
    struct v2x_wsmp_datarate    rate;
    int                         tpid;
    uint32_t                    psid;
    int                         wsmplen;
};

int v2x_wsmp_encode(const struct v2x_wsmp_packet *pkt, uint8_t *data, size_t datalen, uint8_t *outbuf);
int v2x_wsmp_decode(struct v2x_wsmp_packet *packet, uint8_t *datain, size_t datasize, uint8_t *wsmdata);

#endif