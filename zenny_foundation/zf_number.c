//
//  zf_number.c
//  FoundationBasedAlgorithms
//
//  Created by Zenny Chen on 2018/11/21.
//  Copyright © 2018 CodeLearning Studio. All rights reserved.
//

#include "zf_number.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ZFConvertNumberToUTF8String(const struct ZFNumber *numObj, char dstBuffer[64])
{
    if(numObj == NULL || numObj->obj.identifier != ZENNY_NUMBER_IDENTIFIER)
    {
        dstBuffer[0] = '\0';
        return;
    }

    const union ZFNumberValueType value = numObj->value;

    switch(numObj->encoding)
    {
        case ZF_NUMBER_ENCODING_BOOL:
            if(value.b)
            {
                dstBuffer[0] = 't';
                dstBuffer[1] = 'r';
                dstBuffer[2] = 'u';
                dstBuffer[3] = 'e';
                dstBuffer[4] = '\0';
            }
            else
            {
                dstBuffer[0] = 'f';
                dstBuffer[1] = 'a';
                dstBuffer[2] = 'l';
                dstBuffer[3] = 's';
                dstBuffer[3] = 'e';
                dstBuffer[5] = '\0';
            }
            break;
            
        case ZF_NUMBER_ENCODING_CHAR:
            dstBuffer[0] = value.c;
            dstBuffer[1] = '\0';
            break;
            
        case ZF_NUMBER_ENCODING_CHAR16:
            zf_char16_to_chars(value.u, dstBuffer);
            break;

        case ZF_NUMBER_ENCODING_BYTE:
            sprintf(dstBuffer, "%d", value.a);
            break;
            
        case ZF_NUMBER_ENCODING_UBYTE:
            sprintf(dstBuffer, "%u", value.A);
            break;
            
        case ZF_NUMBER_ENCODING_SHORT:
            sprintf(dstBuffer, "%d", value.s);
            break;
            
        case ZF_NUMBER_ENCODING_USHORT:
            sprintf(dstBuffer, "%u", value.S);
            break;
            
        case ZF_NUMBER_ENCODING_INT:
            sprintf(dstBuffer, "%d", value.i);
            break;
            
        case ZF_NUMBER_ENCODING_UINT:
            sprintf(dstBuffer, "%u", value.I);
            break;
            
        case ZF_NUMBER_ENCODING_LONG:
            sprintf(dstBuffer, "%lld", (long long)value.l);
            break;
            
        case ZF_NUMBER_ENCODING_ULONG:
            sprintf(dstBuffer, "%llu", (unsigned long long)value.L);
            break;
            
        case ZF_NUMBER_ENCODING_PTRDIFF:
            // including case ZF_NUMBER_ENCODING_SSIZE:
            sprintf(dstBuffer, "%td", value.t);
            break;
            
        case ZF_NUMBER_ENCODING_SSIZE:
            sprintf(dstBuffer, "%zd", value.z);
            break;

        case ZF_NUMBER_ENCODING_SIZE:
            sprintf(dstBuffer, "%zu", value.Z);
            break;
            
        case ZF_NUMBER_ENCODING_INTPTR:
            sprintf(dstBuffer, "%td", value.p);
            break;
            
        case ZF_NUMBER_ENCODING_UINTPTR:
            sprintf(dstBuffer, "%tu", value.P);
            break;
            
        case ZF_NUMBER_ENCODING_INTMAX:
            sprintf(dstBuffer, "%td", value.x);
            break;
            
        case ZF_NUMBER_ENCODING_UINTMAX:
            sprintf(dstBuffer, "%tu", value.X);
            break;

        case ZF_NUMBER_ENCODING_FLOAT:
            sprintf(dstBuffer, "%f", value.f);
            break;
            
        case ZF_NUMBER_ENCODING_DOUBLE:
            sprintf(dstBuffer, "%f", value.d);
            break;

        default:
            dstBuffer[0] = '\0';
            break;
    }
}

