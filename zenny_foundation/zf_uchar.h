//
//  zf_uchar.h
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/21.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#ifndef zf_uchar_h
#define zf_uchar_h

#ifndef __APPLE__

#include <uchar.h>

#else

#include <stdint.h>

typedef uint16_t char16_t;

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

#endif /* zf_uchar_h */

