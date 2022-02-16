/*
 * =======================================================================================================================
 * This file is part of Darkroom.
 * Darkroom is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Darkroom is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Darkroom.
 * If not, see <https://www.gnu.org/licenses/>.
 * =======================================================================================================================
 *
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
#define TIMERMODEBUTTONPIN  36    // Orange
#define TIMERSIDEBUTTONPIN  34    // Red
#define SOURCEMODEBUTTONPIN 32    // Brown
#define SOURCESIDEBUTTONPIN 30    // Black
#define TARGETMODEBUTTONPIN 28    // White
#define TARGETSIDEBUTTONPIN 26    // Grey
#define BRIGHTNESSBUTTONPIN 24    // Purple
#define EXECUTEBUTTONPIN    22    // Blue

// Cable C
//  LED signals
// ================
#define ENCODEREBUTTONPIN   23    // TODO put a wire in and not colour
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
