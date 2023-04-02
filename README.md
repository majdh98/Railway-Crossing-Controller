# Railway Crossing Controller - Embedded Networking
>  Authors: Ike Abioye, Majd Hamdan, Mubarak Idoko

> ENGS 62 - Microprocessors in Engineered Systems - Winter 2023 - Final Project

> March 2, 2023

## Overview

In this project, we design a finite state machine that controls a railway crossing. We use a ZYBO development board ([Digilent Zybo Z7](https://digilent.com/shop/zybo-z7-zynq-7000-arm-fpga-soc-development-board/?utm_source=google&utm_medium=cpc&utm_campaign=19550988445&utm_content=148947440350&utm_term=zybo%20fpga&gclid=CjwKCAjwrJ-hBhB7EiwAuyBVXVolngGttHRigcdFO4t2e8gi6MxvzEMENUg2RmE5M86mDmBZoEiSrBoCmeoQAvD_BwE)) to implement the state machine. The ZYBO board integrate a dual-core ARM Cortex-A9 processor (Zynq processor) with Xilinx 7-series Field Programmable Gate Array (FPGA) logic. We use the board to control LEDs, servo motor, potentiometer, and a WIFI module to mimic the following case.

## Case description
The crossing consists of a one-way road with an associated set of traffic lights, a blue maintenance light, a railway track with a gate, and a pedestrian crossing with two associated push buttons. Each crossing has a unique id.

Generally, when there are no trains, traffic is allowed to flow continuously for a minimum of 10 seconds. If a pedestrian pushes a crossing button, only after the 10 seconds are up and the red light is illuminated, pedestrians are given 3 seconds to cross the road. The traffic lights sequence on a 3 second interval between different colors.

The crossing communicates with a railway switching substation that holds a database of crossings and their status. When a train is arriving, the substation sends an “train arriving” message to the controller. The controller stops traffic flow and closes the gate. The substation monitors the railway line and informs the controller when the train has passed with a “clear” message; the controller then raises the gate, waits 3 seconds to ensure there are no pedestrians on the crosswalk, and allows traffic to flow with the appropriate traffic signals. While the traffic is stopped, pedestrians can freely cross the road.

Occasionally, a railway engineer may walk up to the crossing, insert a key, and manually close the crossing for maintenance; in this mode trains may still pass, but
the engineer may work on the crossing hardware without traffic flowing. When the key is turned, the controller stops the traffic, closes the gate, and flashes a blue light on the gate at 1 second intervals. A wheel at the side of the road can be used to manually raise and lower the gate. The engineer may manually initiate opening the crossing by use of his key.

## Implementation
- Use RGB (and yellow) LEDs on the board to represent the traffic signals and maintenance light. Lights normally sequence red-yellow-green-yellow-red. The traffic lights are off in maintenance mode.
- Use a Servo motor connected to the board on PMOD JA to control the gate with a full 90-degree swing (up/down).
- Use switches on the board to indicate Maintenance Mode/Clear and Train Arrival /Clear.
- Use buttons on the board for the pedestrian signal – one on each side of the road.
- Use a potentiometer for the wheel at the side of the road.
- Signify the gate status (open/closed), maintenance mode (entry/exit), and train status (arriving/clear) using a message on the screen.
- Use WIFI module to poll the “remote substation status database” 10 times per second to discover the train status. Used to add the capability for the substation to initiate and terminate maintenance mode
remotely, without the operator using a key.

## Content
- [Documentation](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/tree/main/Documentation): Contains documentation on the devices used in this project. All following interfaces were implemented following these documents.
- [led.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/led.h), [led.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/led.c): LED interface. Use Serial I/O, AXI GPIO, and processing system's GPIO to control the LEDs on the ZYBO board.
- [gic.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/gic.h), [gic.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/gic.c): GIC (General Interrupt Controller) module interface. Connect an interrupt handler to devices on the ZYBO board.
- [io.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/io.h), [io.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/io.c): Button and switches interface. Uses AXI GPIO for buttons & switches configuration and interrupt handling. Detect when a button or switch on the ZYBO board have been activated and run a callback() function (user choice) on receiving interrupts.
- [ttc.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/ttc.h), [ttc.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/ttc.c): Processing system Triple Timer Counter interface. initializes and uses the TTC timer to generate interrupts on desired intervals.
- [servo.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/servo.h), [servo.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/servo.c): Servo module interface. Uses AXI timers to generate a PWM (Pulse Width Modulation) signal to control and set the duty cycle of a servo motor connected to the ZYBO board on PMOD JA. Maintains the duty cycle the safe 90-degree limits of the servo motor. 
- [adc.h](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/adc.h), [adc.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/adc.c): Analog to Digital converter interface. Uses XADC (Xilinx Analog to Digital converter) to measure the processing system internal temperature and voltage. Uses XADC to read the value on a potentiometer connected to the ZYBO board on PMOD JA.
- [main.c](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/main.c): Implemnts the FSM. Uses UART to configure the WIFI module connected to the ZYBO board on PMOD JF, connect to WIFI, and communicate with a substation server to poll the station status. Uses the previous interfaces to control and LEDs, servo motor and potentiometer.

## Block Diagram
![Block Diagramt](https://github.com/majdh98/Railway-Crossing-Controller_Embedded-Networking/blob/main/Documentation/block_diagram.png)


