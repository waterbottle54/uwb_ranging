/*
 * libdeca - UWB Library for Qorvo/Decawave DW3000
 *
 * Copyright (C) 2016 - 2024 Bruno Randolf (br@einfach.org)
 *
 * This source code is licensed under the GNU Lesser General Public License,
 * Version 3. See the file LICENSE.txt for more details.
 */

#ifndef DECA_RANGING
#define DECA_RANGING

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "dwmac.h"

/** TWR_PROCESSING_DELAY: the processing delay may need to be increased for
 * different processor and IRQ handling speeds */
#define TWR_PROCESSING_DELAY 600 /* us */
#define TWR_FAILED_VALUE	 UINT16_MAX
#define TWR_OK_VALUE		 (UINT16_MAX - 1)
#define TWR_MSG_GROUP		 0x20

typedef void (*twr_cb_t)(uint64_t src, uint64_t dst, uint16_t dist,
						 uint16_t num);

/** Initialize TWR with processing delay */
void twr_init(uint32_t processing_delay_us, bool send_report);
/** Start DS-TWR (Double Sided - Two Way Ranging) bsequence to ancor */
bool twr_start(uint64_t dst);
/** Start SS-TWR (Single Sided - Two Way Ranging) sequence to ancor */
bool twr_start_ss(uint64_t dst);
bool twr_in_progress(void);
void twr_cancel(void);
void twr_set_observer(twr_cb_t cb);
uint16_t twr_get_cnum(void);
uint64_t twr_get_source_mac(void);

void twr_handle_message(const struct rxbuf* rx);
double twr_distance_calculation_dtu(uint32_t poll_rx_ts, uint32_t resp_tx_ts,
									uint32_t final_rx_ts, uint32_t Ra,
									uint32_t Da);

#endif
