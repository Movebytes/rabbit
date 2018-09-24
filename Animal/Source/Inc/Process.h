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
#ifndef _AML_PROCESS_H_
#define _AML_PROCESS_H_
#include "Types.h"
#include "ProcessManager.h"
namespace aml {
// Forward declaration
class Process;
class ProcessManager;
// Typedefs
typedef std::shared_ptr<Process> FStrongProcessPtr;
typedef std::weak_ptr<Process> FWeakProcessPtr;
// Process class
class Process
{
	friend class ProcessManager;
public:
	enum EProcessState
	{
		ProcessStateUninitialized = 0,
		ProcessStateRemoved,
		ProcessStateRunning,
		ProcessStatePaused,
		ProcessStateSucceeded,
		ProcessStateFailed,
		ProcessStateAborted
	};
private:
	EProcessState m_state;
	FStrongProcessPtr m_pChild;
	// Change state
	void SetState(EProcessState state)
	{
		m_state = state;
	}
public:
	// Default constructor
	Process();
	// Default destructor
	virtual ~Process();
	// Functions for ending the process
	inline void Succeed();
	inline void Fail();
	// Pause
	inline void Pause();
	inline void UnPause();
	// Accessors
	EProcessState GetState() const 
	{
		return m_state;
	}
	bool IsAlive() const
	{
		return (m_state == ProcessStateRunning || m_state == ProcessStatePaused);
	}
	bool IsDead() const
	{
		return (m_state == ProcessStateSucceeded || m_state == ProcessStateFailed || m_state == ProcessStateAborted);
	}
	bool IsRemoved() const 
	{
		return (m_state == ProcessStateRemoved);
	}
	bool IsPaused() const
	{
		return (m_state == ProcessStatePaused);
	}
	// Child functions
	inline void AttachChild(FStrongProcessPtr pChild);
	FStrongProcessPtr RemoveChild();
	FStrongProcessPtr GetChild() const
	{
		return m_pChild;
	}
protected:
	// Have to override in subclass as needed
	virtual void Init() 
	{
		m_state = ProcessStateRunning;
	}
	virtual void Update(U64 iDelta) = 0;
	virtual void Success() {}
	virtual void Fail() {}
	virtual void Abort() {}
}; // Process
} // aml
#endif // _AML_PROCESS_H_