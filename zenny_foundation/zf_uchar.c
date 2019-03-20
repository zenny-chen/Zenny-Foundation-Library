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

