/**
 *  Copyright 2018 Movebytes Group
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#ifndef _AML_MACROS_H_
#define _AML_MACROS_H_
#include "Constants.h"
// Max and min
#define AML_MIN(a, b) (a < b ? a : b)
#define AML_MAX(a, b) (a > b ? b : a)
// Swap
#define AML_SWAP(a, b, t) { t = a; a = b; b = t; }
// Range
#define AML_RAND_RANGE(x, y) (x + (rand() % (y - x + 1))
// Close to zero
#define AML_IS_CLOSE_TO_ZERO(a) (a < EPSILON_E4 && a >= 0.0f)
// Deg/Rad
#define AML_DEG_TO_RAD(ang)  (ang * PI / 180.0f)
#define AML_RAD_TO_DEG(rads) (rads * 180.0f / PI)
// Safe delete
#define AML_DELETE(p) { if (p) { delete (p); (p) = nullptr; } }
// Convert to wide string
#define AML_TEXT(text) L ## text
#define AML_RUNTIME_TEXT(text) AML_TEXT(text)
#endif // _AML_MACROS_H_