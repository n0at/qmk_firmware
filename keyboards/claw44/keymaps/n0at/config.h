/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define MASTER_LEFT

// モッドタップの設定
#define TAPPING_TERM 175
#define PERMISSIVE_HOLD_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// LEADERキーの設定
#define LEADER_TIMEOUT 300
// #define LEADER_PER_KEY_TIMING

// #define OLED_FONT_H "keyboards/claw44/lib/glcdfont.c"

/* WS2812B RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 20
#define RGBLIGHT_SPLIT
#define RGBLED_SPLIT { 10, 10 }    // Number of LEDs

// The LEDs on the slave half go in reverse order
#define RGBLIGHT_LED_MAP {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10}

// #define MOUSEKEY_DELAY 150
// #define MOUSEKEY_INTERVAL 25