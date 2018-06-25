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
#ifndef _AML_LOGGER_H_
#define _AML_LOGGER_H_
#include <mutex>
#include <string>
#include <cstring>
#include <sstream>
#include <time.h>
#include "Types.h"
static std::mutex mutex;
namespace aml {
enum LogLevel
{
    LOG_LEVEL_ALL = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_NONE
};
// Declaration of log class
template <class T>
class Log
{
protected:
    // Logged messages
    std::ostringstream m_messages;
private:
    // Default copy constructor
    Log(const Log<T> & log)
        : m_messages(log.m_messages.str())
    {}
    // Copy and assign logger data
    Log & operator=(const Log<T> & log);
    static std::string ToString(LogLevel logLevel);
public:
    // Default constructor
    Log()
        : m_messages("")
    {}
    // Default desctructor
    virtual ~Log();
    std::ostringstream & GetStream(LogLevel logLevel);
    static LogLevel & GetReportingLevel();
}; // Log
// Return log level in string representation
template <class T>
std::string Log<T>::ToString(LogLevel logLevel)
{
    std::string strLogLevel;
    switch (logLevel)
    {
    case m3e::LOG_LEVEL_INFO:
        strLogLevel = "INFO";
        break;
    case m3e::LOG_LEVEL_WARNING:
        strLogLevel = "WARNING";
        break;
    case m3e::LOG_LEVEL_DEBUG:
        strLogLevel = "DEBUG";
        break;
    case m3e::LOG_LEVEL_ERROR:
        strLogLevel = "ERROR";
        break;
    default:
        strLogLevel = "UNKNOWN";
    }
    return strLogLevel;
} // toString
// Return logged messages
template <class T>
std::ostringstream & Log<T>::GetStream(LogLevel logLevel)
{
    time_t t = time(0);   // get time now
    const S32 BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
	strftime(buffer, BUFFER_SIZE, "%T", localtime(&t));
	// To replace \n
	buffer[strlen(buffer) - 1] = '\0';
    m_messages << "- " << buffer << " " << ToString(logLevel) << ": ";
    return m_messages;
} // getStream
template <class T>
Log<T> & Log<T>::operator=(const Log<T> & log)
{
    m_messages.str(log.m_messages.str());
    return *this;
} // operator=
// Return log level that provide info about what level of logging must be printed
template <class T>
LogLevel & Log<T>::GetReportingLevel()
{
    static LogLevel logLevel = LOG_LEVEL_ALL;
    return logLevel;
} // getReportingLevel
// Destroy the logging object and prS32 the logging messages
template <class T>
Log<T>::~Log()
{
    m_messages << std::endl;
    T::Output(m_messages.str());
} // ~Logger
// Output policy class
class LogToFile
{
public:
    static void Output(const std::string & message);
    static void SetStream(FILE * pFile);
    static FILE *& GetStream();
}; // LogToFile
inline FILE *& LogToFile::GetStream()
{
    // By default output to stderr
    static FILE * pStream = stderr;
    return pStream;
} // getStream
inline void LogToFile::Output(const std::string & message)
{
    std::lock_guard<std::mutex> lock(mutex);
    FILE * pStream = LogToFile::GetStream();
    if (!pStream)
    {
        return;
    }
    fprintf(pStream, "%s", message.c_str());
    fflush(pStream);
} // output
inline void LogToFile::SetStream(FILE * pFile)
{
    std::lock_guard<std::mutex> lock(mutex);
    LogToFile::GetStream() = pFile;
} // setStream

// Logger instance
typedef Log<LogToFile> Logger;

// Define max level logging
#ifndef LOG_MAX_LEVEL
#define LOG_MAX_LEVEL LOG_LEVEL_NONE
#endif

// Macro return the stream of messages
// You can add new messages by << operator
#define M3E_LOG(logLevel) \
    if (logLevel > LOG_MAX_LEVEL); \
    else if (logLevel < Logger::GetReportingLevel() || !LogToFile::GetStream()); \
    else Logger().GetStream(logLevel)
} // aml
#endif // _AML_LOGGER_H_
