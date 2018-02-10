//---------------------------------------------------------------
//
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//
//  Contents: Macros to make exception code no-ops in 16-bit
//    Includes real exceptions for 32-bit
//
//---------------------------------------------------------------

#ifndef __DFEXCEPT_HXX__
#define __DFEXCEPT_HXX__


struct Exception
{
    SCODE GetErrorCode(void) { return 0; }
};

#ifdef _MSC_VER
#pragma warning (disable:4127)  // conditional expression is constant
#endif

#endif // ifndef __DFEXCEPT_HXX__
