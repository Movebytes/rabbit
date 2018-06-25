/*
 * Copyright 2018 Movebytes Group.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _AML_SYSTEM_UTIL_H_
#define _AML_SYSTEM_UTIL_H_
#include <string>
#include <Windows.h>
#include "Types.h"
namespace aml {
// Return application path
inline std::wstring GetAppPath()
{
    static std::wstring strAppPath = L"";
	if (strAppPath.empty())
    {
		// Get full path to app
        wchar_t buffer[_MAX_PATH];
		memset(buffer, 0, sizeof(buffer));
		GetModuleFileName(NULL, buffer, _MAX_PATH);
		// Get path without app name
		S32 i = wcslen(buffer) - 1;
		for (i; i > 0; i--)
		{
			if (buffer[i] == '\\')
			{
				break;
			}
		}
		// Mark end of string
		buffer[i + 1] = '\0';
		strAppPath.assign(buffer);
    } 
	return strAppPath;
} // GetAppPath()
// Get file extension
inline std::wstring GetFileExt(const std::wstring& strFileName)
{
	S32 iDot = strFileName.rfind(L".");
    std::wstring strExt;
    if (iDot != std::wstring::npos)
    {
        strExt = strFileName.substr(iDot + 1);
    }
	return strExt;
} // GetFileExt
// Get file name
inline std::wstring GetFileName(const std::wstring& strFileName)
{
    S32 iDot = strFileName.rfind(L".");
    std::wstring strName = strFileName;
    if (iDot != std::wstring::npos)
    {
        strName = strFileName.substr(0, iDot - 1);
    }
    return strName;
} // GetFileName
} // m3e
#endif // _M3E_SYSTEM_UTIL_H_
