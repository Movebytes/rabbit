/**
 *  Copyright 2017 Movebytes Group
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
#ifndef _AML_TIMER_H_
#define _AML_TIMER_H_
#include <windows.h>
#include "Types.h"
namespace aml {
// Timer declaration
class Timer
{
private:
    U64 m_iStartTicks;
    U64 m_iPausedTicks;
    // Flags
    bool m_bPaused;
    bool m_bStarted;
public:
    // Default constructor
    Timer();
    // Start the timer
    void Start();
    // Stop and reset the timer
    void Stop();
    // Pause the timer
    void Pause();
    // Unpause the timer
    void Resume();
    // Return current ticks
    U64 GetTicks();
    // Check if timer is started
    bool IsStarted();
    // Chekc if timer is paused
    bool IsPaused();
}; // Timer
// Initialize default values
inline Timer::Timer()
{
	m_iStartTicks = 0;
    m_iPausedTicks = 0;
    m_bPaused = false;
    m_bStarted = false;
}
// Start the timer
inline void Timer::Start()
{
    // Mark that timer is started and not paused
    m_bStarted = true;
    m_bPaused = false;
    // Get ticks
	QueryPerformanceCounter((LARGE_INTEGER*) &m_iStartTicks);
    m_iPausedTicks = 0;
}
// Stop and reset the timer
inline void Timer::Stop()
{
    // Mark that timer is stoped
    m_bStarted = false;
    m_bPaused = false;
    // Clear ticks
    m_iStartTicks = 0;
    m_iPausedTicks = 0;
}
// Pause the timer
inline void Timer::Pause()
{
    if (m_bStarted && !m_bPaused)
    {
        // Mark that timer is paused
        m_bPaused = true;
        // Calculate paused ticks
        U64 iTempTicks = 0;
		QueryPerformanceCounter((LARGE_INTEGER*) &iTempTicks);
        m_iPausedTicks = iTempTicks - m_iStartTicks;
        // Clear start ticks
        m_iStartTicks = 0;
    }
}
// Unpause the timer
inline void Timer::Resume()
{
    if (m_bStarted && m_bPaused)
    {
        // Set that timer is unpaused
        m_bPaused = false;
        // Reset the starting ticks
        U64 iTempTicks = 0;
		QueryPerformanceCounter((LARGE_INTEGER*) &iTempTicks);
        m_iStartTicks = iTempTicks - m_iPausedTicks;
        // Reset the paused ticks
        m_iPausedTicks = 0;
    }
}
// Return current ticks
inline U64 Timer::GetTicks()
{
    U64 iTime = 0;
    if (m_bStarted)
    {
        if (m_bPaused)
        {
            iTime = m_iPausedTicks;
        }
        else
        {
            U64 iTempTicks = 0;
			QueryPerformanceCounter((LARGE_INTEGER*) &iTempTicks);
            iTime = iTempTicks - m_iStartTicks;
        }
    }
    return iTime;
}
// Check if timer is started
inline bool Timer::IsStarted()
{
    return m_bStarted;
}
// Chekc if timer is paused
inline bool Timer::IsPaused()
{
    return m_bPaused;
}
} // aml
#endif // _AML_TIMER_H_
