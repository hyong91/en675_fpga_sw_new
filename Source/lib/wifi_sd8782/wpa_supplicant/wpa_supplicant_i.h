/*
 * wpa_supplicant - Internal definitions
 * Copyright (c) 2003-2006, Jouni Malinen <j@w1.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#ifndef WPA_SUPPLICANT_I_H
#define WPA_SUPPLICANT_I_H

#include "driver.h"
#include "ewl.h"

struct wpa_scan_result;
struct wpa_sm;
struct wpa_supplicant;

/*
 * Forward declarations of private structures used within the ctrl_iface
 * backends. Other parts of wpa_supplicant do not have access to data stored in
 * these structures.
 */
struct ctrl_iface_priv;
//struct ctrl_iface_global_priv;
//struct ctrl_iface_dbus_priv;

/**
 * struct wpa_interface - Parameters for wpa_supplicant_add_iface()
 */
struct wpa_interface {

	/**
	 * driver - Driver interface name, or %NULL to use the default driver
	 */
	const char *driver;

	/**
	 * driver_param - Driver interface parameters
	 *
	 * If a configuration file is not used, this variable can be used to
	 * set the driver_param parameters that would have otherwise been read
	 * from the configuration file. If both confname and driver_param are
	 * set, driver_param is used to override the value from configuration
	 * file.
	 */
	//const char *driver_param;

	/**
	 * ifname - Interface name
	 */
	//const char *ifname;

};

/**
 * struct wpa_params - Parameters for wpa_supplicant_init()
 */
struct wpa_params {
	/**
	 * daemonize - Run %wpa_supplicant in the background
	 */
	int daemonize;

	/**
	 * wait_for_interface - Wait for the network interface to appear
	 *
	 * If set, %wpa_supplicant will wait until all the configured network
	 * interfaces are available before starting processing. Please note
	 * that in many cases, a better alternative would be to start
	 * %wpa_supplicant without network interfaces and add the interfaces
	 * dynamically whenever they become available.
	 */
	int wait_for_interface;
	/**
	 * wpa_debug_level - Debugging verbosity level (e.g., MSG_INFO)
	 */
	int wpa_debug_level;
};

/**
 * struct wpa_global - Internal, global data for all %wpa_supplicant interfaces
 *
 * This structure is initialized by calling wpa_supplicant_init() when starting
 * %wpa_supplicant.
 */
struct wpa_global {
	struct wpa_supplicant *ifaces;
	struct wpa_params params;
};

/**
 * struct wpa_supplicant - Internal data for wpa_supplicant interface
 *
 * This structure contains the internal data for core wpa_supplicant code. This
 * should be only used directly from the core code. However, a pointer to this
 * data is used from other files as an arbitrary context pointer in calls to
 * core functions.
 */
struct wpa_supplicant {
	//struct wpa_supplicant *next;
	unsigned char own_addr[ETH_ALEN];
	struct wpa_config *conf;
	int countermeasures;
	u8 bssid[ETH_ALEN];
	u8 pending_bssid[ETH_ALEN]; /* If wpa_state == WPA_ASSOCIATING, this
				     * field contains the targer BSSID. */
	int reassociate; /* reassociation requested */
	int disconnected; /* all connections disabled; i.e., do no reassociate
			   * before this has been cleared */
	struct wpa_ssid *current_ssid;
	int current_id;

	/* Selected configuration (based on Beacon/ProbeResp WPA IE) */
	int pairwise_cipher;
	int group_cipher;
	int key_mgmt;
	int mgmt_group_cipher;

	void *drv_priv; /* private data used by driver_ops */

	struct wpa_ssid *prev_scan_ssid; /* previously scanned SSID;
					  * NULL = not yet initialized (start
					  * with broadcast SSID)
					  * BROADCAST_SSID_SCAN = broadcast
					  * SSID was used in the previous scan
					  */
#define BROADCAST_SSID_SCAN ((struct wpa_ssid *) 1)

	struct wpa_scan_result *scan_results;
	int num_scan_results;

	struct wpa_driver_ops *driver;
	//struct ctrl_iface_priv *ctrl_iface;

