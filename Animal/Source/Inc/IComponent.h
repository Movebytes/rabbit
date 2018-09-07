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
#ifndef _AML_ICOMPONENT_H_
#define _AML_ICOMPONENT_H_
#include "Types.h"
namespace aml {
// Declaration of component class
class IComponent
{
public:
	// Default destructor
	virtual ~IComponent();
	// Initialization of component data
	virtual HRESULT Init() = 0;
	// Updating component state
	virtual HRESULT Update(const F64 iDt) = 0;
	// Releasing component data
	virtual HRESULT Release() = 0;
}; // IComponent
// Default destructor
inline IComponent::~IComponent()
{
	// For any case
	Release();
}
} // aml
#endif // _AML_ICOMPONENT_H_