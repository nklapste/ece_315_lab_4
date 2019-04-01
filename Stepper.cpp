/*
 * Stepper.cpp
 *
 *  Created on: Nov 1, 2016
 *      Author: nem
 *  Modified on: Mar 13, 2019
 *  	Author: Nathan Klapstein
 */

#include <basictypes.h>
#include <pins.h>
#include <predef.h>
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>

#include <constants.h>
#include "Stepper.h"

Stepper::Stepper() {
	// TODO Auto-generated constructor stub
}

Stepper::~Stepper() {
	// TODO Auto-generated destructor stub
}

/**
 * Make the stepper motor take a specified number steps in the specified direction
 *
 * @param direction direction the steps will rotate in (CW=CLOCKWISE=0, CCW=COUNTER_CLOCKWISE=1)
 * @param steps the number of steps to take 
 */
void Stepper::Step(BYTE direction, WORD steps) {
	Enable(); // motor should only be on when moving
	// Insert Exercise 2 code here
	SetDirection(direction);

	printf("starting %d steps going direction %d\n", steps, direction); // TODO: debug

	// create #steps rising edges with the clk line to do #steps
	for (int i = 0; i < steps; i++) {
		STEPPER_CLK.clr();
		OSTimeDly(5); // wait 5 ticks
		STEPPER_CLK.set();
		OSTimeDly(5); // wait 5 ticks
	}
	printf("done %d steps on direction %d\n", steps, direction); // TODO: debug

	Disable(); // once movement is over turn the motor off
}

/**
 * Initialize the stepper motor with the specified step mode 
 * (half-step=STEPPER_MODE_HALF_STEP=0 or full-step=STEPPER_MODE_FULL_STEP=1)
 *
 * @param mode step mode (half-step=STEPPER_MODE_HALF_STEP=0 or full-step=STEPPER_MODE_FULL_STEP=1)
 */
void Stepper::Init(BYTE mode) {
	// Insert Exercise 2 code here
	STEPPER_ENABLE.function(PINJ2_37_GPIO);
	STEPPER_ENABLE.drive();
	Disable(); // initially disable using the stepper motor

	STEPPER_MODE.function(PINJ2_38_GPIO);
	STEPPER_MODE.drive();
	SetMode(mode);

	STEPPER_CLK.function(PINJ2_39_GPIO); // TODO investigate
	STEPPER_CLK.drive();
	STEPPER_CLK.clr();

	STEPPER_DIR.function(PINJ2_40_GPIO);
	STEPPER_DIR.drive();
}

/**
 * Enable (turn-on) the stepper motor
 *
 * @note updates the {@code state} to {@code STEPPER_ON}.
 */
void Stepper::Enable(void) {
	// Insert Exercise 2 code here
	STEPPER_ENABLE.set();
	state = STEPPER_ON;
}

/**
 * Disable (turn-off) the stepper motor
 *
 * @note updates the {@code state} to {@code STEPPER_OFF}.
 */
void Stepper::Disable(void) {
	// Insert Exercise 2 code here
	STEPPER_ENABLE.clr();
	state = STEPPER_OFF;
}

/**
 * Set the direction of the stepper motor turns on a step 
 * (CW=CLOCKWISE=0, CCW=COUNTER_CLOCKWISE=1)
 *
 * @param dir direction to turn the stepper motor on a step (CW=CLOCKWISE=0, CCW=COUNTER_CLOCKWISE=1)
 */
void Stepper::SetDirection(BYTE dir) {
	// Insert Exercise 2 code here
	direction = dir;
	STEPPER_DIR.set(direction);
}

/**
 * Get the direction of rotation of the stepper motor 
 * (CW=CLOCKWISE=1 or CCW=COUNTER_CLOCKWISE=0)
 */
BYTE Stepper::GetDirection(void) {
	return direction;
}

/**
 * Set the step mode of the stepper motor 
 * (half-step=STEPPER_MODE_HALF_STEP=0 or full-step=STEPPER_MODE_FULL_STEP=1)
 *
 * @param mode step mode (half-step=STEPPER_MODE_HALF_STEP=0 or full-step=STEPPER_MODE_FULL_STEP=1)
 */
void Stepper::SetMode(BYTE mode){
	// Insert Exercise 2 code here
	motor_mode = mode;
	STEPPER_MODE.set(motor_mode);
}

/**
 * Get the mode of the stepper's motor 
 * (half-step=STEPPER_MODE_HALF_STEP=0 or full-step=STEPPER_MODE_FULL_STEP=1)
 */
BYTE Stepper::GetMode(void) {
	return motor_mode;
}

/**
 * Get the state of the stepper motor 
 * (on=STEPPER_ON=1 or off=STEPPER_OFF=0)
 */
BYTE Stepper::GetState(void) {
	return state;
}
