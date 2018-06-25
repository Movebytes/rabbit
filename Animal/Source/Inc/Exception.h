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
#ifndef _AML_EXCEPTION_H_
#define _AML_EXCEPTION_H_
#include <exception>
#include <string>
#include "Logger.h"
#include "Types.h"
namespace aml {
// Todo: Add more detailed exception class for different states
// Custom exception class helper
class Exception: public std::exception
{
private:
    const char * m_szFileName;
    S32 m_iLineNum;
    std::string m_strMessage;
    std::string m_strReport;
public:
    // Formating helper class
    class StreamFormatter
    {
    private:
        std::ostringstream m_ossStream;
    public:
        operator std::string() const
        {
            return m_ossStream.str();
        }
        template<typename T>
        StreamFormatter& operator << (const T& value)
        {
            m_ossStream << value;
            return *this;
        }
    }; // StreamFormatter
    // Default constructor
    Exception(const char * szFileName, S32 iLineNum, const std::string strMessage);
    // Default destructor
    ~Exception() throw();
    // Return exception report message
    virtual const char* what() const throw();
    // Return file name where exception was throwed
    const char* GetFileName() const throw();
    // Return line number where exception was throwed
    S32 GetLineNum() const throw();
    // Retur exception error message
    const char* GetMessage() const throw();
}; // Exception
// Default constructor
inline Exception::Exception(const char * szFileName, S32 iLineNum, const std::string strMessage)
    : m_szFileName(szFileName)
    , m_iLineNum(iLineNum)
    , m_strMessage(strMessage)
{
    std::stringstream ssOutput;
    if (!strMessage.empty())
    {
        ssOutput << strMessage << "  ";
    }
    ssOutput << "Exception throwed from file \"" << szFileName << "\" on line " << iLineNum;
    m_strReport = ssOutput.str();
    M3E_LOG(LOG_LEVEL_ERROR) << m_strReport ;
}
// Default destructor
inline Exception::~Exception() throw()
{}
// Return exception report message
inline const char* Exception::what() const throw()
{
    return m_strReport.c_str();
}
// Return file name where exception was throwed
inline const char* Exception::GetFileName() const throw()
{
    return m_szFileName;
}
// Return line number where exception was throwed
inline S32 Exception::GetLineNum() const throw()
{
    return m_iLineNum;
}
// Retur exception error message
inline const char* Exception::GetMessage() const throw()
{
    return m_strMessage.c_str();
}
} // aml
#define AML_EXCEPTION(MESSAGE) throw m3e::Exception(__FILE__, __LINE__, (aml::Exception::StreamFormatter() << MESSAGE));
#define AML_ASSERT(condition) \
if (!condition) \
{ \
    AML_EXCEPTION("Assertion failure!") \
}
#endif // _AML_EXCEPTION_H_
