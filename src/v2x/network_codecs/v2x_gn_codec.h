/**
 *
 * implements Geonetworking codecs
 * 
 * spec: EN 302 636-4-1 V1.3.1
 * 
 * @copyright Eric Young 2019-present
 */
#ifndef __V2X_GN_CODEC_H__
#define __V2X_GN_CODEC_H__

// for uint8
#include <stdint.h>

enum geonet_station_type {
    GEONET_ST_UNKNOWN = 0,
    GEONET_ST_PEDESTRIAN,
    GEONET_ST_CYCLIST,
    GEONET_ST_MOPED,
    GEONET_ST_MOTOR_CYCLE,
    GEONET_ST_PASSENGER_CAR,
    GEONET_ST_BUS,
    GEONET_ST_LIGHT_TRUCK,
    GEONET_ST_HEAVY_TRUCK,
    GEONET_ST_TRAILER,
    GEONET_ST_SPECIAL_VEHICLE,
    GEONET_ST_TRAM,
    GEONET_ST_ROAD_SIDE_UNIT = 15,
};

// geonetworking addrress
struct geonet_addr {
    // 1 or 0
    int manual;
    enum geonet_station_type station_type;
    int reserved;
    uint8_t mid[6];
};

int v2x_gn_encode_geonet_addr(struct geonet_addr *addr, uint8_t *bufout, int pos, size_t bufsize);

#endif