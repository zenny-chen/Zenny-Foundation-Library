//
//  zf_uchar.c
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/21.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#include "zf_uchar.h"

#include <stdint.h>

void zf_char16_to_chars(char16_t ch16, char chBuffer[4])
{
    const uint32_t codepoint = ch16;
    if(codepoint > 0xd7ff && codepoint < 0xe000)
    {
        // The current code point is located within UTF-16 encoding of the high and low surrogates,
        // which is invalid for this function.
        chBuffer[0] = '\0';
        return;
    }
    
    if(codepoint >= 0x0800)
    {
        const uint32_t high4Bits = codepoint >> 12;
        const uint32_t mid6Bits = (codepoint >> 6) & 0x3f;
        const uint32_t low6Bits = codepoint & 0x3f;
        
        chBuffer[0] = high4Bits | 0xe0;
        chBuffer[1] = mid6Bits | 0x80;
        chBuffer[2] = low6Bits | 0x80;
    }
    else if(codepoint >= 0x0080)
    {
        const uint32_t high5Bits = codepoint >> 6;
        const uint32_t low6Bits = codepoint & 0x3f;
        
        chBuffer[0] = high5Bits | 0xc0;
        chBuffer[1] = low6Bits | 0x80;
        chBuffer[2] = '\0';
    }
    else
    {
        chBuffer[0] = codepoint;
        chBuffer[1] = '\0';
        chBuffer[2] = '\0';
    }
    
    chBuffer[3] = '\0';
}

#ifdef _WIN32
// On Windows platforms
#include "zf_sys.h"

size_t zf_utf16str_to_utf8str(char utf8Dst[], const char16_t *srcUTF16Str)
{
    if (utf8Dst == NULL || srcUTF16Str == NULL)
        return 0;

    const int len = WideCharToMultiByte(CP_UTF8, 0, srcUTF16Str, -1, NULL, 0, NULL, NULL);

    WideCharToMultiByte(CP_UTF8, 0, srcUTF16Str, -1, utf8Dst, len, NULL, NULL);

    return len - 1;
}

size_t zf_utf8str_to_utf16str(char16_t utf16Dst[], const char *srcUTF8Str)
{
    if (utf16Dst == NULL || srcUTF8Str == NULL)
        return 0;

    const int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, srcUTF8Str, -1, NULL, 0);

    // Then, convert the UTF-16 string to system default characters
    MultiByteToWideChar(CP_UTF8, 0, srcUTF8Str, -1, utf16Dst, wideStrLen);

    return wideStrLen - 1;
}

size_t zf_utf16_strlen(const char16_t *utf16Str)
{
    if (utf16Str == NULL)
        return 0;

    return wcslen(utf16Str);
}

size_t zf_utf16_strlen_from_utf8str(const char *utf8Str)
{
    if (utf8Str == NULL)
        return 0;

    const int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
    return wideStrLen - 1;
}

size_t zf_utf8_strlen_from_utf16str(const char16_t *utf16Str)
{
    if (utf16Str == NULL)
        return 0;

    const int len = WideCharToMultiByte(CP_UTF8, 0, utf16Str, -1, NULL, 0, NULL, NULL);
    return len - 1;
}

#else
// On Unix platforms

size_t zf_utf16_strlen(const char16_t *utf16Str)
{
    if(utf16Str == NULL)
        return 0;
    
    size_t length;
    for(length = 0; utf16Str[length] != u'\0'; length++);
    
    return length;
}

#ifndef __APPLE__
// On other unix-like platforms except Apple

size_t zf_utf16str_to_utf8str(char utf8Dst[], const char16_t *srcUTF16Str)
{
    if(utf8Dst == NULL || srcUTF16Str == NULL)
        return 0;
    
    size_t orgIndex = 0, dstIndex = 0;
    char16_t ch;
    
    while((ch = srcUTF16Str[orgIndex]) != u'\0')
    {
        // ASCII compatible
        if(ch < 0x80)
        {
            utf8Dst[dstIndex++] = ch;
            orgIndex++;
            continue;
        }
        
        // process Basic Multilingual Plane (BMP) unicodes
        if(ch < 0xd800 || ch >= 0xe000)
        {
            if((ch & 0xf800) == 0)
            {
                // The highest 5 bits are zero，so it indicates the 2-byte UTF-8 code
                uint8_t value = (ch >> 6) | 0xc0;
                utf8Dst[dstIndex++] = value;
                
                value = (ch & 0x3f) | 0x80;
                utf8Dst[dstIndex++] = value;
            }
            else
            {
                // 3-byte UTF-8 code
                uint8_t value = (ch >> 12) | 0xe0;
                utf8Dst[dstIndex++] = value;
                
                value = (ch >> 6) & 0x3f;
                value |= 0x80;
                utf8Dst[dstIndex++] = value;
                
                value = ch & 0x3f;
                value |= 0x80;
                utf8Dst[dstIndex++] = value;
            }
        }
        else
        {
            // process Supplementary Planes
            uint32_t high = ch - 0xd800;
            uint32_t low = srcUTF16Str[++orgIndex] - 0xdc00;
            uint32_t result = low + (high << 10);
            result += 0x00010000;
            
            uint8_t value = (result >> 18) | 0xf0;
            utf8Dst[dstIndex++] = value;
            
            value = (result >> 12) & 0x3f;
            value |= 0x80;
            utf8Dst[dstIndex++] = value;
            
            value = (result >> 6) & 0x3f;
            value |= 0x80;
            utf8Dst[dstIndex++] = value;
            
            value = (result & 0x3f) | 0x80;
            utf8Dst[dstIndex++] = value;
        }
        
        orgIndex++;
    }
    
    utf8Dst[dstIndex] = '\0';
    
    return dstIndex;
}

