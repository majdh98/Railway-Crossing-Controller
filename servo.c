/* servo.c -- module implementing servo.h
* Authors: Ike Abioye, Majd Hamdan, Mubarak Idoko
*
*
* Uses AXI timers 0 and 1 to generate a PWM signal to control and set the duty cycle of a servo motor
*
*/

#include "servo.h"

static XTmrCtr psTmr;

/*
 * Initialize the servo. Uses AXI timer to set the duty cycle to 7.5%.
 */
void servo_init(void) {
    // initialize the timer
    // psTmr = XTmrCtr_LookupConfig(XPAR_TMRCTR_0_DEVICE_ID);
    if (XTmrCtr_Initialize(&psTmr, XPAR_AXI_TIMER_0_DEVICE_ID) != XST_SUCCESS){
		printf("Unable to initilize PS timer");
		fflush(stdout);
	}

    // stop both timers
    XTmrCtr_Stop(&psTmr, 0);
	XTmrCtr_Stop(&psTmr, 1);

    // set options for both timers
    XTmrCtr_SetOptions(&psTmr, 0, XTC_PWM_ENABLE_OPTION | XTC_DOWN_COUNT_OPTION | XTC_EXT_COMPARE_OPTION);
	XTmrCtr_SetOptions(&psTmr, 1, XTC_PWM_ENABLE_OPTION | XTC_DOWN_COUNT_OPTION | XTC_EXT_COMPARE_OPTION);

    servo_set(MIDPOINT);
}

/*
 * Uses AXI timer to change the dutycycle of the servo
 * Protects servo motor from operating outside the safe 90-degree limits (MINPOINT to MAXPOINT)
 */
void servo_set(double dutycycle) {

    u32 HighTime;

    // safety and testing
    if (dutycycle > MAXPOINT){
        dutycycle = MAXPOINT;
        printf("max limit exceeded\n");
        fflush(stdout);
    } else if (dutycycle < MINPOINT){
        dutycycle = MINPOINT;
        printf("min limit exceeded\n");
        fflush(stdout);
    }

    // update the high time based on the duty cycle
    HighTime = (dutycycle * PERIOD)/100;

    // set reset value for both timers
    XTmrCtr_SetResetValue(&psTmr, 0, PERIOD);
    XTmrCtr_SetResetValue(&psTmr, 1, HighTime);

	// start both timers
    XTmrCtr_Start(&psTmr, 0);
	XTmrCtr_Start(&psTmr, 1);

}
