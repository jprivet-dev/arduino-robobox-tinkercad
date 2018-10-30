#ifndef _VARIABLES_H
#define _VARIABLES_H
#include <Arduino.h>

const int STOP = 0;
const int PLAY = 1;

const int DELAY_SHORT = 15;
const int DELAY_DEFAULT = 30;
const int DELAY_LONG = 100;
const int DELAY_WAIT = 500;
const int DELAY_1S = 1000;

const int ROBOT_ARM_LINK_0_PIN = 6;
const int ROBOT_ARM_LINK_1_PIN = 7;
const int BTN_SWITCH_PIN = 2;

const int LED_RED_PIN = 4;
const int LED_GREEN_PIN = 3;

int btnSwitchState = LOW;
int status = STOP;
bool robotIsInTheInitialPosition = false;

#endif