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
#include "Types.h"
namespace aml {
// Return application path
inline wstring GetAppPath()
{
    static wstring strAppPath = L"";
	if (strAppPath.empty())
    {
		// Get full path to app
		strAppPath.resize(MAX_PATH, 0);
		GetModuleFileName(NULL, &strAppPath.front(), MAX_PATH);
		// Get path without app name
		S32 iSlashPos = strAppPath.rfind(L"\\");
		if (iSlashPos != wstring::npos)
		{
			strAppPath.resize(iSlashPos - 1);
		}
    } 
	return strAppPath;
} // GetAppPath()
// Get file extension
inline wstring GetFileExt(const wstring& strFileName)
{
	S32 iDotPos = strFileName.rfind(L".");
    wstring strExt;
    if (iDotPos != wstring::npos)
    {
        strExt = strFileName.substr(iDotPos + 1);
    }
	return strExt;
} // GetFileExt
// Get file name
inline wstring GetFileName(const wstring& strFileName)
{
    S32 iDotPos = strFileName.rfind(L".");
    wstring strName = strFileName;
    if (iDotPos != wstring::npos)
    {
        strName = strFileName.substr(0, iDotPos - 1);
    }
    return strName;
} // GetFileName
} // aml
#endif // _AML_SYSTEM_UTIL_H_
