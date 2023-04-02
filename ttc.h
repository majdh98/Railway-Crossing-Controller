/*
 * ttc.h -- The TTC module interface
 * Authors: Ike Abioye, Majd Hamdan, Mubarak Idoko
 *
 *
 * Initialize and use ttc timer to generate interrupts every 1/frequency
 *
 * NOTE: The TTC hardware must be enabled (Timer 0 on the processing system) before it can be used!!
 * XPAR_XTTCPS_0_DEVICE_ID = device id
 * XPAR_XTTCPS_0_INTR = interrupt id
 * XTTCPS_IXR_INTERVAL_MASK = interrupt mask for interval mode
 * XTTCPS_OPTION_INTERVAL_MODE = interval mode mask for setting mode
 */
#pragma once

#include <stdio.h>
#include "xttcps.h"
#include "xparameters.h"  	/* constants used by the hardware */
#include "xil_types.h"		/* types used by xilinx */

/*
 * ttc_init -- initialize the ttc freqency and callback
 */
void ttc_init(u32 freq, void (*ttc_callback)(void));

/*
 * ttc_start -- start the ttc
 */
void ttc_start(void);

/*
 * ttc_stop -- stop the ttc
 */
void ttc_stop(void);

/*
 * ttc_close -- close down the ttc
 */
void ttc_close(void);
