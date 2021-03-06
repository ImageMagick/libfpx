//---------------------------------------------------------------
//
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h 
// 
//  Copyright (c) 1999 Digital Imaging Group, Inc.
// 
//  Contents:   Implementations of CDocFile iterator methods
//
//---------------------------------------------------------------

#include "dfhead.cxx"


#include "h/msfiter.hxx"
#include "iter.hxx"



//+--------------------------------------------------------------
//
//  Member:     CDocFile::GetIterator, public
//
//  Synopsis:   Gets a new iterator
//
//  Arguments:  [ppdfi] - Iterator object return
//
//  Returns:    Appropriate status code
//
//  Modifies:   [ppdfi]
//
//---------------------------------------------------------------

SCODE CDocFile::GetIterator(PDocFileIterator **ppdfi)
{
    CDocFileIterator *pdfi;
    SCODE sc;

    olDebugOut((DEB_ITRACE, "In  CDocFile::GetIterator(%p)\n", ppdfi));
    olMem(pdfi = new CDocFileIterator);
    olChkTo(EH_pdfi, pdfi->Init(&_stgh));
    *ppdfi = pdfi;
    olDebugOut((DEB_ITRACE, "Out CDocFile::GetIterator => %p\n", *ppdfi));
    return S_OK;

EH_pdfi:
    delete pdfi;
EH_Err:
    return sc;
}
