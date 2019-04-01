/*
 * lab4.cpp
 *
 *  Created on: Mar 13, 2019
 *      Author: Nathan Klapstein
 */

#include <predef.h>
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <smarttrap.h>
#include <taskmon.h>
#include <NetworkDebug.h>
#include "Keypad.h"
#include "error_wrapper.h"
#include "Stepper.h"
#include "Stepper.h"

extern "C" {
	void UserMain(void * pd);
}

const char * AppName="Nathan Klapstein, Thomas Lorincz";

Stepper myStepper;
Keypad myKeypad;

volatile int mode = 0;

/**
 * Interrupt service request handler.
 *
 * Updates the mode by one. Acceptable modes range from 0 to 3.
 */
void EdgePortISR1(void) {
	// Insert your ISR code here for exercise 3
	mode = (mode + 1) % 4;
}

#define OFF_1 0
#define ON_CW_FULL 1
#define OFF_2 2
#define ON_CCW_HALF 3

/**
 * Update the given stepper motor to reflect the state noted by the
 * {@code mode} variable.
 */
void UpdateStepperState(Stepper *stepper){
	switch(mode){
		case OFF_1:
			break;
		case ON_CW_FULL:
			stepper->SetMode(STEPPER_MODE_FULL_STEP);
			stepper->SetDirection(CLOCKWISE);
			break;
		case OFF_2:
			break;
		case ON_CCW_HALF:
			stepper->SetMode(STEPPER_MODE_HALF_STEP);
			stepper->SetDirection(COUNTER_CLOCKWISE);
			break;
		default:
			break;
	}
}

/**
 * Main execution
 */
void UserMain(void * pd) {
    InitializeStack();
    OSChangePrio(MAIN_PRIO);
    EnableAutoUpdate();
    StartHTTP();
    EnableTaskMonitor();

    #ifndef _DEBUG
    EnableSmartTraps();
    #endif

    #ifdef _DEBUG
    InitializeNetworkGDB_and_Wait();
    #endif

    // new keypad interrupt service request
    myKeypad.Init(KEYPAD_INT_MODE, &EdgePortISR1);

    myStepper.Init(STEPPER_MODE_FULL_STEP);

    iprintf("Application started: Lab 4\n");

    while (1) {
        // exercise 3
    	printf("%d mode\n", mode); // TODO: debug
		UpdateStepperState(&myStepper);
//		OSTimeDly(TICKS_PER_SECOND / 20);

		// only step the stepper motor on modes 1 (ON_CW_FULL) and 3 (ON_CCW_HALF)
    	if (mode == 1 || mode == 3) {
    		myStepper.Step(myStepper.GetDirection(), 2);
    	}
//    	OSTimeDly(10); // wait one tick
	}
}
