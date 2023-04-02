/*
 * adc.h -- The ADC module interface
 * Authors: Ike Abioye, Majd Hamdan, Mubarak Idoko
 *
 *
 * Uses XADC (Xilinx Analog to Digital converter) to measure the processing system internal temperature and voltage.
 * Uses XADC to read the value on a potentiometer conntected to the ZYBO board on PMOD JA.
 *
 */
#pragma once

#include <stdio.h>
#include "xadcps.h"
#include "xparameters.h"  	/* constants used by the hardware */
#include "xil_types.h"		/* types used by xilinx */

/*
 * initialize the adc module
 */
void adc_init(void);

/*
 * get the internal temperature in degree's centigrade
 */
float adc_get_temp(void);

/*
 * get the internal vcc voltage (should be ~1.0v)
 */
float adc_get_vccint(void);

/*
 * get the **corrected** potentiometer voltage (should be between 0 and 1v)
 */
float adc_get_pot(void);
