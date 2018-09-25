#pragma once
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
namespace aml {
// Return 32 bit RGB color value
inline U32 RGB32(U8 red, U8 green, U8 blue)
{
    U32 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, red
        shl eax, 8
        mov ah, green
        mov al, blue
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[red], %%ah\n\t"
        "shll $8, %[color]\n\t"
        "movb %[green], %%ah\n\t"
        "movb %[blue], %%al\n\t"
        :[color]"=r"(color)
        :[red]"m"(red),[green]"m"(green),[blue]"m"(blue)
        :"cc");
#endif
    return color;
}
// Return 32 nit BGR color value
inline U32 BGR32(U8 blue, U8 green, U8 red)
{
    U32 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, blue
        shl eax, 8
        mov ah, green
        mov al, red
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[blue], %%ah\n\t"
        "shll $8, %[color]\n\t"
        "movb %[green], %%ah\n\t"
        "movb %[red], %%al\n\t"
        :[color]"=r"(color)
        :[red]"m"(red),[green]"m"(green),[blue]"m"(blue)
        :"cc");
#endif
    return color;
}
// Return 32 bit ARGB color value
inline U32 ARGB32(U8 alpha, U8 red, U8 green, U8 blue)
{
    U32 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, alpha
        mov al, red
        shl eax, 16
        mov ah, green
        mov al, blue
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[alpha], %%ah\n\t"
        "movb %[red], %%al\n\t"
        "shll $16, %[color]\n\t"
        "movb %[green], %%ah\n\t"
        "movb %[blue], %%al\n\t"
        :[color]"=r"(color)
        :[alpha]"m"(alpha),[red]"m"(red),[green]"m"(green),[blue]"m"(blue)
        :"cc");
#endif
    return color;
}
// Return 32 bit RGBA color value
inline U32 RGBA32(U8 red, U8 green, U8 blue, U8 alpha)
{
    U32 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, red
        mov al, green
        shl eax, 16
        mov ah, blue
        mov al, alpha
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[red], %%ah\n\t"
        "movb %[green], %%al\n\t"
        "shll $16, %[color]\n\t"
        "movb %[blue], %%ah\n\t"
        "movb %[alpha], %%al\n\t"
        :[color]"=r"(color)
        :[red]"m"(red),[green]"m"(green),[blue]"m"(blue),[alpha]"m"(alpha)
        :"cc");
#endif
    return color;
}
// Return 32 bit ABGR color value
inline U32 ABGR32(U8 alpha, U8 blue, U8 green, U8 red)
{
    U32 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, alpha
        mov al, blue
        shl eax, 16
        mov ah, green
        mov al, red
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[alpha], %%ah\n\t"
        "movb %[blue], %%al\n\t"
        "shll $16, %[color]\n\t"
        "movb %[green], %%ah\n\t"
        "movb %[red], %%al\n\t"
        :[color]"=r"(color)
        :[alpha]"m"(alpha),[red]"m"(red),[green]"m"(green),[blue]"m"(blue)
        :"cc");
#endif
    return color;
}
// Return 32 bit BGRA color value
inline U32 BGRA32(U8 blue, U8 green, U8 red, U8 alpha)
{
    U8 color = 0;
#ifdef _MSC_VER
    _asm
    {
        mov eax, 0
        mov ah, blue
        mov al, green
        shl eax, 16
        mov ah, red
        mov al, alpha
        mov color, eax
    }
#elif __GNUC__
    asm("movl $0, %[color]\n\t"
        "movb %[blue], %%ah\n\t"
        "movb %[green], %%al\n\t"
        "shll $16, %[color]\n\t"
        "movb %[red], %%ah\n\t"
        "movb %[alpha], %%al\n\t"
        :[color]"=r"(color)
        :[red]"m"(red),[green]"m"(green),[blue]"m"(blue),[alpha]"m"(alpha)
        :"cc");
#endif
    return color;
}
} // aml
