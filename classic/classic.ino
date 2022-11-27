/*
 * Sample sketch which makes the Arduino to impersonate a Classic Controller.
 *
 * Use a PushButton connected to the digital pin 2 and GND. It will trigger
 * a D-Pad RIGHT button press of the impersonated Classic Controller.
 *
 * Copyright (c) 2011 Peter Brinkmann (peter.brinkmann@gmail.com)
 *
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 * 
 * Changes: ©Akerasoft 2022
 */

#include "Wire.h" // This seems redundant, but we need to declare this
                  // dependency in the pde file or else it won't be included
                  // in the build.

#include "wiimote.h"

// Classic Controller Buttons
int bdl = 0; // D-Pad Left state
int bdr = 0; // D-Pad Right state
int bdu = 0; // D-Pad Up state
int bdd = 0; // D-Pad Down state
int ba = 0; // A button state
int bb = 0; // B button state
int bx = 0; // X button state
int by = 0; // Y button state
int bl = 0; // L button state
int br = 0; // R button state
int bm = 0; // MINUS button state
int bp = 0; // PLUS button state
int bhome = 0; // HOME button state
int bzl = 0; // ZL button state
int bzr = 0; // ZR button state

/*
 * Analog Buttons.
 * They are initialized with center values from the calibration buffer.
 */
byte lx = calbuf[2]>>2;
byte ly = calbuf[5]>>2;
byte rx = calbuf[8]>>3;
byte ry = calbuf[11]>>3;

#define PIN_SELECT 2
#define PIN_START  3
#define PIN_UP     4
#define PIN_DOWN   5
#define PIN_LEFT   6
#define PIN_RIGHT  7
#define PIN_B      8
#define PIN_A      9
#define PIN_HOME   10

// Wiimote button data stream
byte *stream_callback(byte *buffer) {
	wiimote_write_buffer(buffer, bdl, bdr, bdu, bdd, ba, bb, bx, by, bl, br,
			bm, bp, bhome, lx, ly, rx, ry, bzl, bzr);

	return buffer;
}

// Setup - ©Akerasoft 2022
void setup() {
	// Set PushButton pins as input, turning pull-up on
	pinMode(PIN_SELECT, INPUT);
	digitalWrite(PIN_SELECT, HIGH);

  pinMode(PIN_START, INPUT);
  digitalWrite(PIN_START, HIGH);

  pinMode(PIN_UP, INPUT);
  digitalWrite(PIN_UP, HIGH);

  pinMode(PIN_DOWN, INPUT);
  digitalWrite(PIN_DOWN, HIGH);

  pinMode(PIN_LEFT, INPUT);
  digitalWrite(PIN_LEFT, HIGH);

  pinMode(PIN_RIGHT, INPUT);
  digitalWrite(PIN_RIGHT, HIGH);

  pinMode(PIN_B, INPUT);
  digitalWrite(PIN_B, HIGH);

  pinMode(PIN_A, INPUT);
  digitalWrite(PIN_A, HIGH);

  pinMode(PIN_HOME, INPUT);
  digitalWrite(PIN_HOME, HIGH);

	// Prepare wiimote communications
	wiimote_stream = stream_callback;
	wiimote_init();
}

// Loop - ©Akerasoft 2022
void loop() {
	bdl = !digitalRead(PIN_LEFT);
  bdr = !digitalRead(PIN_RIGHT);
  bdu = !digitalRead(PIN_UP);
  bdd = !digitalRead(PIN_DOWN);

  bb = !digitalRead(PIN_B);
  ba = !digitalRead(PIN_A);
  bm = !digitalRead(PIN_SELECT);
  bp = !digitalRead(PIN_START);
  
  bhome = !digitalRead(PIN_HOME);
	delay(50);
}
