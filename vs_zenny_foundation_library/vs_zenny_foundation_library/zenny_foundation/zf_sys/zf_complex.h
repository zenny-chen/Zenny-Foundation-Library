//
//  zf_complex.h
//  ZennyFoundationTest
//
//  Created by Zenny Chen on 2019/12/14.
//  Copyright © 2019 Zenny Chen. All rights reserved.
//

#ifndef zf_complex_h
#define zf_complex_h

#include <complex.h>

#ifdef _WIN32
// For MSVC and Clang in Visual Studio

// Complex types
typedef _Fcomplex               zf_float_complex;
typedef _Dcomplex               zf_double_complex;
typedef _C_ldouble_complex      zf_ldouble_complex;

// Construct a complex number object
#define ZF_FLOAT_COMPLEX(real, imag)        _FCOMPLEX_((real), (imag))
#define ZF_DOUBLE_COMPLEX(real, imag)       _DCOMPLEX_((real), (imag))
#define ZF_LONG_DOUBLE_COMPLEX(real, imag)  _LCOMPLEX_((real), (imag))

// complex add
static inline zf_float_complex zf_caddf(zf_float_complex a, zf_float_complex b)
{
    return ZF_FLOAT_COMPLEX(a._Val[0] + b._Val[0], a._Val[1] + b._Val[1]);
}

static inline zf_double_complex zf_cadd(zf_double_complex a, zf_double_complex b)
{
    return ZF_DOUBLE_COMPLEX(a._Val[0] + b._Val[0], a._Val[1] + b._Val[1]);
}

static inline zf_ldouble_complex zf_caddl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return ZF_LONG_DOUBLE_COMPLEX(a._Val[0] + b._Val[0], a._Val[1] + b._Val[1]);
}

// complex sub
static inline zf_float_complex zf_csubf(zf_float_complex a, zf_float_complex b)
{
    return ZF_FLOAT_COMPLEX(a._Val[0] - b._Val[0], a._Val[1] - b._Val[1]);
}

static inline zf_double_complex zf_csub(zf_double_complex a, zf_double_complex b)
{
    return ZF_DOUBLE_COMPLEX(a._Val[0] - b._Val[0], a._Val[1] - b._Val[1]);
}

static inline zf_ldouble_complex zf_csubl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return ZF_LONG_DOUBLE_COMPLEX(a._Val[0] - b._Val[0], a._Val[1] - b._Val[1]);
}

// complex mul
static inline zf_float_complex zf_cmulf(zf_float_complex a, zf_float_complex b)
{
    return ZF_FLOAT_COMPLEX(a._Val[0] * b._Val[0] - a._Val[1] * b._Val[1], 
        a._Val[0] * b._Val[1] + a._Val[1] * b._Val[0]);
}

static inline zf_double_complex zf_cmul(zf_double_complex a, zf_double_complex b)
{
    return ZF_DOUBLE_COMPLEX(a._Val[0] * b._Val[0] - a._Val[1] * b._Val[1], 
        a._Val[0] * b._Val[1] + a._Val[1] * b._Val[0]);
}

static inline zf_ldouble_complex zf_cmull(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return ZF_LONG_DOUBLE_COMPLEX(a._Val[0] * b._Val[0] - a._Val[1] * b._Val[1], 
        a._Val[0] * b._Val[1] + a._Val[1] * b._Val[0]);
}

// complex div
static inline zf_float_complex zf_cdivf(zf_float_complex a, zf_float_complex b)
{
    const float coeff = 1.0f / (b._Val[0] * b._Val[0] + b._Val[1] * b._Val[1]);
    return ZF_FLOAT_COMPLEX((a._Val[0] * b._Val[0] + a._Val[1] * b._Val[1]) * coeff,
        (a._Val[1] * b._Val[0] - a._Val[0] * b._Val[1]) * coeff);
}

static inline zf_double_complex zf_cdiv(zf_double_complex a, zf_double_complex b)
{
    const double coeff = 1.0 / (b._Val[0] * b._Val[0] + b._Val[1] * b._Val[1]);
    return ZF_DOUBLE_COMPLEX((a._Val[0] * b._Val[0] + a._Val[1] * b._Val[1]) * coeff,
        (a._Val[1] * b._Val[0] - a._Val[0] * b._Val[1]) * coeff);
}

static inline zf_ldouble_complex zf_cdivl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    const long double coeff = 1.0L / (b._Val[0] * b._Val[0] + b._Val[1] * b._Val[1]);
    return ZF_LONG_DOUBLE_COMPLEX((a._Val[0] * b._Val[0] + a._Val[1] * b._Val[1]) * coeff,
        (a._Val[1] * b._Val[0] - a._Val[0] * b._Val[1]) * coeff);
}

#else
// For GCC and Clang in Unix-like systems

// Complex types
typedef float complex           zf_float_complex;
typedef double complex          zf_double_complex;
typedef long double complex     zf_ldouble_complex;

// Construct a complex number object
#define ZF_FLOAT_COMPLEX(real, imag)        CMPLXF((real), (imag))
#define ZF_DOUBLE_COMPLEX(real, imag)       CMPLX((real), (imag))
#define ZF_LONG_DOUBLE_COMPLEX(real, imag)  CMPLXL((real), (imag))

// complex add
static inline zf_float_complex zf_caddf(zf_float_complex a, zf_float_complex b)
{
    return a + b;
}

static inline zf_double_complex zf_cadd(zf_double_complex a, zf_double_complex b)
{
    return a + b;
}

static inline zf_ldouble_complex zf_caddl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return a + b;
}

// complex sub
static inline zf_float_complex zf_csubf(zf_float_complex a, zf_float_complex b)
{
    return a - b;
}

static inline zf_double_complex zf_csub(zf_double_complex a, zf_double_complex b)
{
    return a - b;
}

static inline zf_ldouble_complex zf_csubl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return a - b;
}

// complex mul
static inline zf_float_complex zf_cmulf(zf_float_complex a, zf_float_complex b)
{
    return a * b;
}

static inline zf_double_complex zf_cmul(zf_double_complex a, zf_double_complex b)
{
    return a * b;
}

static inline zf_ldouble_complex zf_cmull(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return a * b;
}

// complex div
static inline zf_float_complex zf_cdivf(zf_float_complex a, zf_float_complex b)
{
    return a / b;
}

static inline zf_double_complex zf_cdiv(zf_double_complex a, zf_double_complex b)
{
    return a / b;
}

static inline zf_ldouble_complex zf_cdivl(zf_ldouble_complex a, zf_ldouble_complex b)
{
    return a / b;
}

#endif  // #ifdef _WIN32

#endif /* zf_complex_h */