	wpa_states wpa_state;
	int new_connection;
	int reassociated_connection;
	int keys_cleared;

	int scan_req; /* manual scan request; this forces a scan even if there
		       * are no enabled networks in the configuration */
	int scan_res_tried; /* whether ap_scan=1 mode has tried to fetch scan
			     * results without a new scan request; this is used
			     * to speed up the first association if the driver
			     * has already available scan results. */
#define MAX_DISCONNECT_CNT 3			     
    int disconnect_cnt; //count when connect is failed. 
    int scan_state; /* 0: is finished, 1 : scanning, is used in ewl_scan()	*/	     
    void (*scan_complete_cb)(void);
    void (*connect_failed)(void);
    void (*disconnect_cb)(int); //called when disconnect_cnt;
};


/* wpa_supplicant.c */
void wpa_supplicant_cancel_scan(struct wpa_supplicant *wpa_s);

const char * wpa_supplicant_state_txt(int state);
int 
wpa_supplicant_driver_init(struct wpa_supplicant *wpa_s);

int wpa_supplicant_set_suites(struct wpa_supplicant *wpa_s,
			      struct wpa_scan_result *bss,
			      struct wpa_ssid *ssid,
			      u8 *wpa_ie, size_t *wpa_ie_len);
void wpa_supplicant_associate(struct wpa_supplicant *wpa_s,
			      struct wpa_scan_result *bss,
			      struct wpa_ssid *ssid);
void wpa_supplicant_set_non_wpa_policy(struct wpa_supplicant *wpa_s,
				       struct wpa_ssid *ssid);
void wpa_supplicant_initiate_eapol(struct wpa_supplicant *wpa_s);
int wpa_supplicant_get_scan_results(struct wpa_supplicant *wpa_s);
void wpa_clear_keys(struct wpa_supplicant *wpa_s, const u8 *addr);
void wpa_supplicant_req_auth_timeout(struct wpa_supplicant *wpa_s,
				     int sec, int usec);
void wpa_supplicant_set_state(struct wpa_supplicant *wpa_s, wpa_states state);
struct wpa_ssid * wpa_supplicant_get_ssid(struct wpa_supplicant *wpa_s);
void wpa_supplicant_cancel_auth_timeout(struct wpa_supplicant *wpa_s);
void wpa_supplicant_deauthenticate(struct wpa_supplicant *wpa_s,
				   int reason_code);
void wpa_supplicant_disassociate(struct wpa_supplicant *wpa_s,
				 int reason_code);
void wpa_supplicant_req_scan(struct wpa_supplicant *wpa_s, int sec, int usec);


struct wpa_supplicant * wpa_supplicant_init(void);
//int wpa_supplicant_run(struct wpa_global *global);
inline void
wpa_supplicant_deinit(struct wpa_global *global);

/* events.c */
void wpa_supplicant_mark_disassoc(struct wpa_supplicant *wpa_s);

/* driver_ops */
static inline void * wpa_drv_init(struct wpa_supplicant *wpa_s,
				  const char *ifname)
{
	if (wpa_s->driver->init) {
		return wpa_s->driver->init(wpa_s, ifname);
	}
	return NULL;
}

static inline void wpa_drv_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->deinit)
		wpa_s->driver->deinit(wpa_s->drv_priv);
}

static inline int wpa_drv_set_param(struct wpa_supplicant *wpa_s,
				    const char *param)
{
	if (wpa_s->driver->set_param)
		return wpa_s->driver->set_param(wpa_s->drv_priv, param);
	return 0;
}

static inline int wpa_drv_set_drop_unencrypted(struct wpa_supplicant *wpa_s,
					       int enabled)
{
	if (wpa_s->driver->set_drop_unencrypted) {
		return wpa_s->driver->set_drop_unencrypted(wpa_s->drv_priv,
							   enabled);
	}
	return -1;
}

static inline int wpa_drv_set_countermeasures(struct wpa_supplicant *wpa_s,
					      int enabled)
{
	if (wpa_s->driver->set_countermeasures) {
		return wpa_s->driver->set_countermeasures(wpa_s->drv_priv,
							  enabled);
	}
	return -1;
}

