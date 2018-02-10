//   ----------------------------------------------------------------------------
//  MODULE      : OLECommun.h
//  LANGAGE     : C++
//  AUTHOR      : Nicolas Romantzoff
//  DATE        : July 7th 1995
//  DESCRIPTION :
//  COMMENT     : Most of the definitions are copied from Windows headers
//  SCCSID      : @(#)olecomm.h 1.2 14:47:37 06 Jan 1997
//  ----------------------------------------------------------------------------
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//  ----------------------------------------------------------------------------
#ifndef OLECommun_h
# define OLECommun_h
# ifndef FITypes_h
#  include "b_types.h"
# endif
//  ----------------------------------------------------------------------------


# ifdef macintosh
#  define _MAC 1
#  define MAC  1
#  define _DEBUG 1
#  define DEBUG  1
// The following has to be used with CW7 or better...
#  define NO_NULL_VTABLE_ENTRY 1
# endif

//  Includes
//  --------

# ifdef _WINDOWS
#  include  <ole2.h>
#  include  <ole2ver.h>
#  include  <oleauto.h>
#  include "str8_16.h"
# endif

# ifdef macintosh
#  include  <ole2.h>
#  include  <ole2ver.h>
#  include  <dispatch.h>
# endif

# if defined(_UNIX)
// use the reference implementation header files
#  include "exphead.cxx"
#  include "msfhead.cxx"
#  include "dfhead.cxx"
#  include "props.h" // for VARIANT defenition
# endif // _UNIX

//  Constants
//  ---------

// Storage Access Mode Flags used in the most common opening cases
// As stupid as it can seem, STGM_SHARE_EXCLUSIVE is required by OLE to open a stream, otherwise, OLE
// raises a STG_E_INVALIDFUNCTION error (see OLE2 Programmer's Reference p.572). Consequently, THERE IS
// NO WAY TO OPEN A FILE TWICE EVEN IN READ ONLY... clever...
# define OLE_READ_ONLY_MODE  (STGM_READ      | STGM_SHARE_EXCLUSIVE  | STGM_DIRECT)
# define OLE_READWRITE_MODE  (STGM_READWRITE | STGM_SHARE_EXCLUSIVE  | STGM_DIRECT)
# define OLE_CREATE_MODE   (STGM_READWRITE | STGM_SHARE_EXCLUSIVE  | STGM_DIRECT | STGM_CREATE)

// value to define if the file is to be read/written in Intel mode or not
# if defined(_UNIX)
#  ifdef __linux__
#   include <endian.h>
#  elif defined(__sun)
#   include <solaris.h>
#  else
#   include <machine/endian.h>
#  endif
#  if BYTE_ORDER == BIG_ENDIAN
#   define IN_BIG_ENDIAN short(-257)
#  else
#   define IN_LITTLE_ENDIAN    short(-2) // 0xFFFE
#  endif
# elif defined(macintosh)
#  define IN_BIG_ENDIAN     short(-257) // 0xFEFF
# else
#  define IN_LITTLE_ENDIAN    short(-2) // 0xFFFE
# endif

  // Define OLE_STR and V_UI1REF
# if defined(_UNIX) || defined(macintosh)
#  define OLE_STR (char*)
#  undef V_UI1REF
#  define V_UI1REF(X) V_BSTR(X)
# endif

# define MAKE_DWORD(a,b)   (DWORD)((DWORD(a)<<16) + DWORD(b))

// This is the structure used to define read/writable arrays (vectors).
typedef struct
{
  DWORD cElements;
  union
  {
    BYTE  *prgb;      // Pointer to unsigned char
    WORD  *prgw;      // Pointer to unsigned short
    DWORD *prgdw;     // Pointer to unsigned long
    float *prgflt;    // Pointer to float
    double  *prgdbl;  // Pointer to double
    char  **prgpsz;   // Pointer to char*
    WCHAR **prgpwz;   // Pointer to WCHAR*
    BLOB  **prgblob;  // Pointer to BLOB*
    VARIANT *pvar;    // Pointer to VARIANT
    CLIPDATA  **pcd;  // Pointer to CLIPDATA*
    CLSID *pclsid;    // Pointer to CLSID
  };
} VECTOR;

// ComObj structure
typedef struct tagCOMPOBJHEADER {
  DWORD dwVersionAndByteOrder;
  DWORD dwFormat;
  DWORD unused;
  CLSID clsidClass;
} COMPOBJHEADER;

//  Classes declarations
//  --------------------

//  Classes definitions
//  --------------------

//  Functions 'inline'
//  ------------------

//  Functions 'extern'
//  ------------------

//  Variables 'extern'
//  ------------------

//   ----------------------------------------------------------------------------
  #endif // OLECommun_h
//   ----------------------------------------------------------------------------
