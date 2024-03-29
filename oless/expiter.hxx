//+--------------------------------------------------------------
//
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h 
// 
//  Copyright (c) 1999 Digital Imaging Group, Inc.
// 
//  Contents: CExposedIterator header file
//
//  Classes:  CExposedIterator
//
//---------------------------------------------------------------

#ifndef __EXPITER_HXX__
#define __EXPITER_HXX__

#include "h/dfmsp.hxx"

class CDirectStream;

//+--------------------------------------------------------------
//
//  Class:  CExposedIterator (ei)
//
//  Purpose:  Iterator for wrapped DocFiles
//
//  Interface:  See below
//
//---------------------------------------------------------------

interface CExposedIterator : public IEnumSTATSTG
{
public:
    CExposedIterator(CExposedDocFile *ppdf, CDfName *pKey);
    virtual ~CExposedIterator(void);

    // From IUnknown
    STDMETHOD(QueryInterface)(REFIID iid, void **ppvObj);
    STDMETHOD_(ULONG,AddRef)(void);
    STDMETHOD_(ULONG,Release)(void);

    // New methods
    STDMETHOD(Next)(ULONG celt, STATSTG FAR *rgelt,
                    ULONG *pceltFetched);
#ifndef _UNICODE
    SCODE Next(ULONG celt, STATSTGW FAR *rgelt, ULONG *pceltFetched);
#endif
    STDMETHOD(Skip)(ULONG celt);
    STDMETHOD(Reset)(void);
    STDMETHOD(Clone)(IEnumSTATSTG **ppenm);

    inline SCODE Validate(void) const;
private:
    CDfName _dfnKey;
    LONG _cReferences;
    ULONG _sig;
    CExposedDocFile *_ppdf;
};

// DocFileIter signatures
#define CEXPOSEDITER_SIG LONGSIG('E', 'D', 'F', 'I')
#define CEXPOSEDITER_SIGDEL LONGSIG('E', 'd', 'F', 'i')

//+--------------------------------------------------------------
//
//  Member: CExposedIterator::Validate, public
//
//  Synopsis: Validates the signature
//
//  Returns:  Returns STG_E_INVALIDHANDLE if the signature 
//              doesn't match
//
//---------------------------------------------------------------

inline SCODE CExposedIterator::Validate(void) const 
{ 
    return (_sig != CEXPOSEDITER_SIG) ? STG_E_INVALIDHANDLE : S_OK; 
}

#endif



