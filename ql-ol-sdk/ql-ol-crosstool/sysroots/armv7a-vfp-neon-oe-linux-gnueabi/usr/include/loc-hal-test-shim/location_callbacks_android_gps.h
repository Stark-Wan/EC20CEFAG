/* Copyright (c) 2013-2014 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 */

#ifndef LOCATION_CALLBACKS_ANDROID_GPS_H
#define LOCATION_CALLBACKS_ANDROID_GPS_H

#include "hardware/gps.h"

void test_android_gps_location_cb (GpsLocation * location);
void test_android_gps_status_cb (GpsStatus * status);
void test_android_gps_sv_status_cb (GpsSvStatus * sv_info);
void test_android_gps_nmea_cb (GpsUtcTime timestamp, const char *nmea, int length);
void test_android_gps_set_capabilities_cb (uint32_t capabilities);
void test_android_gps_xtra_time_req_cb ();
void test_android_gps_xtra_download_req_cb ();
void test_android_agps_status_cb (AGpsStatus * status);
void test_android_gps_ni_notify_cb(GpsNiNotification *notification);

void test_android_gps_acquire_wakelock_cb ();
void test_android_gps_release_wakelock_cb ();
pthread_t test_android_gps_create_thread_cb (const char *name, void (*start) (void *),
                                     void *arg);
#ifdef TEST_ULP
void test_ulp_request_phone_context_cb(UlpPhoneContextRequest *req);
void test_ulp_network_location_request_cb(UlpNetworkRequestPos* req);
#endif /* TEST_ULP */
#endif //LOCATION_CALLBACKS_ANDROID_GPS_H
