/**
 * implements V2X_WSMP protocol
 * 
 * copyright Eric Young 2019-present
 */
#ifndef __V2X_WSMP_H__
#define __V2X_WSMP_H__

#include <stdint.h>

struct v2x_wsmp_channel {
    int chan;
    // even though, this is a bit, we use int for alignment
    int valid;
};

struct v2x_wsmp_txpower {
    int txpower;
    int valid;
};

struct v2x_wsmp_datarate {
    int datarate;
    int valid;
};

#define V2X_WSMP_SUBTYPE_DEFAULT 0
#define V2X_WSMP_VERSION_CUR 3

// info elem chan
#define V2X_WSMP_IE_CHAN 0x0F

#define V2X_WSMP_IE_CHAN_LEN 1

// info elem rate
#define V2X_WSMP_IE_RATE 0x10

#define V2X_WSMP_IE_RATE_LEN 1

// info elem txpow
#define V2X_WSMP_IE_TXPOW 0x04

#define V2X_WSMP_IE_TXPOW_LEN 1

struct v2x_wsmp_packet {
    int subtype;
    int options;
    int wsmp_version;
    struct v2x_wsmp_channel chan;
    struct v2x_wsmp_txpower txpow;
    struct v2x_wsmp_datarate rate;
    int tpid;
    uint32_t psid;
    int wsmplen;
};

int v2x_wsmp_encode(const struct v2x_wsmp_packet *pkt, uint8_t *data, size_t datalen, uint8_t *outbuf);
int v2x_wsmp_decode(struct v2x_wsmp_packet *packet, uint8_t *datain, size_t datasize, uint8_t *wsmdata);

#endif