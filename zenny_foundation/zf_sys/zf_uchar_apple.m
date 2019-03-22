//
//  zf_uchar.m
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/3/22.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifdef __APPLE__

@import Foundation;

#include "zf_uchar.h"
#include "zf_sys.h"

size_t zf_utf16str_to_utf8str(char utf8Dst[], const char16_t *srcUTF16Str)
{
    if(utf8Dst == NULL || srcUTF16Str == NULL)
        return 0;

    const let length = zf_utf16_strlen(srcUTF16Str);
    if(length == 0)
    {
        utf8Dst[0] = '\0';
        return 0;
    }

    @autoreleasepool {
        let utf16Str = [NSString stringWithCharacters:srcUTF16Str length:length];
        if(utf16Str == nil)
            return 0;
        
        strcpy(utf8Dst, utf16Str.UTF8String);
    }

    return strlen(utf8Dst);
}

size_t zf_utf8str_to_utf16str(char16_t utf16Dst[], const char *srcUTF8Str)
{
    if(utf16Dst == NULL || srcUTF8Str == NULL)
        return 0;
    
    @autoreleasepool {
        let str = [NSString stringWithUTF8String:srcUTF8Str];
        if(str == nil)
            return 0;
        
        const size_t length = str.length;
        if(length == 0)
            utf16Dst[0] = u'\0';
        else
            [str getCharacters:utf16Dst];
        
        return length;
    }
}

#endif  // #ifdef __APPLE__

