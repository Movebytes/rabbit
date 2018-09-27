#pragma once
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
#define WIN32_LEAN_AND_MEAN

// Include Windows headers
#include <windows.h>

// CRT's memory leak detection
#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

// Include C/C++ runtime headers
#include <stdlib.h>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

// Using
using std::vector;
using std::list;
using std::map;
using std::shared_ptr;
using std::weak_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;

// Typedefs
typedef std::wstring FString;

// Third party headers go here

// Include DirectX's headers
#include <DXUT.h>
#include <d3dx9tex.h>
#include <SDKmisc.h>

// Animal's headers
#include "Types.h"
#include "Constants.h"
#include "Macros.h"
#include "Logger.h"
#include "Exception.h"
