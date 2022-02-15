/*
 * Configuration.h
 *
 * Symbols mapping the wiring, settings and various indicators
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Module connection pins (Digital Pins ONLY!)
//      Symbol              Pin  // Wire color
// =============================================

// Cable A
//  LED Displays and encoder
// =========================
#define ROTARYENCODERPINA    2    // Brown
#define ROTARYENCODERPINB    3    // Black
#define TIMERCLK             8    // White
#define TIMERDIO             9    // Grey
#define SOURCECLK           10    // Purple
#define SOURCEDIO           11    // Blue
#define TARGETCLK           12    // Green
#define TARGETDIO           13    // Yellow

// Cable B
//  Buttons signals
// ================
#define TIMERMODEBUTTONPIN  22    // Orange
#define TIMERSIDEBUTTONPIN  24    // Red
#define SOURCEMODEBUTTONPIN 26    // Brown
#define SOURCESIDEBUTTONPIN 28    // Black
#define TARGETMODEBUTTONPIN 30    // White
#define TARGETSIDEBUTTONPIN 32    // Grey
#define BRIGHTNESSBUTTONPIN 34    // Purple
#define EXECUTEBUTTONPIN    36    // Blue

// Cable C
//  LED signals
// ================
#define TIMERMODEBUTTONLED  25    // Black
#define TIMERSIDEBUTTONLED  27    // White
#define SOURCEMODEBUTTONLED 29    // Grey
#define SOURCESIDEBUTTONLED 31    // Brown
#define TARGETMODEBUTTONLED 33    // Blue
#define TARGETSIDEBUTTONLED 35    // Green
#define BRIGHTNESSBUTTONLED 37    // Yellow

#define BEEPER              53    // Orange (internal short cable)
#define RELAYENLARGER       52    // (internal short cable)

// Cable D
//  LED grounds (just a collector that eventually lands into ground)

// Cable E
//  Various grounds (just a collector that eventually lands into ground)
//  and Power
//        5V      Red
//        3,3V    Brown
//        Ground  Black

// Settings
#define TIMERENCODERMIN    -1
#define TIMERENCODERMAX    60
#define TIMERENCODERSTART   0
#define SIZEENCODERMIN     -1
#define SIZEENCODERMAX    100
#define SIZERENCODERSTART   0
#define ENCODERLEFTMAX     99

// array addresses
#define TIMER_UI       0
#define SOURCE_UI      1
#define TARGET_UI      2

#endif /* CONFIGURATION_H */
