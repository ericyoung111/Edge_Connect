/**
 * implements common types used in WSA / WSMP codec
 * 
 * @copyright Eric Young 2019-present
 */
#ifndef __V2X_16093_COMMON_STRUCTS_H__
#define __V2X_16093_COMMON_STRUCTS_H__

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

struct v2x_16093_common_repeatrate {
    int repeatrate;
    int valid;
};

struct v2x_16093_common_3dlocation {
    double latitude;
    double longitude;
    double elevation;
};

struct v2x_16093_common_advertiserid {
    char advertiser_utf8[32];
    int advertiser_len;
    int valid;
};

struct v2x_16093_common_psc {
    char psc_utf8[32];
    int psc_len;
    int valid;
};

struct v2x_16093_common_ipv6addr {
    uint8_t ipv6addr[16];
    int valid;
};

struct v2x_16093_common_service_port {
    int service_port;
    int valid;
};

struct v2x_16093_common_provider_macaddr {
    uint8_t provider_macaddr[6];
    int valid;
};

struct v2x_16093_common_rcpi_threshold {
    int rcpi_threshold;
    int valid;
};

struct v2x_16093_common_wsa_count_threshold {
    int wsa_count_threshold;
    int valid;
};

struct v2x_16093_common_wsa_count_threshold_intvl {
    int wsa_count_threshold_intvl;
    int valid;
};

struct v2x_16093_common_edca_parameter {
    int res;
    int aci;
    int acm;
    int aifsn;
    int ecwmax;
    int ecwmin;
    int txoplimit;
};

struct v2x_16093_common_edca_parameters {
    struct v2x_16093_common_edca_parameter ac_be;
    struct v2x_16093_common_edca_parameter ac_bk;
    struct v2x_16093_common_edca_parameter ac_vi;
    struct v2x_16093_common_edca_parameter ac_vo;
};

enum channel_access_80211 {
    CHANNEL_ACCESS_80211_CONTINUOUS = 0,
    CHANNEL_ACCESS_80211_ALTERNATING_SCH,
    CHANNEL_ACCESS_80211_ALTERNATING_CCH,
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

// info elem repeat rate
#define V2X_WSMP_IE_REPEAT_RATE 0x11
#define V2X_WSMP_IE_REPEAT_RATE_LEN 1

#endif