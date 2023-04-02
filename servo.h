/*
 * servo.h -- The servo module interface
 * Authors: Ike Abioye, Majd Hamdan, Mubarak Idoko
 *
 *
 * Uses AXI timers 0 and 1 to generate a PWM signal to control and set the duty cycle of a servo motor
 *
 */
#pragma once

#include <stdio.h>
#include "xtmrctr.h"
#include "xparameters.h"  	/* constants used by the hardware */
#include "xil_types.h"		/* types used by xilinx */

// hardware
#define CLOCK_FREQ 50000000

// timer 0 settings
#define PERIOD 1000000 // 20ms period (Timer 0)
#define PERIOD_MS 20 // 20ms period (Timer 0)

// Motor range
#define MINPOINT ((double)5)
#define MAXPOINT ((double)10.75)
#define MIDPOINT ((double)8.25)


/*
 * Initialize the servo. Uses AXI timer to set the duty cycle to 7.5%.
 */
void servo_init(void);

/*
 * Uses AXI timer to change the dutycycle of the servo
 * Protects servo motor from operating outside the safe 90-degree limits (MINPOINT to MAXPOINT)
 */
void servo_set(double dutycycle);
