//
//  zf_uchar.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/21.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifndef zf_uchar_h
#define zf_uchar_h

#include <stdio.h>

#ifndef __APPLE__

#include <uchar.h>

#else

#include <stdint.h>

typedef uint16_t char16_t;
typedef uint32_t char32_t;

#endif  // #ifndef __APPLE__

/// Convert a UTF-16 character to a set of UTF-8 characters.
///
/// The specified UTF-16 character should be in the Basic Multilingual Plane (BMP),
/// which can be represented in UCS-2.
///
/// The range is: U+0000 to U+D7FF and U+E000 to U+FFFF.
/// @param ch16 the specified UTF-16 character
/// @param chBuffer the buffer that will be stored with UTF-8 characters. Its space should contain at least 4 bytes.
extern void zf_char16_to_chars(char16_t ch16, char chBuffer[4]);

/// Convert a specified UTF-16 string to UTF-8 string
/// @param utf8Dst the buffer that stores the destination UTF-8 string
/// @param srcUTF16Str the specified UTF-16 source string
/// @return the length of the destination UTF-8 string (number of bytes)
extern size_t zf_utf16str_to_utf8str(char utf8Dst[], const char16_t *srcUTF16Str);

/// Convert a specified UTF-8 string to UTF-16 string
/// @param utf16Dst the buffer that stores the destination UTF-16 string
/// @param srcUTF8Str the specified UTF-8 string
/// @return the length of the destination UTF-16 string (number of characters)
extern size_t zf_utf8str_to_utf16str(char16_t utf16Dst[], const char *srcUTF8Str);

/// Get the length of the specified UTF-16 string
/// @param utf16Str the specified UTf-16 string
/// @return the number of the characters of the string
extern size_t zf_utf16_strlen(const char16_t *utf16Str);

/// Convert the specified UTF-8 string to the UTF-16 string,
/// and get the length of the UTF-16 string
/// @param utf8Str the specified UTF-8 string
/// @return the length of the converted UTF-16 string
extern size_t zf_utf16_strlen_from_utf8str(const char *utf8Str);

/// Convert the specified UTF-16 string to the UTF-8 string
/// and get the length of the UTF-8 string
/// @param utf16Str the specified UTF-16 string
/// @return the length of the converted UTF-8 string
extern size_t zf_utf8_strlen_from_utf16str(const char16_t *utf16Str);

#endif /* zf_uchar_h */

