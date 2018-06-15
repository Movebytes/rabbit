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
#include <memory>
#include "Types.h"
#include "ProcessManager.h"
namespace aml {
// Forward declaration
class Process;
class ProcessManager;
// Typedefs
typedef std::shared_ptr<Process> StrongProcessPtr;
typedef std::weak_ptr<Process> WeakProcessPtr;
// Process class
class Process
{
	friend class ProcessManager;
public:
	enum State
	{
		UNINITIALIZED = 0,
		REMOVED,
		RUNNING,
		PAUSED,
		SUCCEEDED,
		FAILED,
		ABORTED
	};
private:
	State m_state;
	StrongProcessPtr m_pChild;
	// Change state
	void SetState(State state)
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
	State GetState() const 
	{
		return m_state;
	}
	bool IsAlive() const
	{
		return (m_state == RUNNING || m_state == PAUSED);
	}
	bool IsDead() const
	{
		return (m_state == SUCCEEDED || m_state == FAILED || m_state == ABORTED);
	}
	bool IsRemoved() const 
	{
		return (m_state == REMOVED);
	}
	bool IsPaused() const
	{
		return (m_state == PAUSED);
	}
	// Child functions
	inline void AttachChild(StrongProcessPtr pChild);
	StrongProcessPtr RemoveChild();
	StrongProcessPtr GetChild() const
	{
		return m_pChild;
	}
protected:
	// Have to override in subclass as needed
	virtual void Init() 
	{
		m_state = RUNNING;
	}
	virtual void Update(U64 iDelta) = 0;
	virtual void Success() {}
	virtual void Fail() {}
	virtual void Abort() {}
}; // Process
} // aml
#endif // _AML_PROCESS_H_