size_t zf_utf8str_to_utf16str(char16_t utf16Dst[], const char *srcUTF8Str)
{
    if(utf16Dst == NULL || srcUTF8Str == NULL)
        return 0;

    size_t orgIndex = 0, dstIndex = 0;
    char ch;
    
    while((ch = srcUTF8Str[orgIndex]) != '\0')
    {
        uint32_t result = 0;
        int length = 0;
        
        // counting leading '1' for number of UTF-8 bytes
        uint32_t firstByteFlag = (uint32_t)ch & 0xfc;
        while((firstByteFlag & 0x80) != 0)
        {
            firstByteFlag <<= 1;
            length++;
        }
        
        // If the length is zero, the current code is ASCII compatible.
        if(length == 0)
        {
            utf16Dst[dstIndex++] = ch;
            orgIndex++;
            continue;
        }
        
        // For most operating systems, the byte order of unicode is big endian.
        
        // Firstly, concatenate the remaining significant bits of the first byte
        result = (uint32_t)ch & (0xffU >> (length + 1));

        // If the number of bytes is less than 4，the code point is located in BMP，
        // and the Unicode length must be 2 bytes.
        // If the number of bytes is more than 3, the code point is located in Supplementary plane,
        // and the unicode is expanded to 21 bits.
        int base;
        switch(length)
        {
            case 2:
                base = 11;
                break;
                
            case 3:
                base = 16;
                break;
                
            case 4:
            default:
                base = 21;
                break;
        }
        
        int shiftedBitPosition = base - (8 - (length + 1));
        
        result <<= shiftedBitPosition;
        
        int i = 1;
        
        // Then, concatenate the bits of the remaining bytes
        do
        {
            i++;
            
            shiftedBitPosition -= 6;
            
            result |= ((uint32_t)srcUTF8Str[++orgIndex] & 0x3f) << shiftedBitPosition;
        }
        while(i < length);
        
        // If the number of bytes is less than 4，
        // the code point is located in Basic Multilingual Plane (BMP)，
        // and the Unicode length must be 2 bytes.
        if(length < 4)
            utf16Dst[dstIndex++] = result;
        else
        {
            // If the number of bytes of UTF-8 code is more than 3，
            // use high and low surrogates
            result -= 0x00010000;
            uint16_t high = result >> 10;
            uint16_t low = result - (high << 10);
            utf16Dst[dstIndex++] = high + 0xd800;
            utf16Dst[dstIndex++] = low + 0xdc00;
        }
        
        orgIndex++;
    }

    utf16Dst[dstIndex] = u'\0';

    return dstIndex;
}

size_t zf_utf16_strlen_from_utf8str(const char *utf8Str)
{
    if(utf8Str == NULL)
        return 0;
    
    size_t orgIndex = 0, dstLength = 0;
    char ch;
    
    while((ch = utf8Str[orgIndex]) != '\0')
    {
        int length = 0;
        
        // Count the leading one bits to the UTF-8 character sequence.
        // The number of leading one bits specifies the number of bytes needed to compose the character
        uint32_t firstByteFlag = (uint32_t)ch & 0xfc;
        while((firstByteFlag & 0x80) != 0)
        {
            firstByteFlag <<= 1;
            length++;
        }
        
        if(length == 0)
            length = 1;
        
        orgIndex += length;
        
        int addition = length > 3? 2 : 1;
        dstLength += addition;
    }
    
    return dstLength;
}

size_t zf_utf8_strlen_from_utf16str(const char16_t *utf16Str)
{
    if(utf16Str == NULL)
        return 0;
    
    size_t orgIndex = 0, dstLength = 0;
    char16_t ch;
    
    while((ch = utf16Str[orgIndex]) != u'\0')
    {
        // Processs ASCII compatible code points
        if(ch < 0x80)
        {
            dstLength++;
            orgIndex++;
            continue;
        }
        
        // Process BMP
        if(ch < 0xd800 || ch >= 0xe000)
        {
            if((ch & 0xf800) == 0)
            {
                // The highest 5 bits are zero,
                // which implies the UTF-8 character is composed by 2 bytes.
                dstLength += 2;
            }
            else
            {
                dstLength += 3;
            }
        }
        else
        {
            // Otherwise, the UTF-8 character is composed by 4 bytes.
            dstLength += 4;
            orgIndex++;
        }
        
        orgIndex++;
    }
    
    return dstLength;
}

#endif  // #ifndef __APPLE__


#endif  // #ifndef _WIN32

