//  ------------------------------------------------------------------------------------------------
//  MODULE      : FITypes
//  LANGAGE     : C and C++
//  CREATEUR    : Laurent ALBERT
//  DATE        : Mardi 19 Octobre 1993
//  DESCRIPTION : Define LivePicture Inc's basic types.
//  COMMENT   : Mustn't include ApplCommun.h
//          LS 04/02/96: This file isn't supposed to be included everywhere anymore
//                 Extract FIDefines.h, MacCompatibility.h, FIErrors.h and SwapBytes.h
//  SCCSID      : @(#)b_types.h 1.1 11:49:56 18 Dec 1996
//  ----------------------------------------------------------------------------
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//  ----------------------------------------------------------------------------
//  ------------------------------------------------------------------------------------------------
#ifndef FITypes_h
#define FITypes_h
//  ------------------------------------------------------------------------------------------------


//  Includes
//  --------

#ifndef FIDefines_h
    #include "p_define.h"
#endif

// Defines common types
#include <stddef.h>
#include <inttypes.h>

// Defines common Mac types
#ifdef macintosh
  #include <Types.h>
#endif

//  Types and constants
//  -------------------

// Portable integer types
typedef int32_t	int32;
typedef int16_t	int16;
typedef int8_t	int8;

typedef uint32_t	unsigned32;
typedef uint16_t	unsigned16;
typedef uint8_t	unsigned8;

  // Added by GDN
  typedef unsigned16  uint16;
  typedef unsigned32  uint32;
  
// Portable boolean type
#ifndef macintosh

  #ifndef false
    #define false 0
  #endif
  #ifndef true
    #define true 1
  #endif

  #ifndef Boolean_ID 
    #define Boolean_ID
    typedef unsigned char Boolean;
  #endif
#endif

// MWP 4/29/96: Use these for TRUE & FALSE
#ifndef FALSE
    #define FALSE   0
#endif

#ifndef TRUE
    #define TRUE    1
#endif


/* Portable error code type */
#ifndef macintosh
    typedef int16 OSErr;        
#endif

  // Added by GDN
  typedef unsigned char *StrPtr;
  typedef const unsigned char *ConstStrPtr;

  typedef void* ptr;
  
//  Constants
//  ---------

    #ifndef NULL
      #define NULL 0
    #endif
    
  enum UniteMetrique { uMm, uCm, uInch, uPixel, uPoint, uScreenPixel, uDpi, uDegrees, uMegabytes };

//  ------------------------------------------------------------------------------------------------
#endif // FITypes_h
//  ------------------------------------------------------------------------------------------------
