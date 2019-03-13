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

const char * AppName="Put your name here";




Stepper myStepper;
Keypad myKeypad;

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

    myStepper.Init(STEPPER_MODE_FULL_STEP);

    iprintf("Application started\n");
    while (1) {

    	// exercise 2 example test code
    	myStepper.SetMode(STEPPER_MODE_FULL_STEP);
    	myStepper.Step(COUNTER_CLOCKWISE, STEPS_PER_ROTATION_FULL_STEP_MODE * 2);
    	myStepper.Step(CLOCKWISE, STEPS_PER_ROTATION_FULL_STEP_MODE * 2);
    	OSTimeDly(TICKS_PER_SECOND);

    	myStepper.SetMode(STEPPER_MODE_FULL_STEP);
    	myStepper.Step(CLOCKWISE, STEPS_PER_ROTATION_HALF_STEP_MODE);
    	myStepper.Step(COUNTER_CLOCKWISE, STEPS_PER_ROTATION_HALF_STEP_MODE * 2);
        OSTimeDly(TICKS_PER_SECOND);

        // exercise 3 example test code
        // Most of the stepper settings will be changed by the keypad ISR
        // myStepper.SetMode(STEPPER_MODE_FULL_STEP);
        // myStepper.Step(CLOCKWISE, STEPS_PER_ROTATION_FULL_STEP_MODE * 200);
        //OSTimeDly(TICKS_PER_SECOND);

    }
}