static inline int wpa_drv_set_auth_alg(struct wpa_supplicant *wpa_s,
				       int auth_alg)
{
	if (wpa_s->driver->set_auth_alg) {
		return wpa_s->driver->set_auth_alg(wpa_s->drv_priv,
						   auth_alg);
	}
	return -1;
}

static inline int wpa_drv_set_wpa(struct wpa_supplicant *wpa_s, int enabled)
{
	if (wpa_s->driver->set_wpa) {
		return wpa_s->driver->set_wpa(wpa_s->drv_priv, enabled);
	}
	return 0;
}

static inline int wpa_drv_associate(struct wpa_supplicant *wpa_s,
				    struct wpa_driver_associate_params *params)
{
	if (wpa_s->driver->associate) {
		return wpa_s->driver->associate(wpa_s->drv_priv, params);
	}
	return -1;
}

static inline int wpa_drv_scan(struct wpa_supplicant *wpa_s, const u8 *ssid,
			       size_t ssid_len)
{
	if (wpa_s->driver->scan) {
		return wpa_s->driver->scan(wpa_s->drv_priv, ssid, ssid_len);
	}
	return -1;
}

static inline int wpa_drv_get_scan_results(struct wpa_supplicant *wpa_s,
					   struct wpa_scan_result *results,
					   size_t max_size)
{
	if (wpa_s->driver->get_scan_results) {
		return wpa_s->driver->get_scan_results(wpa_s->drv_priv,
						       results, max_size);
	}
	return -1;
}

static inline int wpa_drv_get_bssid(struct wpa_supplicant *wpa_s, u8 *bssid)
{
	if (wpa_s->driver->get_bssid) {
		return wpa_s->driver->get_bssid(wpa_s->drv_priv, bssid);
	}
	return -1;
}

static inline int wpa_drv_get_ssid(struct wpa_supplicant *wpa_s, u8 *ssid)
{
	if (wpa_s->driver->get_ssid) {
		return wpa_s->driver->get_ssid(wpa_s->drv_priv, ssid);
	}
	return -1;
}

static inline int wpa_drv_set_key(struct wpa_supplicant *wpa_s, wpa_alg alg,
				   const u8 *addr, int key_idx, int set_tx,
				   const u8 *seq, size_t seq_len,
				   const u8 *key, size_t key_len)
{
	if (wpa_s->driver->set_key) {
		wpa_s->keys_cleared = 0;
		return wpa_s->driver->set_key(wpa_s->drv_priv, alg, addr,
					      key_idx, set_tx, seq, seq_len,
					      key, key_len);
	}
	return -1;
}

static inline int wpa_drv_deauthenticate(struct wpa_supplicant *wpa_s,
					 const u8 *addr, int reason_code)
{
	if (wpa_s->driver->deauthenticate) {
		return wpa_s->driver->deauthenticate(wpa_s->drv_priv, addr,
						     reason_code);
	}
	return -1;
}

static inline int wpa_drv_disassociate(struct wpa_supplicant *wpa_s,
				       const u8 *addr, int reason_code)
{
	if (wpa_s->driver->disassociate) {
		return wpa_s->driver->disassociate(wpa_s->drv_priv, addr,
						   reason_code);
	}
	return -1;
}

static inline int wpa_drv_get_capa(struct wpa_supplicant *wpa_s,
				   struct wpa_driver_capa *capa)
{
	if (wpa_s->driver->get_capa) {
		return wpa_s->driver->get_capa(wpa_s->drv_priv, capa);
	}
	return -1;
}

static inline const char * wpa_drv_get_ifname(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->get_ifname) {
		return wpa_s->driver->get_ifname(wpa_s->drv_priv);
	}
	return NULL;
}


static inline int wpa_drv_mlme_setprotection(struct wpa_supplicant *wpa_s,
					     const u8 *addr, int protect_type,
					     int key_type)
{
	if (wpa_s->driver->mlme_setprotection)
		return wpa_s->driver->mlme_setprotection(wpa_s->drv_priv, addr,
							 protect_type,
							 key_type);
	return 0;
}

#endif /* WPA_SUPPLICANT_I_H */
