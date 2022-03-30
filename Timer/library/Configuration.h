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
#define ROTARYENCODERPINA    2    // Orange
#define ROTARYENCODERPINB    3    // Yellow
#define TIMERCLK             4    // Green
#define TIMERDIO             5    // Blue
#define TARGETCLK            6    // Purple
#define TARGETDIO            7    // Grey
#define SOURCECLK            8    // White
#define SOURCEDIO            9    // Black

// Cable B
//  Buttons signals
// ================
#define TIMERSIDEBUTTONPIN  36    // Orange
#define TIMERMODEBUTTONPIN  38    // Yellow
#define SOURCESIDEBUTTONPIN 40    // Green
#define SOURCEMODEBUTTONPIN 42    // Blue
#define TARGETSIDEBUTTONPIN 44    // Purple
#define TARGETMODEBUTTONPIN 46    // Grey
#define BRIGHTNESSBUTTONPIN 48    // White
#define EXECUTEBUTTONPIN    50    // Black

// Cable C
//  LED signals
// ================
#define ENCODEREBUTTONPIN   37    // Orange
#define TIMERMODEBUTTONLED  39    // Yellow
#define TIMERSIDEBUTTONLED  41    // Green
#define SOURCEMODEBUTTONLED 43    // Blue
#define SOURCESIDEBUTTONLED 45    // Purple
#define TARGETMODEBUTTONLED 47    // Grey
#define TARGETSIDEBUTTONLED 49    // White
#define BRIGHTNESSBUTTONLED 51    // Black


#define BEEPER              53    // Brown (internal short cable)
#define RELAYENLARGER       52    // Brown (internal long cable)

// Cable D
//  LED grounds (just a collector that eventually lands into ground)
// Orange: ground
// All following cables goes to a dedicated 2kΩ resistor, then ground
// Yellow: TIMERMODEBUTTONLED
// Green:  TIMERSIDEBUTTONLED
// Blue;   SOURCEMODEBUTTONLED
// Purple: SOURCESIDEBUTTONLED
// Grey:   TARGETMODEBUTTONLED
// White:  TARGETSIDEBUTTONLED
// Black:  BRIGHTNESSBUTTONLED

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
#define BRIGHTNESS_UI  3

#endif /* CONFIGURATION_H */
