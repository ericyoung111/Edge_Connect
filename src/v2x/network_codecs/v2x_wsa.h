/**
 * implements WSA header
 * 
 * @copyright Eric Young 2019-present
 */
#ifndef __V2X_WSA_H__
#define __V2X_WSA_H__

#include <stdint.h>
#include <vector>
#include <v2x_16093_common_structs.h>

// info element structure
struct v2x_wsa_info_elem {
    // repeat rate
    v2x_16093_common_repeatrate         repeatrate;

    // 3d location
    v2x_16093_common_3dlocation         threedlocation;

    // advertiser id
    v2x_16093_common_advertiserid       advertiserid;
};

struct v2x_wsa_service_info_elem {
    uint32_t                                    psid;
    int                                         channel_index;
    v2x_16093_common_psc                        psc;
    v2x_16093_common_ipv6addr                   service_ipv6addr;
    v2x_16093_common_service_port               service_port;
    v2x_16093_common_provider_macaddr           provider_macaddr;
    v2x_16093_common_rcpi_threshold             rcpi_threshold;
    v2x_16093_common_wsa_count_threshold        wsa_count_threshold;
    v2x_16093_common_wsa_count_threshold_intvl  wsa_count_threshold_intvl;
};

struct v2x_wsa_channel_info_elem {
    int                                 operating_class;
    int                                 channel_number;
    int                                 transmit_power_level;
    // boolean
    int                                 adaptable;
    int                                 datarate;
    v2x_16093_common_edca_parameters    edca_parameters;
    channel_access_80211                channel_access;
};

struct v2x_wra_elem {
    int         router_lifetime;
    uint8_t     ipprefix[16];
    int         prefixlen;
    uint8_t     defaultgw[16];
    uint8_t     primarydns[16];
    uint8_t     gwmac[6];
    int         valid_gwmac;
};

struct v2x_wsa_packet {
    int                                     wsa_version;
    int                                     wsa_id;
    int                                     content_count;

    bool                                    has_info_elem;
    v2x_wsa_info_elem                       info_elem;

    bool                                    has_service_info_elem;
    std::vector<v2x_wsa_service_info_elem>  service_info_elem;

    bool                                    has_channel_info_elem;
    std::vector<v2x_wsa_channel_info_elem>  channel_info_elem;

    bool                                    has_wra_elem;
    v2x_wra_elem                            wra_elem;
};

#endif
